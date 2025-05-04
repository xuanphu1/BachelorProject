#ifndef _MAIN_H
#define _MAIN_H
#include "stdint.h"
#include "UART_Data_Manager.h"
#include "InitSystemPeripheral.h"
#include "SCB_Base.h"

DataManager_t Data_Manager = {	.modeActive = NORMAL_MODE,
                                .SetAuto = TURN_ON_AUTO};



typedef enum {

RST_HARDWARE = 0,
RST_BOOTLOADER

}TypeRST_t;

typedef enum {
APP_1_ENABLE = 1,
APP_2_ENABLE = 2
}Select_App_t;

#define FIRMWARE_FLAG_ADDRESS   0x0800FC00
#define LENGTH_FRAME_DATA_CONTROL 9
#endif // _MAIN_H  
