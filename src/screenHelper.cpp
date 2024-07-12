using namespace std;

#include "screenHelper.h"
#include <configHelper.h>
// #include <JPEGDecoder.h>
//  add for lilyGo board
//  #include "logo.h"
// #include "init_code.h"
#include "pins.h"
// #include "xpt2046.h"
#include <SD_MMC.h>
#include <FS.h>

#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */

TFT_eSPI tft = TFT_eSPI();

/**
 * The pixel number in horizontal and vertical
 */

/**
 * Bit number used to represent command and parameter
 */
#define LCD_CMD_BITS (8)
#define LCD_PARAM_BITS (8)

#if USE_CALIBRATION_DATA
touch_calibration_t calibration_data[4];
#endif

/**
 * Please update the following configuration according to your LCD spec
 */
#define LCD_PIXEL_CLOCK_HZ (5 * 1000 * 1000)
#define LCD_BK_LIGHT_ON_LEVEL (1)
#define LCD_BK_LIGHT_OFF_LEVEL (!LCD_BK_LIGHT_ON_LEVEL)
#define LCD_PIN_NUM_DATA0 (LCD_DATA0_PIN)
#define LCD_PIN_NUM_DATA1 (LCD_DATA1_PIN)
#define LCD_PIN_NUM_DATA2 (LCD_DATA2_PIN)
#define LCD_PIN_NUM_DATA3 (LCD_DATA3_PIN)
#define LCD_PIN_NUM_DATA4 (LCD_DATA4_PIN)
#define LCD_PIN_NUM_DATA5 (LCD_DATA5_PIN)
#define LCD_PIN_NUM_DATA6 (LCD_DATA6_PIN)
#define LCD_PIN_NUM_DATA7 (LCD_DATA7_PIN)
#define LCD_PIN_NUM_PCLK (PCLK_PIN)
#define LCD_PIN_NUM_CS (CS_PIN)
#define LCD_PIN_NUM_DC (DC_PIN)
#define LCD_PIN_NUM_RST (RST_PIN)
#define LCD_PIN_NUM_BK_LIGHT (BK_LIGHT_PIN)

static lv_disp_drv_t disp_drv;      // contains callback functions
static lv_indev_drv_t indev_drv;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[48U * 1024U];

extern configObj cConf;

extern int loopCount;
extern int awake;

// UI Variables
lv_obj_t *ui_mainScreen;
lv_obj_t *ui_PanelDeg;
lv_obj_t *ui_LabelCent;
lv_obj_t *ui_PanelHum;
lv_obj_t *ui_LabelHum;
lv_obj_t *ui_Panelnfo;
lv_obj_t *ui_PanelID;
lv_obj_t *ui_LabelID;
lv_obj_t *ui_lblVersion;
lv_obj_t *ui_icon_wifi;
lv_obj_t *ui_icon_mqtt;
lv_obj_t *ui_icon_updating;

lv_obj_t *ui_logoScreen;
lv_obj_t *ui_logoImage;

bool bcanRefresh = true;

// XPT2046 touch(SPI, TOUCHSCREEN_CS_PIN, TOUCHSCREEN_IRQ_PIN);

static void my_disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);
static void lv_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void print_chip_info(void);

