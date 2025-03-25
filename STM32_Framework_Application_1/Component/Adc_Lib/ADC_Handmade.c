#include "ADC_Handmade.h"

/**
 * @brief Bật clock cho ADC1 và cấu hình bộ chia tần
 * @param prescaler: Bộ chia tần ADC (ADC_CLOCK_DIV_2, ADC_CLOCK_DIV_4, ...)
 * @return ADC_Error_t: Trạng thái thực thi
 */
ADC_Error_t ADC_EnableClock(ClockPrescaler_t prescaler) {
    if (prescaler > CLOCK_ADC_DIV_8) {
        return ADC_ERROR_INVALID_PARAM;
    }

    Enable_Clock_RCC_APB2(ADC1_EN_CLK);
    RCC_ClockPrescaler_t Prescaler_RCC = {
        .ADC_Prescaler = (ClockPrescaler_t)prescaler,
    };
    Select_Prescaler_RCC(&Prescaler_RCC, ADC_Prescaler);

    return ADC_OK;
}

/**
 * @brief Khởi tạo ADC1 với cấu hình người dùng
 * @param adcConfig: Con trỏ tới cấu hình ADC
 * @return ADC_Error_t: Trạng thái thực thi
 */
ADC_Error_t ADC_Init(ADC_Config_t *adcConfig) {
    // Kiểm tra tham số đầu vào
    if (adcConfig == NULL || adcConfig->num_of_conversions == 0 || 
        adcConfig->num_of_conversions > 16 ||
        adcConfig->scan_mode > SCAN_ENABLE ||
        adcConfig->dma_mode > DMA_ENABLE ||
        adcConfig->conversion_mode > CONTINUOUS_CONVERSION ||
        adcConfig->data_align > DATAALIGN_LEFT ||
        adcConfig->external_trigger > EXTERNAL_TRIGGER_ENABLE ||
        adcConfig->interrupt_mode > INTERRUPT_ENABLE ||
        adcConfig->sample_time > SAMPLE_239_5_CYCLES) {
        return ADC_ERROR_INVALID_PARAM;
    }

    // Cấu hình GPIO cho các kênh ADC
    for (uint8_t i = 0; i < adcConfig->num_of_conversions; i++) {
        if (adcConfig->RegularSequence[i] > CUSTOM_ADC_CHANNEL_VREFINT) {
            return ADC_ERROR_INVALID_PARAM;
        }

        Port_t port_adc;
        Pin_gpio_t pin_adc;

        // Xác định port và pin cho từng kênh
        if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_7) {
            port_adc = Port_A;
            pin_adc = (Pin_gpio_t)adcConfig->RegularSequence[i];
        } else if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_9) {
            port_adc = Port_B;
            pin_adc = (Pin_gpio_t)(adcConfig->RegularSequence[i] - 8);
        } else if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_15) {
            port_adc = Port_C;
            pin_adc = (Pin_gpio_t)(adcConfig->RegularSequence[i] - 10);
        } else {
            continue; // Bỏ qua kênh TEMP_SENSOR và VREFINT vì không cần GPIO
        }

        GPIO_config_t config_GPIO = {
            .port = port_adc,
            .pin = pin_adc,
            .mode = INPUT_MODE,
            .cnf_mode = CNF_MODE_00 // Analog mode
        };
        if (InitGPIO(&config_GPIO) != GPIO_OK) {
            return ADC_ERROR_INVALID_PARAM;
        }
    }

    // Bật clock ADC với bộ chia tần từ cấu hình
    if (ADC_EnableClock(adcConfig->clock_prescaler) != ADC_OK) {
        return ADC_ERROR_INVALID_PARAM;
    }

    // Tắt ADC trước khi cấu hình
    ADC1_HANDMADE->ADC_CR2 &= ~(1 << 0);

    // Cấu hình chế độ
    ADC1_HANDMADE->ADC_CR2 |= (adcConfig->conversion_mode << 1); // Single/Continuous
    ADC1_HANDMADE->ADC_CR1 |= (adcConfig->scan_mode << 8);       // Scan mode
    ADC1_HANDMADE->ADC_CR2 |= (adcConfig->dma_mode << 8);        // DMA mode
    ADC1_HANDMADE->ADC_CR2 |= (adcConfig->data_align << 11);     // Data alignment
    ADC1_HANDMADE->ADC_CR2 |= (adcConfig->external_trigger << 20); // External trigger
    ADC1_HANDMADE->ADC_CR1 |= (adcConfig->interrupt_mode << 5);   // EOC interrupt

    // Cấu hình số lượng kênh trong chuỗi
    ADC1_HANDMADE->ADC_SQR1 &= ~(0xF << 20);
    ADC1_HANDMADE->ADC_SQR1 |= ((adcConfig->num_of_conversions - 1) << 20);

    // Cấu hình chuỗi kênh thường xuyên
    for (uint8_t i = 0; i < adcConfig->num_of_conversions; i++) {
        if (i < 6) {
            ADC1_HANDMADE->ADC_SQR3 &= ~(0x1F << (i * 5));
            ADC1_HANDMADE->ADC_SQR3 |= (adcConfig->RegularSequence[i] << (i * 5));
        } else if (i < 12) {
            ADC1_HANDMADE->ADC_SQR2 &= ~(0x1F << ((i - 6) * 5));
            ADC1_HANDMADE->ADC_SQR2 |= (adcConfig->RegularSequence[i] << ((i - 6) * 5));
        } else {
            ADC1_HANDMADE->ADC_SQR1 &= ~(0x1F << ((i - 12) * 5));
            ADC1_HANDMADE->ADC_SQR1 |= (adcConfig->RegularSequence[i] << ((i - 12) * 5));
        }

        // Cấu hình thời gian lấy mẫu
        if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_9) {
            ADC1_HANDMADE->ADC_SMPR2 &= ~(0x7 << (adcConfig->RegularSequence[i] * 3));
            ADC1_HANDMADE->ADC_SMPR2 |= (adcConfig->sample_time << (adcConfig->RegularSequence[i] * 3));
        } else {
            uint8_t offset = adcConfig->RegularSequence[i] - 10;
            ADC1_HANDMADE->ADC_SMPR1 &= ~(0x7 << (offset * 3));
            ADC1_HANDMADE->ADC_SMPR1 |= (adcConfig->sample_time << (offset * 3));
        }
    }

    // Bật ADC và hiệu chuẩn
    ADC1_HANDMADE->ADC_CR2 |= (1 << 0); // Bật ADC lần 1
    for (volatile uint32_t i = 0; i < 1000; i++); // Đợi ổn định
    ADC1_HANDMADE->ADC_CR2 |= (1 << 0); // Bật ADC lần 2

    ADC1_HANDMADE->ADC_CR2 |= (1 << 2); // Bắt đầu hiệu chuẩn
    uint32_t timeout = 10000;
    while ((ADC1_HANDMADE->ADC_CR2 & (1 << 2)) && timeout--) {
        if (timeout == 0) return ADC_ERROR_TIMEOUT;
    }

    return ADC_OK;
}

