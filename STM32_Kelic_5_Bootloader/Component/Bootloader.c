#include "Bootloader.h"
#include "stm32f1xx_hal.h"
Data_Process_t *dataToOTA;
uint8_t Flag_Select_App = APP_1_ENABLE;

#define SCS_BASE_HANDMADE            	(0xE000E000UL)  
#define SHCSR_Handmade      					(SCS_BASE_HANDMADE + 0x24)            //*!< Offset: 0x024
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
RCC_config_t rccconfigDefault ={
    .source_clock = HSE_CLOCK,
    .frequency = FREQ_72MHZ
};

GPIO_config_t config_gpio = {
	.port = Port_C,
	.pin = PIN_13,
	.mode = OUTPUT_MODE_50_MHZ,
	.cnf_mode = CNF_MODE_00
};

void InitBootLoader(Data_Process_t *DataOTA){
    dataToOTA = DataOTA;
    init_RCC(&rccconfigDefault);
		SysTick_Init(&SysTickConfigDefault);
		UARTInit(&uartConfigDefault);
		EnableInterrupt_RX_UARTx(UART_1);
		InitGPIO(&config_gpio);
		WritePin(Port_C,PIN_13,1);
}



void Jump_To_Application(uint32_t AppStartAddress)
{
    // 1. Lấy giá trị Stack Pointer từ vector table của ứng dụng
    uint32_t topOfMainStack = *(volatile uint32_t*)AppStartAddress;

    // 2. Lấy địa chỉ Reset_Handler của ứng dụng
    void (*App_Reset_Handler)(void) = 
        (void (*)(void))(*(volatile uint32_t*)(AppStartAddress + 4));

    // 3. Vô hiệu hóa tất cả ngắt
    //__disable_irq();

    // 4. Tắt SysTick
    SYSTICK_HANDMADE->SYST_CSR = 0;
    SYSTICK_HANDMADE->SYST_CVR = 0;
    SYSTICK_HANDMADE->SYST_RVR = 0;

    // 5. Xóa pending fault
    *((volatile uint32_t *)SHCSR_Handmade) &= ~((1UL << 16) | (1UL << 17) | (1UL << 18));

    // 6. Gọi HAL_DeInit
    //HAL_RCC_DeInit();
		RCC_DeInit();
    //HAL_DeInit();

    // 7. Set lại Stack Pointer (MSP)
    __set_MSP(topOfMainStack);

    // 8. Gán lại bảng vector
    _VTOR = AppStartAddress;


    // 10. Nhảy vào ứng dụng
    App_Reset_Handler();
}


void BootLoader(void){

    if (dataToOTA->Flag_Data_Full_Line){
        LoadDataToFlash(dataToOTA);
        dataToOTA->Flag_Data_Full_Line = 0;
    }
    if(dataToOTA->StatusProcess == 1) {
        if((Select_App_t)Flag_Select_App == APP_1_ENABLE) {
            Flash_EraseRange(APP_2_START_ADDRESS,PAGE_MEMORY_EACH_APP);
            Flag_Select_App = APP_2_ENABLE;
            Jump_To_Application(APP_1_START_ADDRESS);
        } else {
            Flash_EraseRange(APP_1_START_ADDRESS,PAGE_MEMORY_EACH_APP);
            Flag_Select_App = APP_1_ENABLE;
            Jump_To_Application(APP_2_START_ADDRESS);
        }
    }
}