#include "main.h"

void USART1_IRQHandler(void) {

  uint8_t data_rx = USART1_HANDMADE->UART_DR;
  ReciveUART(data_rx);
		
}
int main(void)
{
  InitSystemPeripheral();
  InitDataManager(&Data_Manager);
	
  while (1)
  {
		if(Data_Manager.modeActive == NORMAL_MODE)
    {
      UART_Controller();
		} else if (Data_Manager.modeActive == OTA_MODE)
    { 
			Flash_ErasePage(FIRMWARE_FLAG_ADDRESS);
      Flash_WriteHalfWord(FIRMWARE_FLAG_ADDRESS,(APP_2_ENABLE) | (RST_BOOTLOADER << 8));
			NVIC_SystemReset() ;
    }
  
  }
}