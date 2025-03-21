#ifndef CONFIG_H
#define CONFIG_H
#include <TFT_eSPI.h>



// Thông tin WiFi của bạn
const char* ssid_era     = "209-WINAS";
const char* password_era = "if648wgh23";


#define ERA_AUTH_TOKEN "50e4bee6-6a86-48c4-ab2d-8775ed65b6c4"


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



#endif



