#include <lvgl.h>
#include "config.h"
#include "ui.h"
#include <WiFi.h>
#include <Arduino.h>
#include <ERa.hpp>
#include "RTClib.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "Project_Manager.h"



Flag_Signal_Control_t FlagControl = {.Flag_End_OTA = 1};
RTC_DS1307 rtc; // Khởi tạo RTC
unsigned long previousMillisRTC = 0;
const long intervalRTC = 1000; // Cập nhật mỗi 1000ms (1 giây)

unsigned long previousMillisNTP = 0;
const long intervalNTP = 86400000; // Cập nhật NTP mỗi 24 giờ (86400 giây)

// Cấu hình NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000); // GMT+7, cập nhật mỗi 60 giây

bool wifiConnected = false; // Trạng thái WiFi

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

dataManager_t dataManager;
deviceManager_t deviceManager = { .set_Auto = TURN_ON_AUTO,
                                  .modeActive = NORMAL_MODE} ;

ERA_WRITE(V5) { // Fan

  uint8_t SignalControlFanMask = deviceManager.FanStatus;
  deviceManager.FanStatus = param.getInt();
  Serial.printf("Fan Status: %d\n",deviceManager.FanStatus);
  if (SignalControlFanMask != deviceManager.FanStatus) FlagControl.Flag_control_Fan = 1;

}
ERA_WRITE(V6) { // Heater

  uint8_t SignalControlHeartMask = deviceManager.HeaterStatus;
  deviceManager.HeaterStatus = param.getInt();
  Serial.printf("Heater Status: %d\n",deviceManager.HeaterStatus);
  if(SignalControlHeartMask != deviceManager.HeaterStatus) FlagControl.Flag_control_Heater = 1;

}
ERA_WRITE(V7) { // Light
  uint8_t SignalControlLight = deviceManager.LightStatus;
  deviceManager.LightStatus = param.getInt();
  Serial.printf("Light Status: %d\n",deviceManager.LightStatus);
  if(SignalControlLight != deviceManager.LightStatus) FlagControl.Flag_control_Light = 1;
}
ERA_WRITE(V8) { // Feeder
  uint8_t SignalControlFeeder = deviceManager.FeederStatus;
  deviceManager.FeederStatus = param.getInt();
  Serial.printf("Feeder Status: %d\n",deviceManager.FeederStatus);
  if(SignalControlFeeder != deviceManager.FeederStatus) FlagControl.Flag_control_Feeder = 1;

}

ERA_WRITE(V9) { // pump
  uint8_t SignalControlPumb = deviceManager.PumpStatus;
  deviceManager.PumpStatus = param.getInt();
  Serial.printf("Pump Status: %d\n",deviceManager.PumpStatus);
  if(SignalControlPumb != deviceManager.PumpStatus) FlagControl.Flag_control_Pumb = 1;

}

ERA_WRITE(V10) { // Filter
  uint8_t SignalControlFilter = deviceManager.FilterStatus;
  deviceManager.FilterStatus = param.getInt();
  Serial.printf("Filter Status: %d\n",deviceManager.FilterStatus);
  if(SignalControlFilter != deviceManager.FilterStatus) FlagControl.Flag_control_Fillter = 1;

}

ERA_WRITE(V11) { // Filter
  Set_Auto_t SignalControlAuto = deviceManager.set_Auto;
  deviceManager.set_Auto = (Set_Auto_t)param.getInt();
  Serial.printf("Auto Status: %d\n",deviceManager.set_Auto);
  if(SignalControlAuto != deviceManager.set_Auto) FlagControl.Flag_Auto = 1;

}

ERA_WRITE(V12) { // Request OTA
  FlagControl.Flag_Request_OTA  = param.getInt();
  if (1 == FlagControl.Flag_Request_OTA) deviceManager.modeActive = OTA_MODE;
}


