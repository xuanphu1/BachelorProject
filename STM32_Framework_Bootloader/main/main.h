#ifndef _MAIN_H
#define _MAIN_H
#include "Bootloader.h"

// Định nghĩa từng phần
#define IS_APP_ENABLED  ((*(uint8_t*)FIRMWARE_FLAG_ADDRESS) == APP_2_ENABLE || \
                         (*(uint8_t*)FIRMWARE_FLAG_ADDRESS) == APP_1_ENABLE)

#define HAS_VALID_APP   ((*(uint32_t*)APP_2_START_ADDRESS) != 0xFFFFFFFF || \
                         (*(uint32_t*)APP_1_START_ADDRESS) != 0xFFFFFFFF)

#define IS_RST_HARDWARE ((*(uint8_t*)(FIRMWARE_FLAG_ADDRESS + 1)) == RST_HARDWARE && \
                         DataToOTA.SignalLockReciveData != 1)

// Kết hợp thành macro cuối cùng
#define CHECK_RST_HARDWARE  (IS_APP_ENABLED && HAS_VALID_APP && IS_RST_HARDWARE)

Data_Process_t DataToOTA = {0} ;

#endif // _MAIN_H  


