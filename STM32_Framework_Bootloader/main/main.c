#include "Bootloader.h"


Data_Process_t DataToOTA = {0} ;

void USART1_IRQHandler(void) {

    DataToOTA.eachByteData = USART1_HANDMADE->UART_DR;
    receiveDataToOTA(&DataToOTA);
}

int main(void)
{
	
  InitBootLoader(&DataToOTA);
  while (1)
  {
    BootLoader();
  }
}

