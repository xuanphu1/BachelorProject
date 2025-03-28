#include "Systick_Handmade.h"

volatile uint32_t SysTick_ms;


void Systick_ms_inc(void){
	SysTick_ms++;
}

// Hàm khởi tạo SysTick
void SysTick_Init(SysTick_Config_t *systickConfig) {
    // Tắt SysTick trước khi cấu hình
    SYSTICK_HANDMADE->SYST_CSR = 0;

    // Cấu hình nguồn clock
    if (systickConfig->SysTick_Source == SYST_CSR_CLKSOURCE_PROCESSOR) {
        SYSTICK_HANDMADE->SYST_CSR |= (1 << 2); // Chạy theo HCLK
    } else {
        SYSTICK_HANDMADE->SYST_CSR &= ~(1 << 2); // Chạy theo HCLK/8
    }

    // Cấu hình ngắt nếu cần
    if (systickConfig->Generate_interrupt == SYST_CSR_TICKINT_ENABLE) {
        SYSTICK_HANDMADE->SYST_CSR |= (1 << 1);
    } else {
        SYSTICK_HANDMADE->SYST_CSR &= ~(1 << 1);
    }

    // Gán giá trị reload
    SYSTICK_HANDMADE->SYST_RVR = (getFrequencyRCC() / 8) / 1000 - 1;

    // Reset bộ đếm
    SYSTICK_HANDMADE->SYST_CVR = 0;

    // Bật SysTick nếu được yêu cầu
    if (systickConfig->EnableCounter == SYST_CSR_COUNTFLAG_YES) {
        SYSTICK_HANDMADE->SYST_CSR |= (1 << 0);
    }
}

// Hàm Delay chính xác
void Delay_SysTick(uint32_t value_ms) {
  uint32_t SysTick_ms_Start = SysTick_ms;
	while (SysTick_ms - SysTick_ms_Start < value_ms);
}


