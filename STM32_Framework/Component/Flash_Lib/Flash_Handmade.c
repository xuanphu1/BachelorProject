#include "Flash_Handmade.h"

FLASH_Error_t Flash_AdjustForCLK(uint32_t Frequency){

    // 1. Cấu hình Half Cycle Access
    if (Frequency <= 8000000)   
    {
        FLASH_HANDMADE->ACR |= (1 << 3); // Enable Half Cycle Access
    }
    else
    {
        FLASH_HANDMADE->ACR &= ~(1 << 3); // Disable Half Cycle Access
    }

    // 2. Cấu hình Prefetch Buffer
    if (Frequency > 24000000) {
        FLASH_HANDMADE->ACR |= (1 << 4); // Enable Prefetch Buffer
    }

    // 3. Cấu hình Latency (Wait States)
    FLASH_HANDMADE->ACR &= ~0x7; // Xóa các bit latency cũ

    if(Frequency <= 24000000){
        FLASH_HANDMADE->ACR |= (0x0 << 0); // 0 Wait State
    }
    else if(Frequency > 24000000 && Frequency <= 48000000){
        FLASH_HANDMADE->ACR |= (0x1 << 0); // 1 Wait State
    }
    else if(Frequency > 48000000 && Frequency <= 72000000){
        FLASH_HANDMADE->ACR |= (0x2 << 0); // 2 Wait States
    }
    return FLASH_OK;
}
