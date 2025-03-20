#ifndef CONFIG_H
#define CONFIG_H
#include <TFT_eSPI.h>



#define Fan 1
#define Heater 2
#define Light 3
#define Feeder 4
#define Pump 5


// Thông tin WiFi của bạn
const char* ssid     = "209-WINAS";
const char* password = "if648wgh23";


#define ERA_AUTH_TOKEN "50e4bee6-6a86-48c4-ab2d-8775ed65b6c4"
typedef enum {
	TURN_OFF_AUTO = 0x0,
	TURN_ON_AUTO	= 0x1
}Set_Auto_t;

typedef enum {
	OTA_MODE = 0xFE,
	NORMAL_MODE = 0xFF
}Mode_t;

#define END_DATA 0xEE


typedef struct {
  uint8_t Flag_control_Fan;
  uint8_t Flag_control_Fillter;
  uint8_t Flag_control_Pumb;
  uint8_t Flag_control_Heater;
  uint8_t Flag_control_Light;
  uint8_t Flag_control_Feeder;

  uint8_t Flag_Auto;
  uint8_t Flag_OTA;

}Flag_Signal_Control_t;

typedef struct {
  char TDS_Value[6];  
  char PH_Value[6];   
  char CONDUCT_Value[6];  
  char Temperature_Value[6];  
  char Water_Capacity[6];  
  char statusDevice[6];
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

static const uint16_t screenWidth = 172;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

TFT_eSPI tft = TFT_eSPI();

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

const int ledPin = 27;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void tft_init() {
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
  ledcWrite(ledChannel, 255);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
}

void lvgl_init() {
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
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

#endif



