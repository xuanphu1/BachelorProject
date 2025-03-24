#include "main.h"
#include "UART_Data_Manager.h"
#include "InitSystemPeripheral.h"


DataManager_t Data_Manager = {	.modeActive = NORMAL_MODE,
															.SetAuto = TURN_ON_AUTO};


UART_HandleTypeDef huart1;


void USART1_IRQHandler(void) {

  uint8_t data_rx = USART1_HANDMADE->UART_DR;
  ReciveUART(data_rx);
		
}
int main(void)
{
	HAL_Init();
  InitSystemPeripheral();
  InitDataManager(&Data_Manager);
	
  while (1)
  {


		if(Data_Manager.modeActive == NORMAL_MODE){
      UART_Controller();
			
		} else {
			NVIC_SystemReset() ;
      //Jump_To_Application(BOOTLOADER_ADDRESS);
		}
		
		
  }
  
}
