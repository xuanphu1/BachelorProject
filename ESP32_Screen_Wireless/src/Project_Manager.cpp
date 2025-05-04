#include "Project_Manager.h"

// Dữ liệu đầu vào dạng: "Txx.xWxx.xPxx.xxCxxxxYxxxSxxxxx"
uint8_t charArray_to_uint8(char *arr, uint8_t length) {
  uint8_t result = 0;
  for(uint8_t i = 0; i < length; i++) {
      if(arr[i] >= '0' && arr[i] <= '9') {
          result = result * 10 + (arr[i] - '0');
      } else {
          // Ký t? không h?p l?, tr? v? 0 ho?c x? lý l?i tùy ý b?n
          return 0;
      }
  }
  return result;
}

  
// Dữ liệu đầu vào dạng: "Txx.xWxx.xPxx.xxCxxxxYxxxSxxxxx"
void processingData(String data, dataManager_t *Data) {
  uint8_t length = data.length();
  char temp[6];  // Bộ nhớ tạm để lưu số đọc được
  uint8_t tempIndex = 0;  // Vị trí ghi dữ liệu trong `temp`
  char* targetField = nullptr;  // Con trỏ trỏ đến vùng dữ liệu cần lưu

  for (uint8_t i = 0; i < length; i++) {
    char c = data[i];

    // Khi gặp chữ cái, lưu dữ liệu vừa đọc vào đúng biến struct
    if (isAlpha(c)) {
      if (targetField != nullptr && tempIndex > 0) {  
        temp[tempIndex] = '\0';  // Kết thúc chuỗi
        strcpy(targetField, temp);  // Sao chép vào struct
      }

      // Xác định nơi cần lưu dữ liệu tiếp theo
      switch (c) {
        case 'T': targetField = Data->Temperature_Value; break;
        case 'W': targetField = Data->Water_Capacity; break;
        case 'P': targetField = Data->PH_Value; break;
        case 'C': targetField = Data->CONDUCT_Value; break;
        case 'Y': targetField = Data->TDS_Value; break;
        case 'S': targetField = Data->statusDevice; break;
        default: targetField = nullptr; break;
      }

      // Reset bộ nhớ tạm
      tempIndex = 0;
    } 
    else if (isdigit(c) || c == '.') {  // Nếu là số hoặc dấu '.'
      if (tempIndex < 5) {  // Giới hạn 5 ký tự để tránh tràn bộ nhớ
        temp[tempIndex++] = c;
      }
    }
  }

  // Lưu dữ liệu cuối cùng (nếu có)
  if (targetField != nullptr && tempIndex > 0) {
    temp[tempIndex] = '\0';  // Kết thúc chuỗi
    strcpy(targetField, temp);  // Sao chép vào struct
  }
}

