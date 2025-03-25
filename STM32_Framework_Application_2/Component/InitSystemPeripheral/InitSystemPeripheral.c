#include "InitSystemPeripheral.h"




Custom_USART_Config_t uartConfigDefault = {
    .usartEnable = Custom_UE_ENABLE,
    .wordLength = Custom_M_8BIT,
    .stopBits = Custom_STOP_1,
    .baudUART = Custom_Baud_9600,
};

SysTick_Config_t SysTickConfigDefault = {
    .EnableCounter = SYST_CSR_COUNTFLAG_YES,
    .Generate_interrupt = SYST_CSR_TICKINT_DISABLE,
    .SysTick_Source = SYST_CSR_CLKSOURCE_EXTERNAL,
    .ValueInitReload = 0 
};

ADC_Config_t adcConfig_2_PinADC = {
    .RegularSequence = {CUSTOM_ADC_CHANNEL_8, CUSTOM_ADC_CHANNEL_9},  // Ch?n 2 k�nh (PA0 v� PA1)
    .num_of_conversions = 2,
    .conversion_mode = CONTINUOUS_CONVERSION,
    .sample_time = SAMPLE_239_5_CYCLES,  // Ch?n th?i gian l?y m?u th�ch h?p
    .dma_mode = DMA_ENABLE,
    .scan_mode = SCAN_ENABLE
};

DMA_Config_t dmaADC_2_Pin = {
    .Channel = DMA_CHANNEL_1, // DMA1 Channel 1
    .Priority = DMA_HIGH_PRIORITY,
    .PeripheralIncrement = DISABLE_DMA_PINC,
    .MemoryIncrement = ENABLE_DMA_MINC,
    .PeripheralSize = DMA_PSIZE_16BIT,
    .MemorySize = DMA_MSIZE_16BIT,
    .CircularMode = DMA_CIRC_ENABLE, // L?p v� h?n
    .Direction = DMA_DIR_PERIPH_TO_MEM,
    .TransferErrorInt = DMA_TEIE_DISABLE,
    .HalfTransferInt = DMA_HTIE_DISABLE,
    .TransferCompleteInt = DMA_TCIE_DISABLE,
    // .PeripheralAddress = (uint32_t)&ADC1_HANDMADE->ADC_DR, // �?c t? ADC
    // .MemoryAddress = (uint32_t)ADC_Buffer,    // Luu v�o m?ng
    .NumData = 2 // �?c 16 m?u ADC tru?c khi d?ng (ho?c reset n?u Circular Mode)
};

RCC_config_t rccconfigDefault ={
    .source_clock = HSE_CLOCK,
    .frequency = FREQ_72MHZ
};

TIM_Config_t PWMconfig = {
    .Timer = TIMER_2,
    .ValueCount = 0,
    .ValueAutoReload = 1000,
    .DutyCycle = 100,
    .DesiredFrequency = 1000000UL,
    .autoReloadPreload = Custom_ARPE_BUFFERED,
    .counterEnable = Custom_CEN_ON
};

GPIO_config_t GPIO_PWM = {
    .port = Port_A,
    .pin = PIN_0,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_10 // Alternate Function Push-Pull
};

GPIO_config_t LED = {
    .port = Port_C,
    .pin = PIN_13,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_00 // Alternate Function Push-Pull
};

GPIO_config_t config_input = {
	.port = Port_A,
	.pin = PIN_4,
	.mode = INPUT_MODE,
	.cnf_mode = CNF_MODE_10
};

void InitGPIO_Control_Device(void){

	for (Pin_gpio_t idx = PIN_3; idx <= PIN_7; idx++){
		GPIO_config_t GPIO_Ctl_Device = {
		.port = Port_A,
		.pin = idx,
		.mode = OUTPUT_MODE_2_MHZ,
		.cnf_mode = CNF_MODE_00
	};
	InitGPIO(&GPIO_Ctl_Device);
	
	GPIO_config_t GPIO_Ctl_Device_1 = {
		.port = Port_B,
		.pin = PIN_0,
		.mode = OUTPUT_MODE_2_MHZ,
		.cnf_mode = CNF_MODE_00
	};
	InitGPIO(&GPIO_Ctl_Device_1);
	}
}

void InitSystemPeripheral(void){
	
	init_RCC(&rccconfigDefault);
	InitGPIO(&config_input);
	InitGPIO_Control_Device();
	SysTick_Init(&SysTickConfigDefault);
	UARTInit(&uartConfigDefault);
	EnableInterrupt_RX_UARTx(UART_1);
	InitGPIO(&LED);
}
