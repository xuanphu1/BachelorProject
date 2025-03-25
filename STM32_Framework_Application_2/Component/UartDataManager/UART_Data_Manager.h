#ifndef __UART_DATA_MANAGER_H__
#define __UART_DATA_MANAGER_H__

#include "DMA_Handmade.h"
#include "ADC_Handmade.h"
#include "Flash_Handmade.h"
#include "GPIO_Handmade.h"
#include "RCC_Handmade.h"
#include "Timer_Handmade.h"
#include "UART_Handmade.h"
#include "Systick_Handmade.h"

typedef enum {
	OTA_MODE = 0xFE,
	NORMAL_MODE = 0xFF
}Mode_t;

#define END_LINE_DATA 0xEE

typedef enum {
    FAN_OFF      = 0x10,
    FAN_ON       = 0x11,

    FILTER_OFF  = 0x20,
    FILTER_ON   = 0x21,

    PUMB_OFF     = 0x30,
    PUMB_ON      = 0x31,

    HEATER_OFF   = 0x40,
    HEATER_ON    = 0x41,

    LIGHT_OFF    = 0x50,
    LIGHT_ON     = 0x51,
	
		FEEDER_OFF   = 0x60,
		FEEDER_ON		 = 0x61

} CMDtatusDevice;

typedef enum {
	FAN = 0,
	FILTER,
	PUMB,
	HEATER,
	LIGHT,
	FEEDER,

}Device_t;

typedef enum {
	TURN_OFF = 0,
	TURN_ON
}Status_Device_t;

typedef enum {
	TURN_OFF_AUTO = 0x0,
	TURN_ON_AUTO	= 0x1
}Set_Auto_t;


typedef enum {
	TEMPERATURE = 0,
	WATERLEVER,
	PH,
	CONDUCTIVITY,
	TDS
	
}Data_t;

typedef struct {
	
	uint16_t StatusDeveice;

	uint16_t DataSensor[5];
	char DataToESP32[100];
	
	uint8_t UartBuff[8];
	uint8_t flagFullData;
	uint8_t idxData;
	
	Mode_t modeActive;
	Set_Auto_t SetAuto;
	
}DataManager_t;


void ReciveUART(uint8_t Data);

void InitDataManager(DataManager_t *DataManager_t);

void UART_Controller(void);

#endif // __UART_DATA_MANAGER_H__


