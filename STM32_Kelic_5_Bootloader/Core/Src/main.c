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
GPIO_config_t config_input = {
	.port = Port_A,
	.pin = PIN_3,
	.mode = INPUT_MODE,
	.cnf_mode = CNF_MODE_10
};
uint8_t jump;
int main(void)
{
	
		HAL_Init();
		InitBootLoader(&DataToOTA); 
		InitGPIO(&config_input);
		
  while (1)
  {
//		jump = ReadPin(Port_A,PIN_3);
//		//WritePin(Port_C,PIN_13,0);
//		if(jump == 1){
//			Jump_To_Application(0x08002000);
//			//WritePin(Port_C,PIN_13,1);
//		}
//		
    BootLoader();
    //Delay_SysTick(50);
  }
}

