#include "main.h"
#include "Systick_Handmade.h"
#include "GPIO_Handmade.h"
#include "RCC_Handmade.h"
#include "FreeRTOS_Handmade.h"

SysTick_Config_t SysTickConfig = {
    .EnableCounter = SYST_CSR_COUNTFLAG_YES,
    .Generate_interrupt = SYST_CSR_TICKINT_ENABLE,
    .SysTick_Source = SYST_CSR_CLKSOURCE_EXTERNAL,
    .ValueInitReload = 0 
};

RCC_config_t rccconfig ={
    .source_clock = HSE_CLOCK,
    .frequency = FREQ_72MHZ
};

GPIO_config_t LEDHardware = {
    .port = Port_C,
    .pin = PIN_13,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_00 // Alternate Function Push-Pull
};

GPIO_config_t LED2 = {
    .port = Port_A,
    .pin = PIN_0,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_00 // Alternate Function Push-Pull
};
GPIO_config_t LED3 = {
    .port = Port_A,
    .pin = PIN_1,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_00 // Alternate Function Push-Pull
};
// SP HERE - R0 - R1 - R2 - R3 - R12 - PC - LR - EPSR

void HardFault_Handler(){
	return;
}


void SysTick_Handler() {
	Systick_ms_inc();
	TriggerSV_Call_Interrupt();
}


Queue_t* ledQueue;
Mutex_t* gpioMutex;

void main_1(void) { // Task g?i d? li?u
    while (1) {
        uint32_t data = 1; // B?t LED
        Mutex_Lock(gpioMutex);
        Queue_Send(ledQueue, data);
        Mutex_Unlock(gpioMutex);
        Task_Delay(200);
    }
}

void main_2(void) { // Task nh?n d? li?u
    while (1) {
        uint32_t data;
        if (Mutex_Lock(gpioMutex)) {
            if (Queue_Receive(ledQueue, &data)) {
                if (data == 1) {
                    TogglePin(Port_A, PIN_0);
										TogglePin(Port_A, PIN_1);
                }
            }
            Mutex_Unlock(gpioMutex);
        }
        Task_Delay(50);
    }
}

void main_3(){
	while(1){
		TogglePin(Port_C,PIN_13);
		Task_Delay(500);
	}
}




int main(void)
{
	
	HAL_Init();
	init_RCC(&rccconfig);
	SysTick_Init(&SysTickConfig);
	InitGPIO(&LEDHardware);
	InitGPIO(&LED2);
	InitGPIO(&LED3);
	
	ledQueue = Queue_Create(10); // Queue 10 ph?n t?
  gpioMutex = Mutex_Create();
	
	Task_Begin();
	Task_Create(main_1,2);
	Task_Create(main_2,3);
	Task_Create(main_3,4);
	

	
	while (1) {
		RTOS_Run();
	}
  
}


