#include "Flash_Handmade.h"



FLASH_Error_t Flash_AdjustForCLK(uint32_t Frequency){

   // while (CHECK_BUSY);
    // 1. Cấu hình Half Cycle Access
    if (Frequency <= 8000000)   
    {
        FLASH_HANDMADE->FLASH_ACR |= (1 << 3); // Enable Half Cycle Access
    }
    else
    {
        FLASH_HANDMADE->FLASH_ACR &= ~(1 << 3); // Disable Half Cycle Access
    }

    // 2. Cấu hình Prefetch Buffer
    if (Frequency > 24000000) {
        FLASH_HANDMADE->FLASH_ACR |= (1 << 4); // Enable Prefetch Buffer
    }

    // 3. Cấu hình Latency (Wait States)
    FLASH_HANDMADE->FLASH_ACR &= ~0x7; // Xóa các bit latency cũ

    if(Frequency <= 24000000){
        FLASH_HANDMADE->FLASH_ACR |= (0x0 << 0); // 0 Wait State
    }
    else if(Frequency > 24000000 && Frequency <= 48000000){
        FLASH_HANDMADE->FLASH_ACR |= (0x1 << 0); // 1 Wait State
    }
    else if(Frequency > 48000000 && Frequency <= 72000000){
        FLASH_HANDMADE->FLASH_ACR |= (0x2 << 0); // 2 Wait States
    }
    return FLASH_OK;
}

// Hàm mở khóa Flash memory
void Flash_Unlock(void)
{
    // Mở khóa Flash memory để thực hiện các thao tác ghi
    FLASH_HANDMADE->FLASH_KEYR = KEY_1;  // Ghi KEY1 vào FLASH_KEYR
    FLASH_HANDMADE->FLASH_KEYR = KEY_2;  // Ghi KEY2 vào FLASH_KEYR
}

// Hàm khóa Flash memory
void Flash_Lock(void)
{
    // Khóa lại Flash để ngừng các thao tác ghi
    FLASH_HANDMADE->FLASH_CR |= FLASH_CR_LOCK_HANDMADE;
}

void Flash_ErasePage(uint32_t pageAddress)
{
    // Chờ cho đến khi không còn thao tác Flash nào đang diễn ra
    while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE);

    // Mở khóa Flash memory
    Flash_Unlock();

    // Đặt bit PER trong FLASH_CR để kích hoạt chế độ xóa trang
    FLASH_HANDMADE->FLASH_CR |= FLASH_CR_PER_HANDMADE;

    // Đặt địa chỉ của trang cần xóa vào FLASH_AR
    FLASH_HANDMADE->FLASH_AR = pageAddress;

    // Đặt bit STRT trong FLASH_CR để bắt đầu thao tác xóa
    FLASH_HANDMADE->FLASH_CR |= FLASH_CR_STRT_HANDMADE;

    // Chờ cho đến khi thao tác xóa hoàn tất
    while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE);  // Chờ cho đến khi Flash không còn bận

    // Kiểm tra lỗi xóa
    if (FLASH_HANDMADE->FLASH_SR & FLASH_SR_PGERR_HANDMADE)
    {
        // Nếu có lỗi, xóa cờ PGERR và xử lý lỗi
        FLASH_HANDMADE->FLASH_SR = FLASH_SR_PGERR_HANDMADE;  // Xóa lỗi PGERR
    }

    // Kiểm tra cờ EOP (End of Operation) để xác nhận xóa hoàn tất
    if (FLASH_HANDMADE->FLASH_SR & FLASH_SR_EOP_HANDMADE)
    {
        // Nếu thao tác xóa hoàn tất, xóa cờ EOP
        FLASH_HANDMADE->FLASH_SR = FLASH_SR_EOP_HANDMADE;
    }

    // Khóa lại Flash memory
    Flash_Lock();
}

