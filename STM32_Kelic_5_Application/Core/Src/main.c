#include "main.h"
#include "UART_Data_Manager.h"
#include "InitSystemPeripheral.h"
#include "FlashSTM32.h"
#include "SCB_Base.h"


DataManager_t Data_Manager = {	.modeActive = NORMAL_MODE,
															.SetAuto = TURN_ON_AUTO};


UART_HandleTypeDef huart1;

typedef enum {

    RST_HARDWARE = 0,
    RST_BOOTLOADER

}TypeRST_t;

typedef enum {
  APP_1_ENABLE = 1,
  APP_2_ENABLE = 2
}Select_App_t;

#define FIRMWARE_FLAG_ADDRESS   0x0800FC00

void USART1_IRQHandler(void) {

  uint8_t data_rx = USART1_HANDMADE->UART_DR;
  ReciveUART(data_rx);
		
}

void SysTick_Handler(void)
{
	Systick_ms_inc();
}


int main(void)
{
	HAL_Init();
  InitSystemPeripheral(&Data_Manager);
  InitDataManager(&Data_Manager);

  while (1)
  {


		if(Data_Manager.modeActive == NORMAL_MODE){
      UART_Controller();
			
		} else {
			Flash_ErasePage(FIRMWARE_FLAG_ADDRESS);
      Flash_WriteHalfWord(FIRMWARE_FLAG_ADDRESS,(APP_1_ENABLE) | (RST_BOOTLOADER << 8));
			NVIC_SystemReset_handmade() ;
		}
		
		
  }
  
}
