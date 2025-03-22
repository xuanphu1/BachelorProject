#include "GPIO_Handmade.h"

static volatile GPIO_Handmade_t *GPIO_List[] = {
    GPIOA_HANDMADE, GPIOB_HANDMADE, GPIOC_HANDMADE, 
    GPIOD_HANDMADE, GPIOE_HANDMADE, GPIOF_HANDMADE, GPIOG_HANDMADE
};

GPIO_Error_t InitGPIO(GPIO_config_t *config_gpio){

    if (config_gpio == NULL || 
        config_gpio->port > Port_G || 
        config_gpio->pin > PIN_15 || 
        config_gpio->cnf_mode > CNF_MODE_11 || 
        config_gpio->mode > OUTPUT_MODE_50_MHZ) {
        return GPIO_ERROR_INVALID_PARAM;
    }

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[config_gpio->port];

    Enable_Clock_RCC_APB2((APB2_Peripheral_Clock)(config_gpio->port + IOPA_EN_CLK)); // Enable clock for port A, B, C, D, E, F, G
    
    if(config_gpio->pin < PIN_8){
        // clear 4 bits (MODE[1:0] và CNF[1:0])
        GPIOx->GPIO_CRL &= ~(0xF << (config_gpio->pin * 4)); 
        // Set bits mới (MODE & CNF gộp chung)
        GPIOx->GPIO_CRL |= (((config_gpio->cnf_mode << 2) | config_gpio->mode) << (config_gpio->pin * 4));

    }
    else{ if(config_gpio->pin <= PIN_15){
        // clear 4 bits (MODE[1:0] và CNF[1:0])
        GPIOx->GPIO_CRH &= ~(0xF << ((config_gpio->pin-8) * 4)); 
        // Set bits mới (MODE & CNF gộp chung)
        GPIOx->GPIO_CRH |= (((config_gpio->cnf_mode << 2) | config_gpio->mode) << ((config_gpio->pin-8) * 4));

        }
    }
    return GPIO_OK;
}

uint32_t ReadPin(Port_t port,Pin_gpio_t Pin){
    if (port > Port_G || Pin > PIN_15) return GPIO_ERROR_INVALID_PARAM;
    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];
    return (GPIOx->GPIO_IDR >> Pin) & 0x1;

}

GPIO_Error_t WritePin(Port_t port, Pin_gpio_t Pin, uint32_t value){
    if (port > Port_G || Pin > PIN_15 || (value != GPIO_LOW && value != GPIO_HIGH)) {
        return GPIO_ERROR_INVALID_PARAM;
    }
    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];
    uint32_t mode_bits = (Pin < PIN_8) ? 
        ((GPIOx->GPIO_CRL >> (Pin * 4)) & 0x3) : 
        ((GPIOx->GPIO_CRH >> ((Pin - 8) * 4)) & 0x3);

    if (mode_bits == INPUT_MODE) {
        return GPIO_ERROR_NOT_INITIALIZED; // Chân chưa được cấu hình làm đầu ra
    }
    
    if(value == GPIO_LOW){
        GPIOx->GPIO_BRR = (1 << Pin);
    }
    else{
        GPIOx->GPIO_BSRR = (1 << Pin);
    }
    return GPIO_OK;
}

GPIO_Error_t TogglePin(Port_t port, Pin_gpio_t Pin){
    // Kiểm tra port hợp lệ
    if (port > Port_G) return GPIO_ERROR_INVALID_PARAM;

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];

    // Toggle bit tương ứng
    if (((GPIOx->GPIO_ODR >> Pin) & 0x1) == 0){
        GPIOx->GPIO_BSRR = (1 << Pin);
    }
    else{
        GPIOx->GPIO_BRR = (1 << Pin);
    }
    return GPIO_OK;
}

GPIO_Error_t WriteMultiPins(Port_t port, uint32_t pin_mask, uint32_t value) {
    if (port > Port_G) {
        return GPIO_ERROR_INVALID_PARAM;
    }

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];
    GPIOx->GPIO_BSRR = (pin_mask & value);           // Set các bit HIGH
    GPIOx->GPIO_BRR = (pin_mask & ~value);           // Reset các bit LOW
    return GPIO_OK;
}

GPIO_Error_t ReadMultiPins(Port_t port, Pin_gpio_t *pins, uint8_t *output_array, uint8_t pin_count) {
    // Kiểm tra tham số đầu vào
    if (port > Port_G || pins == NULL || output_array == NULL || pin_count == 0 || pin_count > 16) {
        return GPIO_ERROR_INVALID_PARAM;
    }

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];

    // Đọc toàn bộ thanh ghi IDR một lần duy nhất để tối ưu hiệu suất
    uint32_t idr_value = GPIOx->GPIO_IDR;

    // Kiểm tra từng chân và lưu kết quả vào mảng
    for (uint32_t i = 0; i < pin_count; i++) {
        if (pins[i] > PIN_15) {
            return GPIO_ERROR_INVALID_PARAM; // Chân không hợp lệ
        }

        // Kiểm tra xem chân đã được cấu hình làm đầu vào chưa
        uint32_t mode_bits = (pins[i] < PIN_8) ? 
            ((GPIOx->GPIO_CRL >> (pins[i] * 4)) & 0x3) : 
            ((GPIOx->GPIO_CRH >> ((pins[i] - 8) * 4)) & 0x3);

        if (mode_bits != INPUT_MODE) {
            return GPIO_ERROR_NOT_INITIALIZED; // Chân chưa được cấu hình làm đầu vào
        }

        // Lưu trạng thái của chân vào mảng (0 hoặc 1)
        output_array[i] = (idr_value >> pins[i]) & 0x1;
    }

    return GPIO_OK;
}
GPIO_Error_t enableSWD(void) {
    Enable_Clock_RCC_APB2(IOPA_EN_CLK);
    Enable_Clock_RCC_APB2(AFIO_EN_CLK);

    // Kiểm tra nếu SWD đã được bật
    if ((AFIO_HANDMADE->MAPR & (0x7 << 24)) == (0x2 << 24)) {
        return GPIO_OK; // SWD đã được cấu hình
    }

    AFIO_HANDMADE->MAPR &= ~(0x7 << 24); // Clear SWJ bits
    AFIO_HANDMADE->MAPR |= (0x2 << 24);  // SWD ON, JTAG OFF
    return GPIO_OK;
}



