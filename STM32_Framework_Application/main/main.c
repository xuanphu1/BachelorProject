#include "UART_Data_Manager.h"
#include "InitSystemPeripheral.h"
#include "SCB_Base.h"


DataManager_t Data_Manager = {	.modeActive = NORMAL_MODE,
                                .SetAuto = TURN_ON_AUTO};

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


		if(Data_Manager.modeActive == NORMAL_MODE){
            UART_Controller();
			
		} else {
			NVIC_SystemReset() ;
		}
		
		
  }
  
}
