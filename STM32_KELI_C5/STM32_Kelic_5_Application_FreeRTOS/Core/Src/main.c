#include "main.h"
#include "InitSystemPeripheral.h"


DataManager_t Data_Manager = {	.modeActive = NORMAL_MODE,
															  .SetAuto = TURN_OFF_AUTO};

															
Queue_t *uartQueue;


void SysTick_Handler() {
	Systick_ms_inc();
	TriggerSV_Call_Interrupt();
}



void USART1_IRQHandler(void) {

  uint8_t data_rx = USART1_HANDMADE->UART_DR;
	Queue_Send_FromISR(uartQueue, data_rx);
		
}




void ControlDeviceHandle_Task(){
    uint8_t DataFromQueue;
    uint8_t idxBuff = 0;

    while(1){
        if(Queue_Receive(uartQueue, &DataFromQueue)){
            Data_Manager.UartBuff[idxBuff++] = DataFromQueue;
            if(idxBuff >= LENGTH_FRAME_DATA_CONTROL){
							idxBuff = 0;
							// Clear Queue
							while(isQueueEmpty(uartQueue) != 1) Queue_Receive(uartQueue,&DataFromQueue);
							ControlDevice();
            }
        }

        Task_Delay(10);
    }
}

void SendDataToESP32_Task(){
	
	while(1){
		SendData();
		Task_Delay(1000);
	}
}

void ChangeMode_Task(){
	
	while(1){
		if (Data_Manager.modeActive == OTA_MODE)
		{
			Flash_ErasePage(FIRMWARE_FLAG_ADDRESS);
			Flash_WriteHalfWord(FIRMWARE_FLAG_ADDRESS,(APP_1_ENABLE) | (RST_BOOTLOADER << 8));
			NVIC_SystemReset_handmade() ;
		}
		Task_Delay(5);
	}
	
}

void initDevice(){

	InitSystem_Peripheral(&Data_Manager);
	InitDataManager(&Data_Manager);
}

int main(void)
{
	
	HAL_Init();
	Task_Begin();
	Task_Create(initDevice,25);
	Task_Create(ControlDeviceHandle_Task,5);
	Task_Create(SendDataToESP32_Task,3);
	Task_Create(ChangeMode_Task,10);


	
	
	uartQueue = Queue_Create(LENGTH_FRAME_DATA_CONTROL);
	

	

	
	while (1) {

	}
  
}


