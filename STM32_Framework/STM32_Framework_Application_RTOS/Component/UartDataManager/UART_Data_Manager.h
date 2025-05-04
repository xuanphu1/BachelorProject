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
	WATERLEVER = 0,
	PH,
	CONDUCTIVITY,
	TDS
	
}Data_t;

typedef struct {
	
	uint16_t StatusDeveice;
	uint16_t DataTemperature;
	uint16_t DataSensor_Analog[4];
	char DataToESP32[100];
	
	uint8_t UartBuff[8];
	
	Mode_t modeActive;
	Set_Auto_t SetAuto;
	
}DataManager_t;


void getSignalMode(void);
void InitDataManager(DataManager_t *DataManager_t);
void ControlDevice(void);
void SendData(void);

#endif // __CONFIG_H__


