#include "HexFileProcessing.h"

// Hàm tính toán tổng kiểm tra (checksum) của một bản ghi
uint8_t CalculateChecksum(uint8_t* record, uint8_t length) {
    uint8_t sum = 0;
    for (uint8_t i = 0; i < length; i++) {
        sum += record[i];
    }
    return (uint8_t)(~sum + 1);  // Trả về giá trị bổ sung (two's complement)
}


void parseHex(Data_Process_t *path_Hex, uint8_t *ArrayData){
    
    path_Hex->recordType = (RecordType_t)ArrayData[3];
    
    switch (path_Hex->recordType)
    {
    case DATA_LOAD_TO_FLASH:
        path_Hex->addressOffset = ArrayData[2]|(ArrayData[1]<< 8) ;
        
        for (uint8_t i = 0 ; i < path_Hex->byteCount ; i++){
            path_Hex->Data[i] = ArrayData[4 + i];
        }
        break;
    case END_OF_FILE:
        path_Hex->StatusProcess = 1;
				// Jump new application
        break;
    case EXTENDED_ADDRESS:
        
        break;
    case BASE_ADDRESS:
        path_Hex->BaseAddress = ArrayData[5]|(ArrayData[4]<< 8) ;
        break;
    case START_ADDRESS:
        /* code */
        break;
    } 
    path_Hex->checkSum = path_Hex->ArrayBuff[path_Hex->byteCount + 4];
}
uint32_t DataMask;
uint32_t Address ;
void LoadDataToFlash(Data_Process_t *path_Hex){
    parseHex(path_Hex, path_Hex->ArrayBuff);  // Phân tích dữ liệu Hex

    // Tính địa chỉ để ghi vào Flash (BaseAddress và addressOffset)
    Address = (path_Hex->BaseAddress << 16) | path_Hex->addressOffset;

    if (path_Hex->recordType == DATA_LOAD_TO_FLASH) {
        uint8_t dataIdx = 0;  // Chỉ số dữ liệu

        // Vòng lặp ghi 4 byte mỗi lần
        while (dataIdx < path_Hex->byteCount) {
            // Lấy 4 byte dữ liệu tại một thời điểm
            DataMask = 0;
            for (uint8_t i = 0; i < 4; i++) {
                if (dataIdx + i < path_Hex->byteCount) {
                    DataMask |= (path_Hex->Data[dataIdx + i] << (8 * i));
                }
            }

            // Ghi dữ liệu vào Flash
            Flash_Write(Address + dataIdx, DataMask);
            if (dataIdx == 0) Flash_Write(Address + dataIdx, DataMask);
            // Cập nhật địa chỉ và chỉ số dữ liệu
            //Address += 4;
            dataIdx += 4;  // Tiến tới 4 byte tiếp theo
        }
        
    }
}
void receiveDataToOTA(Data_Process_t *DataToOTA){
    DataToOTA->byteCount = DataToOTA->ArrayBuff[0];
	if( DataToOTA->ArrayIndex >= (DataToOTA->byteCount + 5)){
		DataToOTA->Flag_Data_Full_Line = 1;
		DataToOTA->ArrayIndex = 0;
	}
	else {
		DataToOTA->ArrayBuff[DataToOTA->ArrayIndex++] = DataToOTA->eachByteData;
	}
}



// 10 8000 00 00500020 11820008 0D820008 0D820008 370A
// 10 8010 00 0D820008 0D820008 0D820008 00000000 9B



