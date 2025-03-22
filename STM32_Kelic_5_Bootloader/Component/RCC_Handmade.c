#include "RCC_Handmade.h"

FREQ_Frequency_t Frequency_RCC;
PPRE_Prescaler_t PPRE1_Prescaler;
PPRE_Prescaler_t PPRE2_Prescaler;
HPRE_Prescaler_t HPRE_Prescaler;

RCCError_t Enable_Clock_RCC_APB2(APB2_Peripheral_Clock Peripheral_CLK){
    // Kiểm tra nếu clock đã được bật, nếu chưa thì mới bật
    if (!(RCC_HANDMADE->RCC_APB2ENR & (1U << Peripheral_CLK))) {
        RCC_HANDMADE->RCC_APB2ENR |= (1U << Peripheral_CLK);
    }
    return RCC_OK;
}

RCCError_t Enable_Clock_RCC_APB1(APB1_Peripheral_Clock Peripheral_CLK) {
    // Kiểm tra nếu clock đã được bật, nếu chưa thì mới bật
    if (!(RCC_HANDMADE->RCC_APB1ENR & (1U << Peripheral_CLK))) {
        RCC_HANDMADE->RCC_APB1ENR |= (1U << Peripheral_CLK);
    }
    return RCC_OK;
}

RCCError_t Enable_Clock_RCC_AHB(AHB_Peripheral_Clock Peripheral_CLK) {
    // Kiểm tra nếu clock đã được bật, nếu chưa thì mới bật
    if (!(RCC_HANDMADE->RCC_AHBENR & (1U << Peripheral_CLK))) {
        RCC_HANDMADE->RCC_AHBENR |= (1U << Peripheral_CLK);
    }
    return RCC_OK;
}



RCCError_t Select_Prescaler_RCC(RCC_ClockPrescaler_t *Prescaler, RCC_Prescaler_t Prescaler_type){

    if (!Prescaler) return RCC_ERROR_INVALID_PARAM; // Kiểm tra con trỏ null

    switch (Prescaler_type) {
        case AHB_Prescaler:
            if (Prescaler->HPRE_Prescaler > HPRE_CLOCK_DIV_512) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~(0xF << 4); // Xóa HPRE
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->HPRE_Prescaler << 4); // Cấu hình bộ chia tần
            HPRE_Prescaler = Prescaler->HPRE_Prescaler;
            break;

        case APB1_Prescaler:
            if (Prescaler->PPRE1_Prescaler > PPRE_CLOCK_DIV_16) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~(0x7 << 8); // Xóa PPRE1
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->PPRE1_Prescaler << 8); // Cấu hình bộ chia tần
            PPRE1_Prescaler = Prescaler->PPRE1_Prescaler;
            break;

        case APB2_Prescaler:
            if (Prescaler->PPRE2_Prescaler > PPRE_CLOCK_DIV_16) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~(0x7 << 11); // Xóa PPRE2
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->PPRE2_Prescaler << 11); // Cấu hình bộ chia tần
            PPRE2_Prescaler = Prescaler->PPRE2_Prescaler;
            break;

        case ADC_Prescaler:
            if (Prescaler->ADC_Prescaler > ADC_CLOCK_DIV_8) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~(0x3 << 14); // Xóa ADCPRE
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->ADC_Prescaler << 14); // Cấu hình bộ chia tần
            break;

        default:
            return RCC_ERROR_INVALID_PARAM; // Trường hợp không hợp lệ
    }
    
    
    
    return RCC_OK;
}



RCCError_t Select_Sources_Clock(Source_Clock_t Source_Clock){

    if (Source_Clock != HSI_CLOCK && Source_Clock != HSE_CLOCK) {
        return RCC_ERROR_INVALID_PARAM; // Nguồn clock không hợp lệ
    }

    if (Source_Clock == HSI_CLOCK) {
        #ifndef HSE_REQUIRED_FOR_72MHZ
        #error "HSE requires an external crystal (e.g., 8MHz) connected to OSC_IN/OSC_OUT"
        #endif
        RCC_HANDMADE->RCC_CR |= (ENABLE_RCC << 0); // Enable HSI
        while (!((RCC_HANDMADE->RCC_CR >> 1) & 0x1) ); // Wait for HSI ready
    }
    else if (Source_Clock == HSE_CLOCK)
    {
        Enable_Clock_RCC_APB2(IOPD_EN_CLK);
        RCC_HANDMADE->RCC_CR |= (ENABLE_RCC << 16); // Enable HSE
        while (!((RCC_HANDMADE->RCC_CR >> 17) & 0x1) ); // Wait for HSE ready
    }
    return RCC_OK;
}

