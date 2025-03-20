#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "DMA_Handmade.h"
#include "ADC_Handmade.h"
#include "Flash_Handmade.h"
#include "GPIO_Handmade.h"
#include "RCC_Handmade.h"
#include "Timer_Handmade.h"
#include "UART_Handmade.h"
#include "Systick_Handmade.h"
#include "stdint.h"
#include "Syscall_Handmade.h"


typedef enum {
    FAN_OFF      = 0x10,
    FAN_ON       = 0x11,

    FILLTER_OFF  = 0x20,
    FILLTER_ON   = 0x21,

    PUMB_OFF     = 0x30,
    PUMB_ON      = 0x31,

    HEATER_OFF   = 0x40,
    HEATER_ON    = 0x41,

    LIGHT_OFF    = 0x50,
    LIGHT_ON     = 0x51

} CMDtatusDevice;

typedef enum {
	FAN = 0,
	FILLTER,
	PUMB,
	HEATER,
	LIGHT
}Device_t;

typedef enum {
	TURN_OFF = 0,
	TURN_ON
}Status_Device_t;

typedef struct {
	
	uint16_t StatusDeveice;
	uint16_t Temperature;
	uint16_t TDS_Value;
	uint16_t Conductivity_Value;
	uint16_t PH_Value;
	uint16_t WaterLevel;
	char DataToESP32[100];
	
}DataManager_t;







void InitGPIO_Control_Device(void);
uint16_t strlen_custom(const char *str);
void uint16_to_char(uint16_t value, char *buffer);
void memset_custom(void *ptr, uint8_t value, uint16_t size);
void InitDataToESP32(DataManager_t *DataManager) ;

#endif // __CONFIG_H__


