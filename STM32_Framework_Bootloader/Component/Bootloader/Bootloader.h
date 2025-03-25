#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__
#include "HexFileProcessing.h"
#include "SCB_Base.h"

typedef enum {
    APP_1_ENABLE = 1,
    APP_2_ENABLE = 2
}Select_App_t;

typedef enum {

    RST_HARDWARE = 0,
    RST_BOOTLOADER

}TypeRST_t;

#define __set_MSP(addr)  __asm__ volatile ("MSR msp, %0" :: "r" (addr) : )

#define PAGE_MEMORY_EACH_APP 27

// Capcity of Bootloader is 8KB
#define APP_1_START_ADDRESS 0x08002000 // Page 8 -> Page 36
#define APP_2_START_ADDRESS 0x08009000 // Page 36 -> Page 63

#define FIRMWARE_FLAG_ADDRESS 0x0800FC00




void InitBootLoader(Data_Process_t *DataOTA);
void BootLoader(void);

void Jump_To_Application(uint32_t AppStartAddress);


#endif