RCCError_t Select_Frequency_CLK(FREQ_Frequency_t Frequency_clk){

    if (Frequency_clk > FREQ_72MHZ) {
        return RCC_ERROR_INVALID_PARAM; // Vượt quá tần số tối đa
    }

    uint32_t pll_input_freq;

    // Kiểm tra nguồn clock hiện tại (đã bật từ trước)
    if((RCC_HANDMADE->RCC_CR >> 17) & 0x1) {
        pll_input_freq = 8000000; // HSE là 8MHz
        RCC_HANDMADE->RCC_CFGR |= (1 << 16); // PLLSRC = HSE
    }
    else if((RCC_HANDMADE->RCC_CR >> 1) & 0x1){
        pll_input_freq = 4000000; // HSI là 8MHz chia 2 còn 4MHz
        RCC_HANDMADE->RCC_CFGR &= ~(1 << 16); // PLLSRC = HSI/2
    } else {
        return RCC_ERROR_INVALID_PARAM; // Không có nguồn clock hợp lệ, thoát
    }

     // Cấu hình bộ chia bus giống HAL
     RCC_ClockPrescaler_t Clock_persaler = {
        .ADC_Prescaler = ADC_CLOCK_DIV_2,
        .PPRE1_Prescaler = PPRE_CLOCK_DIV_1,
        .PPRE2_Prescaler = PPRE_CLOCK_DIV_1,    
        .HPRE_Prescaler = HPRE_CLOCK_DIV_1
     };

    if (Frequency_clk > FREQ_36MHZ) Clock_persaler.PPRE1_Prescaler = PPRE_CLOCK_DIV_2; // AHB = SYSCLK/2
    if (Frequency_clk > FREQ_12MHZ) Clock_persaler.ADC_Prescaler = ADC_CLOCK_DIV_6; // ADC = PCLK2/6
        
    Select_Prescaler_RCC(&Clock_persaler, APB1_Prescaler);
    Select_Prescaler_RCC(&Clock_persaler, ADC_Prescaler);
    // Tính PLL multiplier
    uint32_t pllmul = Frequency_clk / pll_input_freq;
    if(pllmul < 2 || pllmul > 16) return RCC_ERROR_INVALID_PARAM; // PLL multiplier phải trong khoảng 2-16

    // Cấu hình PLL multiplier
    RCC_HANDMADE->RCC_CFGR &= ~(0xF << 18);            // Clear PLLMUL
    RCC_HANDMADE->RCC_CFGR |= ((pllmul - 2) << 18);    // Set PLLMUL

    // Bật PLL và chờ PLL sẵn sàng
    RCC_HANDMADE->RCC_CR |= (1 << 24);                 // PLLON = 1   
    uint32_t timeout = 10000;
    while (!(RCC_HANDMADE->RCC_CR & (1 << 25)) && timeout--) { // Chờ PLLRDY
        if (timeout == 0) return RCCError_tIMEOUT; // PLL không sẵn sàng
    }
    // Chọn PLL làm SYSCLK
    RCC_HANDMADE->RCC_CFGR &= ~0x3;                    // Clear SW bits
    RCC_HANDMADE->RCC_CFGR |= 0x2;                     // SW = PLL

    // Chờ đến khi PLL được chọn làm SYSCLK
    timeout = 10000;
    while (((RCC_HANDMADE->RCC_CFGR >> 2) & 0x3) != 0x2 && timeout--) {
        if (timeout == 0) return RCCError_tIMEOUT; // SYSCLK không chuyển sang PLL
    }

    PPRE1_Prescaler = Clock_persaler.PPRE1_Prescaler;
    PPRE2_Prescaler = Clock_persaler.PPRE2_Prescaler;
    HPRE_Prescaler = Clock_persaler.HPRE_Prescaler;
    return RCC_OK;
}


RCCError_t init_RCC(RCC_config_t *RCC_config){

   if (RCC_config == NULL) return RCC_ERROR_INVALID_PARAM;

    RCCError_t status;
    status = (RCCError_t)Flash_AdjustForCLK(RCC_config->frequency);
    if (status != RCC_OK) goto fallback;

    status = Select_Sources_Clock(RCC_config->source_clock);
    if (status != RCC_OK) goto fallback;

    status = Select_Frequency_CLK(RCC_config->frequency);
    Frequency_RCC = RCC_config->frequency;
    if (status != RCC_OK) goto fallback;

    return RCC_OK;

fallback:
    // Khôi phục về HSI mặc định (8MHz)
    RCC_HANDMADE->RCC_CR |= (ENABLE_RCC << 0);
    uint32_t timeout = 10000;
    while (!((RCC_HANDMADE->RCC_CR >> 1) & 0x1) && timeout--);
    RCC_HANDMADE->RCC_CFGR &= ~0x3; // Chọn HSI làm SYSCLK
    return RCCError_tIMEOUT;

}


FREQ_Frequency_t getFrequencyAHB(void) {
    uint8_t hpre_divider = (HPRE_Prescaler < 8) ? 1 : (2 << (HPRE_Prescaler - 8)); 
    return (FREQ_Frequency_t)(Frequency_RCC / hpre_divider);
}

FREQ_Frequency_t getFrequencyAPB1(void) {
    uint8_t ppre1_divider = (PPRE1_Prescaler < 4) ? 1 : (2 << (PPRE1_Prescaler - 4));
    return (FREQ_Frequency_t)(Frequency_RCC / ppre1_divider);
}

FREQ_Frequency_t getFrequencyAPB2(void) {
    uint8_t ppre2_divider = (PPRE2_Prescaler < 4) ? 1 : (2 << (PPRE2_Prescaler - 4));
    return (FREQ_Frequency_t)(Frequency_RCC / ppre2_divider);
}
FREQ_Frequency_t getFrequencyRCC(void){
    return (FREQ_Frequency_t)(Frequency_RCC);
}


