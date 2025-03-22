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
#include "Config.h"
#include "HexFileProcessing.h"


DataManager_t DataManager = {	.modeActive = NORMAL_MODE,
                                .SetAuto = TURN_ON_AUTO};

Data_Process_t DataToOTA ;
uint16_t ADC_Buffer[2];


void USART1_IRQHandler(void) {
	
	if(DataManager.modeActive == NORMAL_MODE){
		uint8_t data_rx = USART1_HANDMADE->UART_DR;
		ReciveUART(&DataManager,data_rx);
	} else {
		DataToOTA.eachByteData = USART1_HANDMADE->UART_DR;
		receiveDataToOTA(&DataToOTA);
	}
		
}


Custom_USART_Config_t uartConfigDefault = {
    .usartEnable = Custom_UE_ENABLE,
    .wordLength = Custom_M_8BIT,
    .stopBits = Custom_STOP_1,
    .baudUART = Custom_Baud_115200,
};

SysTick_Config_t SysTickConfigDefault = {
    .EnableCounter = SYST_CSR_COUNTFLAG_YES,
    .Generate_interrupt = SYST_CSR_TICKINT_DISABLE,
    .SysTick_Source = SYST_CSR_CLKSOURCE_EXTERNAL,
    .ValueInitReload = 0 
};

ADC_Config_t adcConfig_2_PinADC = {
    .RegularSequence = {CUSTOM_ADC_CHANNEL_8, CUSTOM_ADC_CHANNEL_9},  // Ch?n 2 kênh (PA0 và PA1)
    .num_of_conversions = 2,
    .conversion_mode = CONTINUOUS_CONVERSION,
    .sample_time = SAMPLE_239_5_CYCLES,  // Ch?n th?i gian l?y m?u thích h?p
    .dma_mode = DMA_ENABLE,
    .scan_mode = SCAN_ENABLE
};

DMA_Config_t dmaADC_2_Pin = {
    .Channel = DMA_CHANNEL_1, // DMA1 Channel 1
    .Priority = DMA_HIGH_PRIORITY,
    .PeripheralIncrement = DISABLE_DMA_PINC,
    .MemoryIncrement = ENABLE_DMA_MINC,
    .PeripheralSize = DMA_PSIZE_16BIT,
    .MemorySize = DMA_MSIZE_16BIT,
    .CircularMode = DMA_CIRC_ENABLE, // L?p vô h?n
    .Direction = DMA_DIR_PERIPH_TO_MEM,
    .TransferErrorInt = DMA_TEIE_DISABLE,
    .HalfTransferInt = DMA_HTIE_DISABLE,
    .TransferCompleteInt = DMA_TCIE_DISABLE,
    .PeripheralAddress = (uint32_t)&ADC1_HANDMADE->ADC_DR, // Ð?c t? ADC
    .MemoryAddress = (uint32_t)ADC_Buffer,    // Luu vào m?ng
    .NumData = 2 // Ð?c 16 m?u ADC tru?c khi d?ng (ho?c reset n?u Circular Mode)
};

RCC_config_t rccconfigDefault ={
    .source_clock = HSE_CLOCK,
    .frequency = FREQ_72MHZ
};

TIM_Config_t PWMconfig = {
    .Timer = TIMER_2,
    .ValueCount = 0,
    .ValueAutoReload = 1000,
    .DutyCycle = 100,
    .DesiredFrequency = 1000000UL,
    .autoReloadPreload = Custom_ARPE_BUFFERED,
    .counterEnable = Custom_CEN_ON
};

GPIO_config_t GPIO_PWM = {
    .port = Port_A,
    .pin = PIN_0,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_10 // Alternate Function Push-Pull
};

GPIO_config_t LED = {
		.port = Port_C,
    .pin = PIN_13,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_00 // Alternate Function Push-Pull
};
int main(void)
{

	init_RCC(&rccconfigDefault);
	InitGPIO_Control_Device();
	SysTick_Init(&SysTickConfigDefault);
	UARTInit(&uartConfigDefault);
	EnableInterrupt_RX_UARTx(UART_1);
	InitGPIO(&LED);
    WritePin(Port_C,PIN_13,1);
	//Flash_ErasePage(0x08008000);
  while (1)
  {
		if (DataManager.modeActive == NORMAL_MODE){
				getDataSensor_ControlDevice(&DataManager);
				InitDataToESP32(&DataManager);
				TransmitDataUART(UART_1,(uint8_t*)&DataManager.DataToESP32,strlen_custom(DataManager.DataToESP32));
				WritePin(Port_C,PIN_13,0);
				Delay_SysTick(100);
				WritePin(Port_C,PIN_13,1);
				Delay_SysTick(3000);
		} else {
				if (DataToOTA.Flag_Data_Full_Line){
				LoadDataToFlash(&DataToOTA);
				DataToOTA.Flag_Data_Full_Line = 0;
				}
				if(DataToOTA.StatusProcess == 1) DataManager.modeActive = NORMAL_MODE;
				// Will Update
		}
		
		
  }
  
}
