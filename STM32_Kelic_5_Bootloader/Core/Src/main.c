/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Bootloader.h"


Data_Process_t DataToOTA ;

void USART1_IRQHandler(void) {

    DataToOTA.eachByteData = USART1_HANDMADE->UART_DR;
    receiveDataToOTA(&DataToOTA);
}

int main(void)
{

		HAL_Init();
		InitBootLoader(&DataToOTA); 

  while (1)
  {
    BootLoader();
    Delay_SysTick(50);
  }
}

