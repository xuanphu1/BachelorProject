#include "config.h"


DataManager_t DataManager;
uint16_t ADC_Buffer[2];
char UART_Buff[5] ; // Status of 5 device are controlled by ESP32

void USART1_IRQHandler(void) {
    ReceiveDataUART_IT(UART_1,(uint8_t*)UART_Buff,5);
}

void ControlDevice(uint8_t *Control_Deveice) {
    for (Device_t Device = FAN; Device <= LIGHT; Device++) {
        uint8_t deviceState = (Control_Deveice[Device] & 0x10) ? 1 : 0;  
        WritePin(Port_A, (Pin_gpio_t)Device, deviceState);
    }
		DataManager.StatusDeveice = ((UART_Buff[FAN]        & 0x1) << FAN) 		| 
                                    ((UART_Buff[FILLTER]    & 0x1) << FILLTER) 	| 
                                    ((UART_Buff[PUMB]       & 0x1) << PUMB)  	| 
                                    ((UART_Buff[HEATER]     & 0x1) << HEATER)   | 
                                    ((UART_Buff[LIGHT]      & 0x1) << LIGHT); 
}

void getDataFromSensor(DataManager_t *dataSensor){
		dataSensor->Conductivity_Value = 100 ;
		dataSensor->PH_Value = 10 ;
		dataSensor->TDS_Value = 1000 ;
		dataSensor->Temperature = 33 ;
		dataSensor->WaterLevel = 44 ;
	
		dataSensor->Conductivity_Value++;
		dataSensor->PH_Value++;
	
		
		
}


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
    .RegularSequence = {CUSTOM_ADC_CHANNEL_8, CUSTOM_ADC_CHANNEL_9},  // Ch?n 2 kênh (PA0 và PA1)
    .num_of_conversions = 2,
    .conversion_mode = CONTINUOUS_CONVERSION,
    .sample_time = SAMPLE_239_5_CYCLES,  // Ch?n th?i gian l?y m?u thích h?p
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
    .CircularMode = DMA_CIRC_ENABLE, // L?p vô h?n
    .Direction = DMA_DIR_PERIPH_TO_MEM,
    .TransferErrorInt = DMA_TEIE_DISABLE,
    .HalfTransferInt = DMA_HTIE_DISABLE,
    .TransferCompleteInt = DMA_TCIE_DISABLE,
    .PeripheralAddress = (uint32_t)&ADC1_HANDMADE->ADC_DR, // Ð?c t? ADC
    .MemoryAddress = (uint32_t)ADC_Buffer,    // Luu vào m?ng
    .NumData = 2 // Ð?c 16 m?u ADC tru?c khi d?ng (ho?c reset n?u Circular Mode)
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

int main(void)
{
	init_RCC(&rccconfigDefault);
	InitGPIO_Control_Device();
	SysTick_Init(&SysTickConfigDefault);
	UARTInit(&uartConfigDefault);
	EnableInterrupt_RX_UARTx(UART_1);
  while (1)
  {
    

    getDataFromSensor(&DataManager);
		
    ControlDevice((uint8_t*)UART_Buff);
    
    InitDataToESP32(&DataManager);
    TransmitDataUART(UART_1,(uint8_t*)&DataManager.DataToESP32,strlen_custom(DataManager.DataToESP32));
    Delay_SysTick(1000);
}
  
}