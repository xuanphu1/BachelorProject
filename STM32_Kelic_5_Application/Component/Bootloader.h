#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__
#include "stdio.h"
#include "Systick_Handmade.h"
#include "stm32f1xx_hal.h"

#define BOOTLOADER_ADDRESS  0x08000000

#define _VTOR (*((volatile uint32_t *)0xE000ED08))

#define SCB_BASE_HANDMADE            	(0xE000E000UL)  
#define SHCSR_Handmade      			(SCB_BASE_HANDMADE + 0x24)            //*!< Offset: 0x024



// #define ADDR_APP_PROGRAM 0x08000000
// typedef void (*run_app_handler)(void);
// run_app_handler run_app;
// void run_app_program()
// {
// /* Turn off Peripheral, Clear Interrupt Flag*/
// HAL_RCC_DeInit();
// /* Clear Pending Interrupt Request, turn off System Tick*/
// HAL_DeInit(); /* Turn off fault harder*/
// SCB->SHCSR &= ~(    SCB_SHCSR_USGFAULTENA_Msk |
//                     SCB_SHCSR_BUSFAULTENA_Msk |
//                     SCB_SHCSR_MEMFAULTENA_Msk ) ;
// /* Set Main Stack Pointer*/
// __set_MSP(*((volatile uint32_t*) ADDR_APP_PROGRAM));
// run_app = (run_app_handler)*((volatile uint32_t*) (ADDR_APP_PROGRAM + 4));
// run_app();
// }

void Jump_To_Application(uint32_t AppStartAddress);





#endif