// Hàm ghi dữ liệu vào Flash
void Flash_Write(uint32_t address, uint32_t data)
{
    // Chờ cho đến khi không còn thao tác Flash nào đang diễn ra
    while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE); // Chờ cho đến khi Flash không còn bận

    // Mở khóa Flash memory
    Flash_Unlock();

    // Đặt bit PG trong FLASH_CR để kích hoạt chế độ ghi
    FLASH_HANDMADE->FLASH_CR |= FLASH_CR_PG_HANDMADE;

    // Ghi dữ liệu vào địa chỉ Flash
    *(volatile uint32_t*)address = data;

    // Chờ cho đến khi thao tác ghi hoàn tất
    while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE); // Chờ cho đến khi Flash không còn bận

    // Kiểm tra lỗi ghi
    if (FLASH_HANDMADE->FLASH_SR & FLASH_SR_PGERR_HANDMADE)
    {
        // Nếu có lỗi, xóa cờ PGERR và xử lý lỗi
        FLASH_HANDMADE->FLASH_SR = FLASH_SR_PGERR_HANDMADE;  // Xóa lỗi PGERR
    }

    // Kiểm tra cờ EOP (End of Operation)
    if (FLASH_HANDMADE->FLASH_SR & FLASH_SR_EOP_HANDMADE)
    {
        // Nếu thao tác ghi hoàn tất (End of Operation), xóa cờ EOP
        FLASH_HANDMADE->FLASH_SR = FLASH_SR_EOP_HANDMADE;  // Xóa cờ EOP
    }

    // Xóa cờ lỗi và khóa lại Flash memory
    FLASH_HANDMADE->FLASH_SR = FLASH_SR_EOP_HANDMADE | FLASH_SR_PGERR_HANDMADE;  // Xóa cờ EOP và PGERR
    Flash_Lock();
}

// Hàm ghi 1 byte vào Flash memory
// void Flash_WriteByte(uint32_t address, uint8_t data)
// {
//     // Chờ cho đến khi không còn thao tác Flash nào đang diễn ra
//     while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE);

//     // Mở khóa Flash memory
//     Flash_Unlock();

//     // Đặt bit PG trong FLASH_CR để kích hoạt chế độ ghi
//     FLASH_HANDMADE->FLASH_CR |= FLASH_CR_PG_HANDMADE;

//     // Ghi dữ liệu (1 byte) vào địa chỉ Flash
//     *(volatile uint8_t*)address = data;

//     // Chờ cho đến khi thao tác ghi hoàn tất
//     while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE);

//     // Kiểm tra lỗi ghi
//     if (FLASH_HANDMADE->FLASH_SR & FLASH_SR_PGERR_HANDMADE)
//     {
//         // Xử lý lỗi nếu có
//         FLASH_HANDMADE->FLASH_SR = FLASH_SR_PGERR_HANDMADE; // Xóa lỗi
//     }

//     // Xóa cờ lỗi và khóa lại Flash memory
//     FLASH_HANDMADE->FLASH_SR = FLASH_SR_EOP_HANDMADE | FLASH_SR_PGERR_HANDMADE;
//     Flash_Lock();
// }

// Hàm ghi 2 byte vào Flash memory
void Flash_WriteHalfWord(uint32_t address, uint16_t data)
{
    // Chờ cho đến khi không còn thao tác Flash nào đang diễn ra
    while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE);

    // Mở khóa Flash memory
    Flash_Unlock();

    // Đặt bit PG trong FLASH_CR để kích hoạt chế độ ghi
    FLASH_HANDMADE->FLASH_CR |= FLASH_CR_PG_HANDMADE;

    // Ghi dữ liệu (2 byte) vào địa chỉ Flash
    *(volatile uint16_t*)address = data;

    // Chờ cho đến khi thao tác ghi hoàn tất
    while (FLASH_HANDMADE->FLASH_SR & FLASH_SR_BSY_HANDMADE);

    // Kiểm tra lỗi ghi
    if (FLASH_HANDMADE->FLASH_SR & FLASH_SR_PGERR_HANDMADE)
    {
        // Xử lý lỗi nếu có
        FLASH_HANDMADE->FLASH_SR = FLASH_SR_PGERR_HANDMADE; // Xóa lỗi
    }

    // Xóa cờ lỗi và khóa lại Flash memory
    FLASH_HANDMADE->FLASH_SR = FLASH_SR_EOP_HANDMADE | FLASH_SR_PGERR_HANDMADE;
    Flash_Lock();
}
