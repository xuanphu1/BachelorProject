#include "InitSystemPeripheral.h"

DataManager_t *_Data_Manager;


Custom_USART_Config_t uartConfigDefault = {
    .usartEnable = Custom_UE_ENABLE,
    .wordLength = Custom_M_8BIT,
    .stopBits = Custom_STOP_1,
    .baudUART = Custom_Baud_115200,
};

SysTick_Config_t SysTickConfigDefault = {
    .EnableCounter = SYST_CSR_COUNTFLAG_YES,
    .Generate_interrupt = SYST_CSR_TICKINT_ENABLE,
    .SysTick_Source = SYST_CSR_CLKSOURCE_EXTERNAL,
    .ValueInitReload = 9000 
};

ADC_Config_t ADC_Config_5_SENSOR = {
    .RegularSequence = {CUSTOM_ADC_CHANNEL_3, CUSTOM_ADC_CHANNEL_4,
                        CUSTOM_ADC_CHANNEL_5,CUSTOM_ADC_CHANNEL_6,
                        },  // Các kênh đọc ADC
    .num_of_conversions = 4,
    .conversion_mode = CONTINUOUS_CONVERSION,
    .sample_time = SAMPLE_239_5_CYCLES,  // Ch?n th?i gian l?y m?u th�ch h?p
    .dma_mode = DMA_ENABLE,
    .scan_mode = SCAN_ENABLE
};

DMA_Config_t DMA_ADC_4_SENSOR = {
    .Channel = DMA_CHANNEL_1, // DMA1 Channel 1
    .Priority = DMA_HIGH_PRIORITY,
    .PeripheralIncrement = DISABLE_DMA_PINC,
    .MemoryIncrement = ENABLE_DMA_MINC,
    .PeripheralSize = DMA_PSIZE_16BIT,
    .MemorySize = DMA_MSIZE_16BIT,
    .CircularMode = DMA_CIRC_ENABLE,
    .Direction = DMA_DIR_PERIPH_TO_MEM,
    .TransferErrorInt = DMA_TEIE_DISABLE,
    .HalfTransferInt = DMA_HTIE_DISABLE,
    .TransferCompleteInt = DMA_TCIE_DISABLE,
		.PeripheralAddress = (uint32_t)&ADC1_HANDMADE->ADC_DR,
		.MemoryAddress = 0,
    .NumData = 4 
};

RCC_config_t rccconfigDefault ={
    .source_clock = HSE_CLOCK,
    .frequency = FREQ_72MHZ
};






GPIO_config_t LED_Hardware = {
    .port = Port_C,
    .pin = PIN_13,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_00 // Alternate Function Push-Pull
};


void InitGPIO_Control_Device(void){

	for (Pin_gpio_t idx = PIN_3; idx <= PIN_7; idx++){
		GPIO_config_t GPIO_Ctl_Device = {
		.port = Port_B,
		.pin = idx,
		.mode = OUTPUT_MODE_50_MHZ,
		.cnf_mode = CNF_MODE_00
	};
	InitGPIO(&GPIO_Ctl_Device);
	}
}

	GPIO_config_t GPIO_DS18B20 = {
		.port = Port_A,
		.pin = PIN_7,
		.mode = OUTPUT_MODE_50_MHZ,
		.cnf_mode = CNF_MODE_00
	};
	
	TIM_Config_t PWM_Servo_Feeder = {
    .Timer = TIMER_2,
    .ValueCount = 0,
    .ValueAutoReload = 1000,
    .DutyCycle = 100,
    .DesiredFrequency = 1000000UL,
    .autoReloadPreload = Custom_ARPE_BUFFERED,
    .counterEnable = Custom_CEN_ON
};

GPIO_config_t GPIO_PWM_Servo_Feeder = {
    .port = Port_A,
    .pin = PIN_8,
    .mode = OUTPUT_MODE_50_MHZ,
    .cnf_mode = CNF_MODE_10 // Alternate Function Push-Pull
};



void InitSystemPeripheral(DataManager_t *_DataManager){
	
	_Data_Manager = _DataManager;
	DMA_ADC_4_SENSOR.MemoryAddress = (uint32_t)&_Data_Manager->DataSensor;
	init_RCC(&rccconfigDefault);
	InitGPIO_Control_Device();
	InitGPIO(&GPIO_DS18B20);
	InitGPIO(&GPIO_PWM_Servo_Feeder);
	InitGPIO(&LED_Hardware);
	SysTick_Init(&SysTickConfigDefault);
	ADC_Init(&ADC_Config_5_SENSOR);
	DMA_Init(&DMA_ADC_4_SENSOR);
	DMA_Start(DMA_CHANNEL_1);
	ADC_DMA_Start();
	
	UARTInit(&uartConfigDefault);
	EnableInterrupt_RX_UARTx(UART_1);
	
}
