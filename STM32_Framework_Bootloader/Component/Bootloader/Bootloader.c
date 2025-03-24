#include "Bootloader.h"

Data_Process_t *dataToOTA;
const Select_App_t firmwareFlag __attribute__((section(".user_data"))) = APP_1_ENABLE;

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

GPIO_config_t config_led = {
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
    InitGPIO(&config_led);
    WritePin(Port_C,PIN_13,0);
}



void Jump_To_Application(uint32_t AppStartAddress)
{
    
    // 1. Lấy giá trị Stack Pointer từ vector table của ứng dụng
    uint32_t topOfMainStack = *(volatile uint32_t*)AppStartAddress;

    // 2. Lấy địa chỉ Reset_Handler của ứng dụng
    void (*App_Reset_Handler)(void) = 
        (void (*)(void))(*(volatile uint32_t*)(AppStartAddress + 4));
    
    // 4. Tắt SysTick
    SYSTICK_HANDMADE->SYST_CSR = 0;
    SYSTICK_HANDMADE->SYST_CVR = 0;
    SYSTICK_HANDMADE->SYST_RVR = 0;

    // 5. Xóa pending fault
    ClearPendingFault();
    
    // 6. Gọi HAL_DeInit
    RCC_DeInit();
    // 7. Set lại Stack Pointer (MSP)
    __set_MSP(topOfMainStack);

    // 8. Gán lại bảng vector
    NVIC_SetVectorTable(AppStartAddress);


    // 10. Nhảy vào ứng dụng
    App_Reset_Handler();
}

void BootLoader(void){

    if (dataToOTA->Flag_Data_Full_Line){
        LoadDataToFlash(dataToOTA);
        dataToOTA->Flag_Data_Full_Line = 0;
        TogglePin(Port_C,PIN_13);
    }
    if(dataToOTA->StatusProcess == 1) {

        if(*((uint8_t*)0x0800FC00)  == APP_1_ENABLE) {
            Flash_EraseRange(APP_2_START_ADDRESS,PAGE_MEMORY_EACH_APP);
            Flash_EraseRange(APP_2_START_ADDRESS,PAGE_MEMORY_EACH_APP);
            Flash_ErasePage(63);
            Flash_ErasePage(63);
            Flash_Write((uint32_t)(&firmwareFlag),APP_2_ENABLE);
            Flash_Write((uint32_t)(&firmwareFlag),APP_2_ENABLE);
            Jump_To_Application(APP_1_START_ADDRESS);
        } 
        if(*((uint8_t*)0x0800FC00) == APP_2_ENABLE) {
            Flash_EraseRange(APP_1_START_ADDRESS,PAGE_MEMORY_EACH_APP);
            Flash_EraseRange(APP_1_START_ADDRESS,PAGE_MEMORY_EACH_APP);
            Flash_ErasePage(63);
            Flash_ErasePage(63);
            Flash_Write((uint32_t)&firmwareFlag,APP_1_ENABLE);
            Flash_Write((uint32_t)&firmwareFlag,APP_1_ENABLE);
            Jump_To_Application(APP_2_START_ADDRESS);
        }
    }
}


