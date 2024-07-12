#pragma once

#ifndef SCREEN_HELPER_H
#define SCREEN_HELPER_H
#include "lvgl.h"
#include "Arduino.h"

#define LCD_H_RES (240)
#define LCD_V_RES (320)




void ui_mainScreen_screen_init();
void setDataDisplay(char* vTempChar, char* vHumChar, char *vIDChar);
void showMainDisplay();
void initDisplay();
void setVersion(String ver);
void setWIFIIcon(boolean bConnected);
void setMQTTIcon(boolean bConnected);

void screenRefresh();
void screenForceRefresh();
void setUpdatingIcon();
void wakeUp();
void goSleep();
void lv_ex_msgbox_1();
void showLogo();
void canRefreshScreen(bool ic);

#endif