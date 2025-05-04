#ifndef __FLASH_STM32_H
#define __FLASH_STM32_H
#include "stdint.h"
#include "string.h"
#include "stm32f1xx.h"

#pragma pack (1)
typedef struct{

	uint8_t no;
	uint8_t ssid[30];
	uint8_t password[30];
} wifi_info_t ;
#pragma pack ()





void Flash_erase(uint32_t address);
void Flash_write_int(uint32_t address, int value);
void Flash_write_float (uint32_t address, float value);
void Flash_write_array (uint32_t address, uint8_t *arr, uint16_t len);
void Flash_write_Struct(uint32_t address,wifi_info_t data);

int Flash_read_int(uint32_t address);
float Flash_read_float(uint32_t address);
void Flash_read_array(uint32_t address, uint8_t *arr,uint16_t len);
void Flash_read_struct(uint32_t address,wifi_info_t *data);









#endif 