void initDisplay()
{

  // Serial.begin(115200); /* prepare for possible serial debug */ // change from 9600 to 115200 for lilyGo board
  // pinMode(PWR_ON_PIN, OUTPUT);
  // digitalWrite(PWR_ON_PIN, HIGH);
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");
#if USE_CALIBRATION_DATA
  data_init();
  data_read(calibration_data);
#endif

  // SPI.begin(TOUCHSCREEN_SCLK_PIN, TOUCHSCREEN_MISO_PIN, TOUCHSCREEN_MOSI_PIN);
  // touch.begin(240, 320);
#if USE_CALIBRATION_DATA
  touch.setCal(calibration_data[0].rawX, calibration_data[2].rawX, calibration_data[0].rawY, calibration_data[2].rawX, 240, 320); // Raw xmin, xmax, ymin, ymax, width, height
#else
  // touch.setCal(1788, 285, 1877, 311, 240, 320); // Raw xmin, xmax, ymin, ymax, width, height
  Serial.println("Use default calibration data");
#endif
  // touch.setRotation(0);
  print_chip_info();
  pinMode(PWR_EN_PIN, OUTPUT);
  digitalWrite(PWR_EN_PIN, HIGH);
  pinMode(LCD_PIN_NUM_BK_LIGHT, OUTPUT);
  digitalWrite(LCD_PIN_NUM_BK_LIGHT, LCD_BK_LIGHT_ON_LEVEL);
  delay(50);

  tft.begin();
  tft.setRotation(0);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  delay(100);

  
  lv_init();

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, 48U * 1024U);

  Serial.println("Register display driver to LVGL");
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = LCD_H_RES;
  disp_drv.ver_res = LCD_V_RES;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  // disp_drv.user_data = panel_handle;
  lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = lv_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // lv_init();
  // tft.begin();        /* TFT init */
  // tft.setRotation(0); //( 3 ); /* Landscape orientation, flipped */
  // touch.setCal(526, 3443, 750, 3377, 320, 240, 1);
  // lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 2);

  // /*Initialize the display*/
  // static lv_disp_drv_t disp_drv;
  // lv_disp_drv_init(&disp_drv);
  // /*Change the following line to your display resolution*/
  // disp_drv.hor_res = screenWidth;
  // disp_drv.ver_res = screenHeight;
  // disp_drv.flush_cb = my_disp_flush; // 刷新
  // disp_drv.draw_buf = &draw_buf;
  // lv_disp_drv_register(&disp_drv);

  // /*Initialize the (dummy) input device driver*/
  // static lv_indev_drv_t indev_drv;
  // lv_indev_drv_init(&indev_drv);
  // indev_drv.type = LV_INDEV_TYPE_POINTER;
  // indev_drv.read_cb = my_touchpad_read;
  // lv_indev_drv_register(&indev_drv);
}

