#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H
#include <Arduino.h>  // Thêm thư viện này để định nghĩa String
#include "esp_task_wdt.h"


#define Fan 1
#define Heater 2
#define Light 3
#define Feeder 4
#define Pump 5



typedef enum {
	TURN_OFF_AUTO = 0x0,
	TURN_ON_AUTO	= 0x1
}Set_Auto_t;

typedef enum {
	OTA_MODE = 0xFE,
	NORMAL_MODE = 0xFF
}Mode_t;

#define END_LINE_DATA 0xEE


typedef struct {
  uint8_t Flag_control_Fan;
  uint8_t Flag_control_Fillter;
  uint8_t Flag_control_Pumb;
  uint8_t Flag_control_Heater;
  uint8_t Flag_control_Light;
  uint8_t Flag_control_Feeder;

  uint8_t Flag_Auto;
  uint8_t Flag_OTA;

  uint8_t Flag_Request_OTA;

}Flag_Signal_Control_t;

typedef struct {
  char TDS_Value[6];  
  char PH_Value[6];   
  char CONDUCT_Value[6];  
  char Temperature_Value[6];  
  char Water_Capacity[6];  
  char statusDevice[6];

  uint8_t *dataEachLine_HEX_OTA; 
  float PercentProgress;
} dataManager_t;

typedef enum {
	FAN = 0,
	FILLTER,
	PUMB,
	HEATER,
	LIGHT,
  FEEDER,

  SET_AUTO
}Device_t;



typedef struct {
  uint8_t FanStatus;
  uint8_t FilterStatus;
  uint8_t PumpStatus;
  uint8_t HeaterStatus;
  uint8_t LightStatus;
  uint8_t FeederStatus;

  Set_Auto_t set_Auto;
  Mode_t modeActive;

} deviceManager_t;



// Dữ liệu đầu vào dạng: "Txx.xWxx.xPxx.xxCxxxxYxxxSxxxxx"
void processingData(String data, dataManager_t *Data);
uint8_t charArray_to_uint8(char *arr, uint8_t length);

#endif



