#ifndef FLASH_HANDMADE_H
#define FLASH_HANDMADE_H
#include "stdint.h"
#include "NVIC_Handmade.h"

// Struct to represent the Flash registers
typedef struct 
{
    volatile uint32_t FLASH_ACR;
    volatile uint32_t FLASH_KEYR;
    volatile uint32_t FLASH_OPTKEYR;
    volatile uint32_t FLASH_SR;
    volatile uint32_t FLASH_CR;
    volatile uint32_t FLASH_AR;
    volatile uint32_t FLASH_OBR;
    volatile uint32_t FLASH_WRPR;
} FLASH_HANDMADE_t;

// Base address of Flash registers
#define FLASH_HANDMADE_BASE      0x40022000U
#define FLASH_HANDMADE           ((volatile FLASH_HANDMADE_t *) FLASH_HANDMADE_BASE)

#define KEY_1 0x45670123
#define KEY_2 0xCDEF89AB

#define FLASH_PAGE_SIZE 1024U
// Error enumeration for Flash operations
typedef enum {
    FLASH_OK = 0,
    FLASH_NOT_OK = 1
} FLASH_Error_t;


// Các bit trong FLASH_CR (Control Register)
#define FLASH_CR_LOCK_HANDMADE        (1 << 7)     // Lock bit
#define FLASH_CR_PG_HANDMADE          (1 << 0)      // Programming bit
#define FLASH_CR_PER_HANDMADE         (1 << 1)      // Page Erase bit
#define FLASH_CR_STRT_HANDMADE        (1 << 6)      // Start bit for operations
#define  FLASH_SR_WRPRTERR_HANDMADE   (1 << 4)
// Các bit trong FLASH_SR (Status Register)
#define FLASH_SR_BSY_HANDMADE         (1 << 0)     // Busy flag
#define FLASH_SR_EOP_HANDMADE         (1 << 5)      // End of Operation flag
#define FLASH_SR_PGERR_HANDMADE       (1 << 2)      // Programming error flag

// Hàm mở khóa Flash memory
void Flash_Unlock(void);

// Hàm khóa Flash memory
void Flash_Lock(void);
// Hàm ghi 16-bit vào Flash memory
void Flash_Write(uint32_t address, uint32_t data);
// Hàm xóa một trang Flash
FLASH_Error_t Flash_ErasePage(uint32_t pageAddress);
void Flash_WriteHalfWord(uint32_t address, uint16_t data);
FLASH_Error_t Flash_AdjustForCLK(uint32_t Frequency);
FLASH_Error_t Flash_EraseRange(uint32_t startAddress, uint8_t pageCount);

#endif // FLASH_HANDMADE_H  
