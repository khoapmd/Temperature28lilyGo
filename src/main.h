
// Prototypesvoid getData();
void ui_mainScreen_screen_init();
void connectWIFI();
void sendDataMQTT(float temp, float hum);
void printWifiInfo();
void startWatchDog();
void stopWatchDog();
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
