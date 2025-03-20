#ifndef FLASH_HANDMADE_H
#define FLASH_HANDMADE_H
#include "stdint.h"


typedef struct 
{
    uint32_t ACR;
    uint32_t KEYR;
    uint32_t OPTKEYR;
    uint32_t SR;
    uint32_t CR;
    uint32_t AR;
    uint32_t RESERVED;
    uint32_t OBR;
    uint32_t WRPR;

}FLASH_HANDMADE_t;

typedef enum {
    FLASH_OK = 0,
    FLASH_NOT_OK = 1
} FLASH_Error_t;

#define FLASH_HANDMADE_BASE      0x40022000
#define FLASH_HANDMADE          ((FLASH_HANDMADE_t *) FLASH_HANDMADE_BASE)


FLASH_Error_t Flash_AdjustForCLK(uint32_t Frequency);

#endif // FLASH_HANDMADE_H  


