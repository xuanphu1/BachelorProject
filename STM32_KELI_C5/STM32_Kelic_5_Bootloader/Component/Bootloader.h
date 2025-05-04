#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__
#include "HexFileProcessing.h"

#define _VTOR (*((volatile uint32_t *)0xE000ED08))


#define PAGE_MEMORY_EACH_APP 28

// Capcity of Bootloader is 8KB
#define APP_1_START_ADDRESS 0x08002000 // Page 8 -> Page 36
#define APP_2_START_ADDRESS 0x08009000 // Page 36 -> Page 63



typedef enum {
    APP_1_ENABLE = 1,
    APP_2_ENABLE = 2
}Select_App_t;

void InitBootLoader(Data_Process_t *DataOTA);
void BootLoader(void);

void Jump_To_Application(uint32_t AppStartAddress);





#endif