#include "Systick_Handmade.h"

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
    SYSTICK_HANDMADE->SYST_RVR = systickConfig->ValueInitReload - 1;

    // Reset bộ đếm
    SYSTICK_HANDMADE->SYST_CVR = 0;

    // Bật SysTick nếu được yêu cầu
    if (systickConfig->EnableCounter == SYST_CSR_COUNTFLAG_YES) {
        SYSTICK_HANDMADE->SYST_CSR |= (1 << 0);
    }
}

// Hàm Delay chính xác
void Delay_SysTick(uint32_t value_ms) {
    if (value_ms == 0) return; // Tránh lỗi nếu delay = 0

    // Tính số ticks cho mỗi 1ms
    uint32_t ticks_per_ms = (getFrequencyRCC() / 8) / 1000;

    // Đặt giá trị reload cho mỗi lần đếm 1ms
    SYSTICK_HANDMADE->SYST_RVR = ticks_per_ms - 1;
    SYSTICK_HANDMADE->SYST_CVR = 0; // Reset bộ đếm

    // Bật SysTick nhưng không bật ngắt
    SYSTICK_HANDMADE->SYST_CSR |= SYST_CSR_ENABLE_ENABLE;

    // Đếm value_ms lần, mỗi lần là 1ms
    for (uint32_t i = 0; i < value_ms; i++) {
        while (!(SYSTICK_HANDMADE->SYST_CSR & (1 << 16))){
            

        } // Chờ COUNTFLAG = 1
        SYSTICK_HANDMADE->SYST_CVR = 0; // Reset counter
    }

    // Tắt SysTick sau khi hoàn thành
    SYSTICK_HANDMADE->SYST_CSR = 0;
}


