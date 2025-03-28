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

void main_1(){
	while(1){
		TogglePin(Port_A,PIN_0);
		Task_Delay(100);
	}

}

void main_2(){
	while(1){
		TogglePin(Port_A,PIN_1);
		Task_Delay(300);
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
	Task_Begin();
	Task_Create(main_1,2);
	Task_Create(main_2,3);
	Task_Create(main_3,4);
	
	while (1) {
		RTOS_Run();
	}
  
}