/**
 * @brief Đọc nhiều kênh ADC không dùng DMA
 * @param adcConfig: Con trỏ tới cấu hình ADC, chứa kết quả
 * @return ADC_Error_t: Trạng thái thực thi
 */
ADC_Error_t ADC_ReadMultiple(ADC_Config_t *adcConfig) {
    if (adcConfig == NULL || adcConfig->num_of_conversions == 0 || 
        adcConfig->dma_mode == DMA_ENABLE) {
        return ADC_ERROR_INVALID_PARAM;
    }

    // Kiểm tra ADC đã bật chưa
    if (!(ADC1_HANDMADE->ADC_CR2 & (1 << 0))) {
        return ADC_ERROR_NOT_INITIALIZED;
    }

    // Bắt đầu chuyển đổi
    ADC1_HANDMADE->ADC_CR2 |= (1 << 22);

    // Đọc dữ liệu cho từng kênh
    for (uint8_t i = 0; i < adcConfig->num_of_conversions; i++) {
        uint32_t timeout = 10000;
        while (!(ADC1_HANDMADE->ADC_SR & (1 << 1)) && timeout--) {
            if (timeout == 0) return ADC_ERROR_TIMEOUT;
        }
        adcConfig->Result_ADC[i] = ADC1_HANDMADE->ADC_DR;
    }

    return ADC_OK;
}


/**
 * @brief Bắt đầu chuyển đổi ADC với DMA
 * @return ADC_Error_t: Trạng thái thực thi
 */
ADC_Error_t ADC_DMA_Start(void) {
    // Kiểm tra ADC đã bật và DMA đã được cấu hình chưa
    if (!(ADC1_HANDMADE->ADC_CR2 & (1 << 0)) || !(ADC1_HANDMADE->ADC_CR2 & (1 << 8))) {
        return ADC_ERROR_NOT_INITIALIZED;
    }

    ADC1_HANDMADE->ADC_CR2 |= (1 << 22); // Bắt đầu chuyển đổi
    return ADC_OK;
}