void ui_mainScreen_screen_init()
{
  // static lv_style_t style_label;
  // lv_style_init(&style_label);

  lv_obj_t *scr = lv_scr_act();
  lv_obj_remove_style_all(scr);
  lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

  ui_mainScreen = lv_obj_create(scr);
  lv_obj_remove_style_all(ui_mainScreen);

  lv_obj_set_size(ui_mainScreen, lv_pct(100), lv_pct(100));
  lv_obj_clear_flag(ui_mainScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_align(ui_mainScreen, LV_ALIGN_CENTER);

  ui_PanelDeg = lv_obj_create(ui_mainScreen);
  lv_obj_set_width(ui_PanelDeg, lv_pct(100));
  lv_obj_set_height(ui_PanelDeg, lv_pct(40));
  lv_obj_set_x(ui_PanelDeg, 0);
  lv_obj_set_y(ui_PanelDeg, lv_pct(11));
  lv_obj_clear_flag(ui_PanelDeg, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_radius(ui_PanelDeg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_LabelCent = lv_label_create(ui_PanelDeg);
  lv_obj_set_width(ui_LabelCent, lv_pct(100));
  lv_obj_set_height(ui_LabelCent, lv_pct(75));
  lv_obj_set_x(ui_LabelCent, lv_pct(0));
  lv_obj_set_y(ui_LabelCent, lv_pct(20));
  lv_obj_set_align(ui_LabelCent, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(ui_LabelCent, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
  // lv_obj_set_style_text_font(ui_LabelCent, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_LabelCent, &arimo_30, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_PanelHum = lv_obj_create(ui_mainScreen);
  lv_obj_set_width(ui_PanelHum, lv_pct(100));
  lv_obj_set_height(ui_PanelHum, lv_pct(40));
  lv_obj_set_x(ui_PanelHum, 0);
  lv_obj_set_y(ui_PanelHum, lv_pct(22));
  lv_obj_set_align(ui_PanelHum, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_PanelHum, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_radius(ui_PanelHum, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_LabelHum = lv_label_create(ui_PanelHum);
  lv_obj_set_width(ui_LabelHum, lv_pct(100));
  lv_obj_set_height(ui_LabelHum, lv_pct(75));
  lv_obj_set_x(ui_LabelHum, lv_pct(0));
  lv_obj_set_y(ui_LabelHum, lv_pct(20));
  lv_obj_set_align(ui_LabelHum, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(ui_LabelHum, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
  // lv_obj_set_style_text_font(ui_LabelHum, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_LabelHum, &arimo_30, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *imgHum = lv_img_create(ui_PanelHum);

  LV_IMG_DECLARE(humi);
  lv_img_set_src(imgHum, &humi);
  lv_obj_set_x(imgHum, lv_pct(50));
  lv_obj_set_y(imgHum, lv_pct(700));
  lv_obj_align(imgHum, LV_ALIGN_LEFT_MID, 0, -5);

  lv_obj_t *img = lv_img_create(ui_PanelDeg);

  LV_IMG_DECLARE(temp);
  lv_img_set_src(img, &temp);
  lv_obj_set_x(img, lv_pct(50));
  lv_obj_set_y(img, lv_pct(700));
  lv_obj_align(img, LV_ALIGN_LEFT_MID, 0, -5);
  // add device id information

  ui_PanelID = lv_obj_create(ui_mainScreen);
  lv_obj_set_width(ui_PanelID, lv_pct(100));
  lv_obj_set_height(ui_PanelID, lv_pct(18));
  lv_obj_set_x(ui_PanelID, 0);
  lv_obj_set_y(ui_PanelID, lv_pct(52));
  lv_obj_set_align(ui_PanelID, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_PanelID, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_radius(ui_PanelID, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_LabelID = lv_label_create(ui_PanelID);

  lv_obj_set_width(ui_LabelID, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_LabelID, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_LabelID, 0);
  lv_obj_set_y(ui_LabelID, -11);
  lv_obj_set_align(ui_LabelID, LV_TEXT_ALIGN_CENTER);
  lv_obj_set_style_text_font(ui_LabelID, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_Panelnfo = lv_obj_create(ui_mainScreen);
  lv_obj_set_width(ui_Panelnfo, lv_pct(100));
  lv_obj_set_height(ui_Panelnfo, lv_pct(10));
  lv_obj_clear_flag(ui_Panelnfo, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_radius(ui_Panelnfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  // lv_obj_set_style_bg_color(ui_Panelnfo, lv_color_hex(0xCAC9C9), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Panelnfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_icon_wifi = lv_label_create(ui_Panelnfo);
  lv_label_set_text(ui_icon_wifi, LV_SYMBOL_WIFI);
  lv_obj_set_style_text_font(ui_icon_wifi, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(ui_icon_wifi, LV_ALIGN_OUT_TOP_RIGHT);
  lv_obj_set_width(ui_icon_wifi, 100); /// 1
  lv_obj_set_height(ui_icon_wifi, 22); /// 1
  lv_obj_set_x(ui_icon_wifi, 190);
  lv_obj_set_y(ui_icon_wifi, -10);
  lv_obj_set_style_text_color(ui_icon_wifi, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_icon_mqtt = lv_label_create(ui_Panelnfo);
  lv_label_set_text(ui_icon_mqtt, LV_SYMBOL_LOOP);
  lv_obj_set_style_text_font(ui_icon_mqtt, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(ui_icon_mqtt, LV_ALIGN_OUT_TOP_RIGHT);
  lv_obj_set_width(ui_icon_mqtt, 100); /// 1
  lv_obj_set_height(ui_icon_mqtt, 22); /// 1
  lv_obj_set_x(ui_icon_mqtt, 160);
  lv_obj_set_y(ui_icon_mqtt, -10);
  lv_obj_set_style_text_color(ui_icon_mqtt, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_icon_updating = lv_label_create(ui_Panelnfo);
  lv_label_set_text(ui_icon_updating, LV_SYMBOL_DOWNLOAD);
  lv_obj_set_style_text_font(ui_icon_updating, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(ui_icon_updating, LV_ALIGN_OUT_TOP_RIGHT);
  lv_obj_set_width(ui_icon_updating, 100); /// 1
  lv_obj_set_height(ui_icon_updating, 22); /// 1
  lv_obj_set_x(ui_icon_updating, 80);
  lv_obj_set_y(ui_icon_updating, -10);
  lv_obj_set_style_text_color(ui_icon_updating, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_flag(ui_icon_updating, LV_OBJ_FLAG_HIDDEN); /// Flags

  ui_lblVersion = lv_label_create(ui_Panelnfo);

  lv_obj_set_width(ui_lblVersion, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_lblVersion, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_lblVersion, -2);
  lv_obj_set_y(ui_lblVersion, -8);
  lv_obj_set_align(ui_lblVersion, LV_ALIGN_TOP_LEFT);
  // lv_obj_set_style_blend_mode(ui_lblVersion, LV_BLEND_MODE_SUBTRACTIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
  // lv_obj_set_style_opa(ui_lblVersion, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_label_set_text(ui_LabelCent, "");
  lv_label_set_text(ui_LabelHum, "");
  lv_label_set_text(ui_LabelID, "");
}

void showMainDisplay()
{
  //lv_scr_load(ui_mainScreen);
}

void setDataDisplay(char *vTempChar, char *vHumChar, char *vIDChar)
{
  //Serial.println("Before Refreshing Screen");

  lv_label_set_text(ui_LabelCent, vTempChar);
  lv_label_set_text(ui_LabelHum, vHumChar);
  lv_label_set_text(ui_LabelID, vIDChar);

   lv_obj_invalidate(ui_LabelCent);
   lv_obj_invalidate(ui_LabelHum);
   lv_obj_invalidate(ui_LabelID);


  screenForceRefresh();

  //Serial.println("After Refreshing Screen");

}

void setVersion(String ver)
{
  lv_label_set_text(ui_lblVersion, ver.c_str());
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

// /*Read the touchpad*/

// void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
// {
//   uint16_t touchX, touchY;

//   bool touched = touch.Pressed(); // tft.getTouch( &touchX, &touchY, 600 );

//   if (!touched)
//   {
//     data->state = LV_INDEV_STATE_REL;
//   }
//   else
//   {
//     // inverted because landscape
//     touchX = touch.Y();
//     touchY = 320 - touch.X();
//     if ((int)awake == 0)
//     {
//       loopCount = 0;

//     }

//     data->state = LV_INDEV_STATE_PR;

//     /*Set the coordinates*/
//     data->point.x = touchX;
//     data->point.y = touchY;

//     // Serial.print("Data x ");
//     // Serial.println(touchX);

//     // Serial.print("Data y ");
//     // Serial.println(touchY);
//   }
// }

void setWIFIIcon(boolean bConnected)
{
  lv_color_t c;
  if (bConnected)
  {
    c = lv_color_hex(0x0000FF);
  }
  else
  {
    c = lv_color_hex(0xFF0000);
  }
  lv_obj_set_style_text_color(ui_icon_wifi, c, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_invalidate(ui_icon_wifi);
  screenForceRefresh();
}

void setMQTTIcon(boolean bConnected)
{
  lv_color_t c;
  if (bConnected)
  {
    c = lv_color_hex(0x0000FF);
  }
  else
  {
    c = lv_color_hex(0xFF0000);
  }
  lv_obj_set_style_text_color(ui_icon_mqtt, c, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_invalidate(ui_icon_mqtt);
  screenForceRefresh();
}

void canRefreshScreen(bool ic)
{
  bcanRefresh = ic;
}

void screenRefresh()
{
  // if (bcanRefresh)
  //{
  //    lv_task_handler(); /* let the GUI do its work */
  lv_timer_handler();
  //}
}

void screenForceRefresh()
{
  if (bcanRefresh)
  {
    lv_refr_now(NULL);
  }
};

void setUpdatingIcon()
{
  lv_obj_clear_flag(ui_icon_updating, LV_OBJ_FLAG_HIDDEN); /// Flags
  lv_obj_invalidate(ui_icon_updating);
  screenForceRefresh();
}
/*
void goSleep()
{
  tft.writecommand(0x10);
  delay(300);
}

void wakeUp()
{
  tft.writecommand(0x11);
  delay(300);
  tft.init();
}
*/


static void lv_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{

    data->state = LV_INDEV_STATE_REL;
}

void print_chip_info(void)
{
  Serial.print("Chip: ");
  Serial.println(ESP.getChipModel());
  Serial.print("ChipRevision: ");
  Serial.println(ESP.getChipRevision());
  Serial.print("Psram size: ");
  Serial.print(ESP.getPsramSize() / 1024);
  Serial.println("KB");
  Serial.print("Flash size: ");
  Serial.print(ESP.getFlashChipSize() / 1024);
  Serial.println("KB");
  Serial.print("CPU frequency: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println("MHz");
}
