#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__
#include "stdio.h"
#include "Systick_Handmade.h"
#include "stm32f1xx_hal.h"

#define BOOTLOADER_ADDRESS  0x08000000

#define _VTOR (*((volatile uint32_t *)0xE000ED08))

#define SCB_BASE_HANDMADE            	(0xE000E000UL)  
#define SHCSR_Handmade      					(SCB_BASE_HANDMADE + 0x24)            //*!< Offset: 0x024

void Jump_To_Application(uint32_t AppStartAddress);






#endif












