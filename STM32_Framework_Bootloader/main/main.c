#include "main.h"

void USART1_IRQHandler(void) {
  DataToOTA.eachByteData = USART1_HANDMADE->UART_DR;
  receiveDataToOTA(&DataToOTA);
}

int main(void)
{
	
  InitBootLoader(&DataToOTA);
  while (1)
  {
    if(CHECK_RST_HARDWARE) DataToOTA.StatusProcess = 1;
    BootLoader();
  }
}

