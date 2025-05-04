#include "main.h"
#include "UART_Data_Manager.h"
#include "InitSystemPeripheral.h"
#include "SCB_Base.h"



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
