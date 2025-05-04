#include "Bootloader.h"


void Jump_To_Application(uint32_t AppStartAddress)
{
    // 1. Lấy giá trị Stack Pointer từ vector table của ứng dụng
    uint32_t topOfMainStack = *(volatile uint32_t*)AppStartAddress;

    // 2. Lấy địa chỉ Reset_Handler của ứng dụng
    void (*App_Reset_Handler)(void) = 
        (void (*)(void))(*(volatile uint32_t*)(AppStartAddress + 4));

    // 3. Vô hiệu hóa tất cả ngắt

    // 4. Tắt SysTick
    SYSTICK_HANDMADE->SYST_CSR = 0;
    SYSTICK_HANDMADE->SYST_CVR = 0;
    SYSTICK_HANDMADE->SYST_RVR = 0;

    // 5. Xóa pending fault
    *((volatile uint32_t *)SHCSR_Handmade) &= ~((1UL << 16) | (1UL << 17) | (1UL << 18));

    // 6. Gọi HAL_DeInit

    RCC_DeInit();


    // 7. Set lại Stack Pointer (MSP)
    __set_MSP(topOfMainStack);

    // 8. Gán lại bảng vector
    _VTOR = AppStartAddress;


    // 10. Nhảy vào ứng dụng
    App_Reset_Handler();
}
