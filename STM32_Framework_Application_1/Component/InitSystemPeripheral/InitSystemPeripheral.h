#ifndef __INIT_SYSTEM_H__
#define __INIT_SYSTEM_H__
#include "stdio.h"
#include "ADC_Handmade.h"
#include "DMA_Handmade.h"
#include "Flash_Handmade.h"
#include "GPIO_Handmade.h"
#include "NVIC_Handmade.h"
#include "RCC_Handmade.h"
#include "Systick_Handmade.h"
#include "Timer_Handmade.h"
#include "UART_Handmade.h"
#include "UART_Data_Manager.h"



void InitSystemPeripheral(DataManager_t *_DataManager);





#endif






