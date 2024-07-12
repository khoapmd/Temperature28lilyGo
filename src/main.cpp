using namespace std;

#include <Arduino.h>
#include <configHelper.h>
#include <ArduinoJson.h>
#include "SHT85.h"
#include <Ticker.h>
#include <screenHelper.h>
#include <WiFi.h>
#include <mqttHelper.h>
#include "pins.h"
#include <OTAHelper.h>
#include <esp_task_wdt.h>

#define WDT_TIMEOUT 300 //5 minutes

// top connector
//#define SDAPIN 16 // changes for lilyGo board
//#define SCLPIN 15 // changes for lilyGo board
#define SHT35_ADDRESS 0x44
SHT30 sht;

// comment out for lilyGo board
// #define MQ2PIN 35
// #define MQ2VCC 21
// #define LEDGREEN 16
// #define LEDRED 4
// #define LEDBLUE 17
// comment out for lilyGo board
String sVer = "Ver ";
// String vIDChar = "Device ID:  ";
char vIDChar[] = "Device ID: ";
char boardID[23];

float vTemp = 0;
float vTempOld = 0;
float vHum = 0;
float vHumOld = 0;
float TempVarition = 0.05;
float HumVarition = 1;
int awake = 1;
int loopCount = 0;
int dataCollectCount = 301;
unsigned long previousMillis;
bool alreadyGotExtInfo = false;
bool newVersionChecked = false;
bool isConnected = false;
bool bGotDeviceName = false;
int disconnectionTime = 0;

// Prototypes
void getData();
void connectWIFI();
void disconnectWifi(); // for testing
void sendDataMQTT(float temp, float hum);
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
void checkFirmware();
// void turnOff();
// void turnOn();
void startWatchDog();
void stopWatchDog();

// MQTT Needs
// WiFiClient net;
// HTTPClient httpClient;

Ticker tickerGetData(getData, 1000);
Ticker tickerFirmware(checkFirmware, 1800003, 0, MILLIS); // 30 minutes
// Ticker tickerDisconnect(disconnectWifi, 67000, 0, MILLIS); // 1 minute - For testing purposes
// Ticker tickerRestart(disconnectWifi, 6700000000, 0, MILLIS); // 30 minutes

configObj cConf = configObj();

void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */ // change from 9600 to 115200 for lilyGo board

  Serial.println("Setup Starting");

  snprintf(boardID, 23, "%llX", ESP.getEfuseMac());

  Wire.setPins(SENDORSDAPIN, SENSORSCLPIN);
  Wire.begin();
  sht.begin(SHT35_ADDRESS);
  Wire.setClock(100000);

  initDisplay();
  // canRefreshScreen(false);
  ui_mainScreen_screen_init();
  showMainDisplay();

  // showLogo(); //can not work

  sVer.concat(APPVERSION);
  setVersion(sVer);
  delay(10);
  cConf.LoadConfiguration();

  Serial.println("Setup done");

  // wifi controls
  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  // Serial.println(cConf.WIFIpassword + " - " + cConf.MQTTPassword) ;

  connectWIFI();
  delay(10);
  tickerGetData.start(); // start the ticker.
  tickerFirmware.start();
  // tickerDisconnect.start();
  // tickerRestart.start();
  
  // bGotDeviceName = cConf.getDeviceID();

  // if (bGotDeviceName) {
  //   String myDevName = cConf.DeviceName;
  //   strcat(vIDChar, myDevName.c_str());
  // }

  getData();

  startWatchDog();
  delay(100);
}