void setup() {

    // Khởi tạo Serial để debug trên Serial Monitor
Serial.begin(115200);
Serial.println("Khởi tạo Serial Monitor");

// Sử dụng đối tượng Serial2 có sẵn của ESP32, cấu hình chân RX = 16, TX = 17 với tốc độ 115200
Serial2.begin(115200, SERIAL_8N1, 16, 17);
Serial.println("Serial2 khởi tạo trên chân 16 (RX) và 17 (TX)");

// Khởi tạo màn hình TFT và LVGL
tft_init();
lvgl_init();
ui_init();
  
  // Kiểm tra RTC
if (!rtc.begin()) {
  Serial.println("Không tìm thấy RTC");
}

if (!rtc.isrunning()) {
    Serial.println("RTC chưa chạy, đang cài đặt thời gian...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Cài đặt thời gian từ thời gian biên dịch
}


Serial.printf("ERa đang kết nối wifi %s ...\n", ssid_era);
ERa.begin(ssid_era, password_era);  
if (WiFi.status() == WL_CONNECTED) {
    timeClient.begin();
    Serial.println("Đã khởi động NTP.");

    wifiConnected = WiFi.status();
    
    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();
    if (epochTime > 1000000000) { // Kiểm tra nếu thời gian hợp lệ
        rtc.adjust(DateTime(epochTime));
        Serial.println("Đã cập nhật thời gian từ NTP vào RTC.");
    } else {
        Serial.println("Lỗi: Thời gian từ NTP không hợp lệ!");
    }
} else {
    Serial.println("WiFi chưa kết nối, không thể lấy thời gian NTP.");
}


  
  lv_img_set_src(WifiStatus, wifiConnected ? &ui_img_1365894730 : &ui_img_2139209214);

  
  ERa.virtualWrite(V5,0);
  ERa.virtualWrite(V6,0);
  ERa.virtualWrite(V7,0);
  ERa.virtualWrite(V8,0);
  ERa.virtualWrite(V9,0);
  ERa.virtualWrite(V10,0);
  ERa.virtualWrite(V11,deviceManager.set_Auto);
  ERa.virtualWrite(V12,FlagControl.Flag_Request_OTA);
  Serial.println("Setup done");




}

void loop() {
  unsigned long currentMillis = millis();

  // Kiểm tra trạng thái WiFi
  bool newWifiStatus = (WiFi.status() == WL_CONNECTED);
  if (newWifiStatus != wifiConnected) { // Nếu trạng thái thay đổi
      wifiConnected = newWifiStatus;
      Serial.printf("WiFi trạng thái thay đổi: %s\n", wifiConnected ? "Đã kết nối" : "Mất kết nối");
      lv_img_set_src(WifiStatus, wifiConnected ? &ui_img_1365894730 : &ui_img_2139209214);
      
      // Nếu WiFi kết nối lại, bắt đầu lại NTP
      if (wifiConnected) {
          timeClient.begin();
          Serial.println("WiFi đã kết nối! Bắt đầu đồng bộ NTP.");
      }
  }

  //Cập nhật thời gian NTP mỗi 24 giờ
  if (wifiConnected && (currentMillis - previousMillisNTP >= intervalNTP)) {
      previousMillisNTP = currentMillis;
      timeClient.update();
      DateTime ntpTime(timeClient.getEpochTime());

      if (ntpTime.year() > 2020) { // Kiểm tra thời gian hợp lệ từ NTP
          rtc.adjust(ntpTime);
          Serial.println("Đã cập nhật thời gian từ NTP vào RTC.");
      } else {
          Serial.println("Lỗi: Thời gian từ NTP không hợp lệ!");
      }
  }

  // Cập nhật thời gian RTC mỗi giây
  if (currentMillis - previousMillisRTC >= intervalRTC) {
      previousMillisRTC = currentMillis;

      DateTime now = rtc.now();

      // Cập nhật thời gian lên LVGL
      lv_label_set_text_fmt(ui_Hour, "%02d", now.hour());
      lv_label_set_text_fmt(ui_Minute, "%02d", now.minute());
      lv_label_set_text_fmt(ui_Second, "%02d", now.second());

      lv_label_set_text_fmt(ui_HourMask, "%02d", now.hour());
      lv_label_set_text_fmt(ui_MinuteMask, "%02d", now.minute());
      lv_label_set_text_fmt(ui_SecondMask, "%02d", now.second());

      lv_label_set_text_fmt(ui_Day, "%02d", now.day());
      lv_label_set_text_fmt(ui_month, "%02d", now.month());
      lv_label_set_text_fmt(ui_year, "%04d", now.year());
      lv_label_set_text(ui_WeekDay, daysOfTheWeek[now.dayOfTheWeek()]); // Cập nhật thứ trong tuần
  }

  if( FlagControl.Flag_control_Fan || FlagControl.Flag_control_Fillter || FlagControl.Flag_control_Heater || FlagControl.Flag_control_Light || FlagControl.Flag_control_Pumb || FlagControl.Flag_control_Feeder)
  {
    uint8_t ControlCommand[9];
    uint8_t *ptr = (uint8_t*)&deviceManager;
    Serial.print("Command: ");
    for(uint8_t i = 0 ; i < 9 ; i++){
      ControlCommand[i] = ((i+1) << 4) | (*(ptr + i) & 0x1);
      if(i == 6) ControlCommand[i] = (deviceManager.set_Auto == TURN_ON_AUTO) ? TURN_ON_AUTO : TURN_OFF_AUTO;
      if(i == 7) ControlCommand[i] = (deviceManager.modeActive == NORMAL_MODE) ? NORMAL_MODE : OTA_MODE;
      if(i == 8) ControlCommand[i] = END_DATA;
      Serial2.write(ControlCommand[i]);
      
      Serial.printf("%x",ControlCommand[i]);
    }
    
    FlagControl = {0};
  } 

  if (Serial2.available() > 0) {
    // Đọc dữ liệu đến khi gặp ký tự xuống dòng
    String receivedData = Serial2.readStringUntil('\0');
    Serial.print("Nhận được từ Serial2: ");
    Serial.println(receivedData);
    
    processingData(receivedData,&dataManager);
    uint8_t StatusDevice ;

    if(dataManager.statusDevice[2] != 0){
      StatusDevice = charArray_to_uint8(dataManager.statusDevice,3);
    } else 
    {
        if (dataManager.statusDevice[1] != 0){
          StatusDevice = charArray_to_uint8(dataManager.statusDevice,2);
        } else {
          StatusDevice = dataManager.statusDevice[0] - '0';
        }
    }
    Serial.printf("StatusDevice :%d\n",StatusDevice);
    deviceManager.FanStatus       = (StatusDevice >> FAN)                     & 0x1;
    deviceManager.FilterStatus    = (StatusDevice >> FILLTER)                 & 0x1;
    deviceManager.PumpStatus      = (StatusDevice >> PUMB)                    & 0x1;
    deviceManager.HeaterStatus    = (StatusDevice >> HEATER)                  & 0x1;
    deviceManager.LightStatus     = (StatusDevice >> LIGHT)                   & 0x1;
    deviceManager.FeederStatus    = (StatusDevice >> FEEDER)                  & 0x1;
    //deviceManager.set_Auto        = (Set_Auto_t)((StatusDevice >> SET_AUTO)   & 0x1);

    ERa.virtualWrite(V5,deviceManager.FanStatus);
    ERa.virtualWrite(V6,deviceManager.HeaterStatus);
    ERa.virtualWrite(V7,deviceManager.LightStatus);
    ERa.virtualWrite(V8,deviceManager.FeederStatus);
    ERa.virtualWrite(V9,deviceManager.PumpStatus);
    ERa.virtualWrite(V10,deviceManager.FilterStatus);
    ERa.virtualWrite(V11,deviceManager.set_Auto);
    Serial.printf("Fan: %d, Heater: %d, Light: %d, Feeder: %d, Pump: %d, Filter: %d, Auto: %d\n", deviceManager.FanStatus,
                                                                                                  deviceManager.HeaterStatus,
                                                                                                  deviceManager.LightStatus,
                                                                                                  deviceManager.FeederStatus,
                                                                                                  deviceManager.PumpStatus,
                                                                                                  deviceManager.FilterStatus,
                                                                                                  deviceManager.set_Auto);
    ERa.virtualWrite(V0,atoi(dataManager.Temperature_Value));
    ERa.virtualWrite(V1,atoi(dataManager.TDS_Value));
    ERa.virtualWrite(V2,atoi(dataManager.PH_Value));
    ERa.virtualWrite(V3,atoi(dataManager.Water_Capacity));
    ERa.virtualWrite(V4,atoi(dataManager.CONDUCT_Value));
    Serial.printf("Temp: %d TDS: %d PH: %d Water: %d Conduct: %d\n",atoi(dataManager.Temperature_Value),
                                                                    atoi(dataManager.TDS_Value),
                                                                    atoi(dataManager.PH_Value),
                                                                    atoi(dataManager.Water_Capacity),
                                                                    atoi(dataManager.CONDUCT_Value));
  }
    ERa.virtualWrite(V12,FlagControl.Flag_Request_OTA);
  lv_label_set_text(ui_DoDucValue,dataManager.CONDUCT_Value);

  lv_label_set_text(ui_Phvalue,dataManager.PH_Value);

  lv_label_set_text(ui_TDSvalue,dataManager.TDS_Value);


  lv_label_set_text(ui_percentwatermask, dataManager.Water_Capacity);
  lv_label_set_text(ui_percentwater, dataManager.Water_Capacity);


  lv_label_set_text(ui_TemperatureMask,dataManager.Temperature_Value);
  lv_label_set_text(ui_Temperature,dataManager.Temperature_Value);

  if (WiFi.status() == WL_CONNECTED) ERa.run();
  
  lv_timer_handler();
  delay(10);
}

                                                                                                     