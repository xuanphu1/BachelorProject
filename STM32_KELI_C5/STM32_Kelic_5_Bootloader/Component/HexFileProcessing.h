#ifndef __HEX_FILE_PROCESSING_H__
#define __HEX_FILE_PROCESSING_H__
#include "stdint.h"
#include "Flash_Handmade.h"
#include "UART_Handmade.h"
#include "Systick_Handmade.h"
#include "cmsis_armcc.h"



typedef enum {
    NACK = 0,
    ACK
}ACK_t;

typedef enum {
    START_OTA = 0,
    END_OTA
}StatusOTA;


#define END_LINE_DATA 0xEE

typedef enum {

    DATA_LOAD_TO_FLASH = 0x00,
    END_OF_FILE = 0x01,
    EXTENDED_ADDRESS = 0x02,
    BASE_ADDRESS = 0x04,
    START_ADDRESS = 0x05

}RecordType_t;

typedef struct {
    // Each data field of the hex file
    uint8_t byteCount;    // Số byte dữ liệu
    uint16_t addressOffset;     // Địa chỉ
    RecordType_t recordType;   // Loại bản ghi
    uint8_t Data[16];        // Con trỏ đến dữ liệu
    uint8_t checkSum;
    uint32_t BaseAddress;
    uint8_t StatusProcess;

    // Data for UART
    uint8_t Flag_Data_Full_Line;
    uint8_t eachByteData;
    uint8_t ArrayIndex;
    uint8_t ArrayBuff[25];

} Data_Process_t;




// Hàm tính toán tổng kiểm tra (checksum) của một bản ghi
uint8_t CalculateChecksum(uint8_t* record, uint8_t length);
void parseHex(Data_Process_t *path_Hex, uint8_t *ArrayData);
void LoadDataToFlash(Data_Process_t *path_Hex);
void receiveDataToOTA(Data_Process_t *DataToOTA);

#endif // __HEX_FILE_PROCESSING_H__