void loop()
{
  screenRefresh();

  delay(5);

  isConnected = WiFi.isConnected() && WiFi.localIP().toString() != "0.0.0.0";

  // check version (only once)
  if (isConnected)
  {
    // didn't check the new version yet!!
    if (!newVersionChecked)
    {
      checkFirmware();
      newVersionChecked = true;
    }

    if (!bGotDeviceName) {
      bGotDeviceName = cConf.getDeviceID();

      if (bGotDeviceName) {
        String myDevName = cConf.DeviceName;
        strcat(vIDChar, myDevName.c_str());
      }
    }
      
    // Didn't get extended information yet
    if (!alreadyGotExtInfo)
    {
       alreadyGotExtInfo = cConf.getExtraInfo();
    }

    // MQTT not connected!!!
    if (!mqttIsConnected())
    {
      mqttCheckConnectivity();
    }
  } else {
    vTaskDelay(2500 / portTICK_PERIOD_MS);
  }

  // tells WatchDog that it is alive! Only with network. If more than 5 minutes without it, also force restart!
   esp_task_wdt_reset();

  // Reconnect wifi - checking only connected flag....
  if (WiFi.status() != WL_CONNECTED)
  {
    connectWIFI();
    delay(100);
  }

  tickerGetData.update();

  mqttLoop();

  tickerFirmware.update();
}

void getData()
{
  char vTempChar[10];
  char vHumChar[10];
  bool sendData;
  dataCollectCount++;

  sht.read(true);

  // float tempOrg = sht.getTemperature();
  float humOrg = (sht.getHumidity() * cConf.hSlope) + cConf.hIntercept;
  float tempOrg = (sht.getTemperature() * cConf.tSlope) + cConf.tIntercept;


  if (humOrg < 0)
    humOrg = 0;
  if (tempOrg < 0)
    tempOrg = 0;

  vTemp = ((int)(tempOrg * 10.0 + 0.5) / 10.0);
  vHum = ((int)(humOrg * 10.0 + 0.5) / 10.0);

  sprintf(vTempChar, "%3.1f ℃", vTemp);

  sprintf(vHumChar, "%3.1f %%", vHum);

  // sendData = (vTemp >= vTempOld + TempVarition || vTemp <= vTempOld - TempVarition) || (vHum >= vHumOld + HumVarition || vHum <= vHumOld - HumVarition);

  setDataDisplay(vTempChar, vHumChar, vIDChar);
  //Serial.print("Temperature to Show:");
  //Serial.println(vTempChar);

  // send every 5 minutes;

  if (dataCollectCount > 300)
  {
    sendDataMQTT(vTemp, vHum);
    vTempOld = vTemp;
    vHumOld = vHum;
    dataCollectCount = 0;
  }
}

void disconnectWifi()
{ // for testing
  // if (WiFi.isConnected()) {
  //   WiFi.disconnect(false);
  // }
  // Serial.println("forced disconnect!!!");
  // mqttDisconnect();
}

void connectWIFI()
{
  // WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  // WiFi.begin("ESP32_Test", "ESP32@ttigroup");
  WiFi.begin(cConf.WIFIssid, cConf.WIFIpassword);
  Serial.println("\nConnecting ");
  delay(100);

  for (int i = 0; i < 10; i++)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(150);
    }
    else
    {
      Serial.println(WiFi.localIP().toString());
      break;
    }
  }

  delay(100);
}

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.print("Connected Network Signal Strength (RSSI): ");
  Serial.println(WiFi.RSSI()); /*Print WiFi signal strength*/
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.localIP());

  setWIFIIcon(true);
  delay(40);
  cConf.getNTP();
  screenForceRefresh();
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("Disconnected Event");
  // mqttDisconnect();
  setMQTTIcon(false);
  setWIFIIcon(false);
  screenForceRefresh();
}

void checkFirmware()
{
  if (WiFi.status() == WL_CONNECTED && WiFi.localIP().toString() != "0.0.0.0")
  {
    stopWatchDog();
    OTACheck(true);
    startWatchDog();
  }
}

void startWatchDog()
{
  // WatchDog
  Serial.println("Start WatchDog");
  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch
  
}

void stopWatchDog()
{
  Serial.println("Stopping WatchDog");
  esp_task_wdt_delete(NULL);
  esp_task_wdt_deinit();
  }