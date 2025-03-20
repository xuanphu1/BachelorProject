#include "Config.h"

uint16_t strlen_custom(const char *str) {
    uint16_t length = 0;
    while (*str++) { // Lặp qua từng ký tự cho đến khi gặp '\0'
        length++;
    }
    return length;
}

void uint16_to_char(uint16_t value, char *buffer) {
    uint8_t i = 0;
    char temp[6];  // Tối đa 5 chữ số + 1 null-terminator

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    uint8_t j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }

    buffer[j] = '\0';  // Kết thúc chuỗi
}

void memset_custom(void *ptr, uint8_t value, uint16_t size) {
	uint8_t *p = (uint8_t*)ptr;  // Ép kiểu con trỏ về `uint8_t*`
	while (size--) {
			*p++ = value;  // Gán giá trị và tăng con trỏ
	}
}

/**
 * Hàm ghép `Data` (uint16_t) vào `DataChar` (char buffer)
 */
void InitDataToESP32(DataManager_t *DataManager) {
    char SymbolData[] = {'T','W','P','C','Y','S'};
    //uint8_t idx = 0;
    char tempBuffer[6];  // Đủ để chứa số `uint16_t`
    char *ptr = DataManager->DataToESP32;  // Con trỏ để ghi dữ liệu

    memset_custom(DataManager->DataToESP32, 0, sizeof(DataManager->DataToESP32)); // Xóa dữ liệu cũ

    uint16_t *dataFields[] = {
                            &DataManager->Temperature,
                            &DataManager->WaterLevel,
                            &DataManager->PH_Value,
                            &DataManager->Conductivity_Value,
                            &DataManager->TDS_Value,
                            &DataManager->StatusDeveice,    
    };

    for (uint8_t i = 0; i < 6; i++) {
        uint16_to_char(*dataFields[i], tempBuffer);  // Chuyển số thành chuỗi
        if (i < 6) {
            *ptr++ = SymbolData[i];  // Thêm dấu `,` giữa các số
        }
        // Dùng con trỏ `tempPtr` thay vì `tempBuffer++`
        char *tempPtr = tempBuffer;
        while (*tempPtr) {
            *ptr++ = *tempPtr++;  // Ghi dữ liệu vào `DataToESP32`
        }

        
    }

    *ptr = '\0';  // Kết thúc chuỗi
}

void InitGPIO_Control_Device(void){
	for (Pin_gpio_t idx = PIN_3; idx <= PIN_7; idx++){
		GPIO_config_t GPIO_Ctl_Device = {
		.port = Port_A,
		.pin = idx,
		.mode = OUTPUT_MODE_2_MHZ,
		.cnf_mode = CNF_MODE_00
	};
	InitGPIO(&GPIO_Ctl_Device);
	}
}

