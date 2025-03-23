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
#include "UART_Data_Manager.h"
#include "Bootloader.h"
#include "InitSystemPeripheral.h"


DataManager_t DataManager = {	.modeActive = NORMAL_MODE,
															.SetAuto = TURN_ON_AUTO};


UART_HandleTypeDef huart1;


void USART1_IRQHandler(void) {

  uint8_t data_rx = USART1_HANDMADE->UART_DR;
  ReciveUART(data_rx);
		
}


int main(void)
{
	
  InitSystemPeripheral();
  InitDataManager(&DataManager);
	
  while (1)
  {


		if(DataManager.modeActive == NORMAL_MODE){
      UART_Controller();
		} else {
      Jump_To_Application(BOOTLOADER_ADDRESS);
		}
		
		
  }
  
}
