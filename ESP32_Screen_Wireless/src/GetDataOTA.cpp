#include "Update.h"
#include "Project_Manager.h"

extern dataManager_t dataManager;

extern Flag_Signal_Control_t FlagControl;

extern deviceManager_t deviceManager;


static float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static inline uint8_t hexDigitToValue(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else
        return 0;  
}

void convertCharToHex(uint8_t *arrayOutPut, char *arrayInPut, uint8_t length) {
    // Gi? s? length là s? ký t? trong arrayInPut và ph?i là s? ch?n
    uint8_t idx = 0;
    if (arrayInPut[0] == ':') idx = 1;
    uint8_t outputIndex = 0;

    for (idx; idx < length; idx += 2) {
        char high = arrayInPut[idx];
        char low  = arrayInPut[idx + 1];

        uint8_t byteVal = (hexDigitToValue(high) << 4) | hexDigitToValue(low);
        arrayOutPut[outputIndex++] = byteVal;
    }
}

/*
 * Modified version of Espressif's original writeStream() function 
 * to properly receive HEX data from Gateway Era.
 *
 * @author Hồ Xuân Phú
 */
size_t UpdateClass::writeStream(Stream &data) {
    size_t written = 0;
    int byteCount;
    uint32_t total = size();
    Serial.println("Start FOTA ...");
    // Vòng lặp: đọc từng dòng của file .hex cho đến khi không còn dữ liệu hoặc đạt đủ số byte cần ghi
    if (deviceManager.modeActive == OTA_MODE){
        while (remaining()) {
            // Đọc một dòng đến ký tự xuống dòng '\n'
            String line = data.readStringUntil('\n');
            line.trim();  // Loại bỏ khoảng trắng thừa (ví dụ: '\r')
    
             // Nếu dòng bắt đầu bằng dấu ':', bỏ qua ký tự đó
             uint8_t startIndex = 0;
             if (line.charAt(0) == ':') {
                 startIndex = 1;
             }
    
            uint8_t lengthHexLine = line.length();
    
            if (lengthHexLine == 0) {
                Serial.println("Chuyển dữ liệu OTA hoàn tất");
                break; // Không còn dữ liệu
            }
            
            // Giả sử 'line' là một String chứa một dòng dữ liệu HEX
            if (line.charAt(0) == ':') {
                // Lấy 2 ký tự đầu tiên sau dấu ':'
                String byteCountStr = line.substring(1, 3);
                // In ra Serial chuỗi byte count
                
                // Chuyển chuỗi hex thành số nguyên (số byte)
                byteCount = (int) strtol(byteCountStr.c_str(), NULL, 16);
            }
       
            uint8_t numBytes = byteCount + 5;
            // Cấp phát bộ nhớ tạm để lưu dữ liệu chuyển đổi
            dataManager.dataEachLine_HEX_OTA = new uint8_t[numBytes];
            
            convertCharToHex(dataManager.dataEachLine_HEX_OTA, (char*)(line.c_str() + startIndex), lengthHexLine - startIndex);
            Serial.print("Data: ");
            for(int i = 0 ; i < numBytes; i++){
                
                Serial.printf("%02x",dataManager.dataEachLine_HEX_OTA[i]);
                Serial2.write(dataManager.dataEachLine_HEX_OTA[i]);
            }
            Serial2.write(END_LINE_DATA);
            Serial.println("");
            //delay(50);
            yield();   // Nhả CPU


            written += numBytes;
            _progress += numBytes; 
            
            uint32_t progress = total - remaining();
            float percentMask = (progress * 100) / total;
            Serial.printf("percentmask: %0.2f\n",percentMask);
            float percent = mapFloat(percentMask,0,46,0,100);
            Serial.printf("Progress: %0.2f%%\n", percent);
            
            // Giải phóng bộ nhớ đã cấp phát cho dòng hiện tại
            delete[] dataManager.dataEachLine_HEX_OTA;
            dataManager.dataEachLine_HEX_OTA = nullptr;

        }
    }
    
    deviceManager.modeActive = NORMAL_MODE;
    return written;
}