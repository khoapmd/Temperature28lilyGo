#include "configHelper.h"
#include <SD.h>
#include <ArduinoJson.h>
#include "Cipher.h"
#include "SPI.h"
#include <HTTPClient.h>
#include "WiFiClient.h"
#include "Preferences.h"
#include <SD_MMC.h>
#include <FS.h>

/*
#define SD_MISO_PIN (13)
#define SD_MOSI_PIN (11)
#define SD_SCLK_PIN (12)
*/
#define BUFFERSIZE 1000

String configFile = "/config.json";
Cipher *cipher = new Cipher();
char encCode[] = APPENCKEY;
extern char boardID[23];
WiFiClient netConfig;
Preferences preferences;
bool needToUpdate = false;

void printLocalTime();

void assignIfDifferent(String &memberVar, const JsonDocument &doc, const char *key)
{
  if (doc.containsKey(key))
  {
    String newValue = doc[key].as<String>();
    if (memberVar != newValue)
    {
      memberVar = newValue;
      needToUpdate = true;
    }
  }
}

bool configObj::isConfigAvailable()
{
  // SD_MMC.begin(SD_CS);
  SD_MMC.begin("/sdcard", true);
  bool has = SD_MMC.exists(configFile);
  SD_MMC.end();
  return has;
}

bool configObj::LoadConfiguration()
{
  configObj::sd_config();

  preferences.begin("fData", false);
  this->hSlope = preferences.getDouble("hSlope", 0);
  this->hIntercept = preferences.getDouble("hIntercept", 0);
  this->tSlope = preferences.getDouble("tSlope", 0);
  this->tIntercept = preferences.getDouble("tIntercept", 0);
  preferences.end();

  // File file = SD.open(configFile); // comment out for lilyGo board
  File file = SD_MMC.open(configFile, "r"); // add for lilyGo board

  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, file);
  file.close();
  configObj::sd_close();

  if (error)
  {
    this->error = "Failed get Data";
    Serial.println(this->error);
    return false;
  }

  this->WIFIssid = doc["wifi_ssid"].as<String>();
  this->WIFIpassword = doc["wifi_pwd"].as<String>();
  this->LineNo = doc["line_no"].as<String>();
  this->wifiEncoded = doc["wifi_endcoded"].as<String>();
  this->Lang = doc["lang"] | 0;
  this->Org = doc["org"].as<String>();
  this->Dept = doc["dept"].as<String>();
  this->Room = doc["room"].as<String>();
  this->DisplayName = doc["DisplayName"].as<String>();
  this->MQTTUser = doc["mqtt_user"].as<String>();
  this->MQTTPassword = doc["mqtt_pwd"].as<String>();
  this->MQTTTopic = doc["mqtt_topic"].as<String>();
  this->MQTTEncoded = doc["mqtt_encoded"].as<String>();
  this->MQTTBroker = doc["mqtt_broker"].as<String>();
  this->MQTTPort = doc["mqtt_port"] | 0;
  this->DeviceName = doc["DeviceName"].as<String>();

  if (this->DeviceName == NULL)
  {
    this->DeviceName = "NONE";
  }

  if (this->wifiEncoded == "Y")
  {
    this->WIFIpasswordToUpdate = this->WIFIpassword;
    this->WIFIpassword = cipher->decryptString(this->WIFIpassword, encCode);
  }
  else
  {
    needToUpdate = true;
    this->WIFIpasswordToUpdate = cipher->encryptString(this->WIFIpassword, encCode);
    this->wifiEncoded = "Y";
  }

  if (this->MQTTEncoded == "Y")
  {
    this->MQTTpasswordToUpdate = this->MQTTPassword;
    this->MQTTPassword = cipher->decryptString(this->MQTTPassword, encCode);
  }
  else
  {
    needToUpdate = true;
    this->MQTTpasswordToUpdate = cipher->encryptString(this->MQTTPassword, encCode);
    this->MQTTEncoded = "Y";
  }

  Serial.println("Done");

  if (needToUpdate)
  {
    configObj::SaveConfiguration();
  }

  return true;
}

bool configObj::SaveConfiguration()
{
  StaticJsonDocument<1024> doc;

  doc["wifi_ssid"] = this->WIFIssid;
  doc["wifi_pwd"] = this->WIFIpasswordToUpdate;
  doc["line_no"] = this->LineNo;
  doc["wifi_endcoded"] = this->wifiEncoded;
  doc["lang"] = this->Lang;
  doc["org"] = this->Org;
  doc["dept"] = this->Dept;
  doc["room"] = this->Room;
  doc["DisplayName"] = this->DisplayName;
  doc["mqtt_user"] = this->MQTTUser;
  doc["mqtt_pwd"] = this->MQTTpasswordToUpdate;
  doc["mqtt_topic"] = this->MQTTTopic;
  doc["mqtt_encoded"] = this->MQTTEncoded;
  doc["mqtt_broker"] = this->MQTTBroker;
  doc["mqtt_port"] = this->MQTTPort;
  doc["DeviceName"] = this->DeviceName;

  configObj::sd_config();
  //    SD.remove(configFile);
  // First remove the "new" to craete as it.
  if (SD_MMC.exists(configFile + ".new"))
  {
    SD_MMC.remove(configFile + ".new");
  }

  File file;
  // file = SD.open(configFile + ".new", FILE_WRITE); //comment out for lilyGo board
  file = SD_MMC.open(configFile + ".new", FILE_WRITE); // add for lilyGo board
  if (serializeJson(doc, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
    return false;
  }
  // Close the file
  file.close();

  Serial.println(F("Removing old"));

  if (SD_MMC.exists(configFile + ".old"))
  {
    SD_MMC.remove(configFile + ".old");
  }

  Serial.println(F("Renaming"));
  // backup of the old
  SD_MMC.rename(configFile, configFile + ".old");
  SD_MMC.rename(configFile + ".new", configFile);

  configObj::sd_close();
  needToUpdate = false;
  return true;
}

void configObj::sd_config()
{
  // SD(SPI)
  Serial.println("Creating SPI and Configurating IO");

  SD_MMC.setPins(SD_SCK, SD_MOSI, SD_MISO);

  Serial.println("finished SPI configuration");
  bool rlst = SD_MMC.begin("/sdcard", true);
  if (!rlst)
  {
    Serial.println("SD init failed");
    Serial.println("➸ No detected SdCard");
  }
  else
  {
    Serial.println("SD init success");
    Serial.printf("➸ Detected SdCard insert: %.2f GB\r\n", SD_MMC.cardSize() / 1024.0 / 1024.0 / 1024.0);
  }

  // if (!SD.begin(SD_CS, SPI))
  // {
  //   this->error = "SD.begin failed!";

  //   Serial.println(this->error);
  //   return;
  // }
}

void configObj::sd_close()
{
  SD_MMC.end();
  SPI.end();
}

bool configObj::getLogo()
{
  return true;

  Serial.println("Checking Logo");

  bool bRet = true;
  sd_config();
  File file;

  if (SD_MMC.exists("/Logo.jpg"))
  {

    // file = SD.open("/Logo.jpg", FILE_READ); //comment out for lilyGo board
    file = SD_MMC.open("/Logo.jpg", FILE_READ); // add for lilyGo board
    if (file.size() < 10000)
    {
      file.close();
      SD_MMC.remove("/Logo.jpg");
      Serial.println("Checking Logo: File Size issue. Removing and Downloading again!");
    }
    else
    {
      Serial.println("Checking Logo: Already Exists...Leaving");
      sd_close();
      return true;
    }
  }

  size_t _totalLength;
  size_t _currentLength = 0; //

  String queryURL = "http://cnshadoop01.cn.globaltti.net:8088/getEspFiles?key=XXV7lnIse9q4YGA11pXA&filePrefix=" + String(APPUPDNAME);
  HTTPClient client;
  client.begin(netConfig, queryURL.c_str());
  int httpResponseCode = client.GET();

  if (httpResponseCode == 200)
  {
    Serial.println("Checking Logo: Creating File");

    // file = SD.open("/Logo.jpg", FILE_WRITE); //comment out for lilyGo board
    file = SD_MMC.open("/Logo.jpg", FILE_WRITE); // add for lilyGo board

    _totalLength = client.getSize();
    // transfer to local variable
    int len = _totalLength;
    // this is required to start firmware update process
    uint8_t buff[BUFFERSIZE] = {0};
    // get tcp stream
    Stream *stream = client.getStreamPtr();
    // read all data from server
    while (client.connected() && (len > 0 || len == -1))
    {
      // get available data size
      size_t size = stream->available();
      if (size)
      {
        Serial.printf("Checking Logo: Will Read Buffer: %d, %d, %d  \n", size, sizeof(buff), _totalLength);
        size_t c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
        Serial.printf("Checking Logo: Downloading Logo: %d \n", c);

        file.write(buff, c);
        Serial.printf("Checking Logo:Saving: %d \n", c);

        if (len > 0)
          len -= c;
      }
    }

    Serial.println("Checking Logo: Closing File");

    file.close();
    bRet = true;
  }
  else
  {
    bRet = false;
  }
  sd_close();
  Serial.println("Checking Logo: Finishing");

  return bRet;
}

bool configObj::getDeviceID()
{
  HTTPClient client;

  StaticJsonDocument<96> doc;

  String queryURL = String(APPAPI) + "/checkexist?key=" + String(APPAPIKEY) + "&code=" + String(boardID) + "&devicetype=" + APPDEVTYPE;

  Serial.println("Will connect " + queryURL);

  client.begin(netConfig, queryURL.c_str());

  int httpResponseCode = client.GET();

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = client.getString();

    Serial.println("Response " + payload);

    DeserializationError error = deserializeJson(doc, payload);

    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      client.end();
      return false;
    }

    if (this->DeviceName != doc["deviceName"].as<String>())
    {
      this->DeviceName = doc["deviceName"].as<String>();
      this->SaveConfiguration();
    }
  }
  else
  {
    client.end();
    return false;
  }

  client.end();

  configObj::getLogo();

  return true;
}

void configObj::getNTP()
{
  configTime(this->gmtOffset_sec, this->daylightOffset_sec, this->ntpServer.c_str());
  printLocalTime();
}

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

bool configObj::getExtraInfo()
{
  HTTPClient client;

  StaticJsonDocument<1024> doc;

  String queryURL = String(APPAPI) + "/getExtInfo?key=" + String(APPAPIKEY) + "&code=" + String(boardID);

  Serial.println("Will connect " + queryURL);

  client.begin(netConfig, queryURL.c_str());

  int httpResponseCode = client.GET();

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = client.getString();

    Serial.println("Response " + payload);

    DeserializationError error = deserializeJson(doc, payload);

    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      client.end();
      return false;
    }
    assignIfDifferent(this->Dept, doc, "dept");
    assignIfDifferent(this->Org, doc, "org");
    assignIfDifferent(this->Room, doc, "room");
    assignIfDifferent(this->LineNo, doc, "line");
    assignIfDifferent(this->DisplayName, doc, "display_name");
    
    if (needToUpdate)
    {
      configObj::SaveConfiguration();
    }

    preferences.begin("fData", false);

    // only treat if different
    if (doc.containsKey("hSlope"))
    {
      if (doc["hSlope"].as<double>() != this->hSlope || doc["hIntercept"].as<double>() != this->hIntercept)
      {
        this->hSlope = doc["hSlope"].as<double>();
        this->hIntercept = doc["hIntercept"].as<double>();
        // save for the future
        preferences.putDouble("hSlope", this->hSlope);
        preferences.putDouble("hIntercept", this->hIntercept);
      }
    }

    if (doc.containsKey("tSlope"))
    {
      // only treat if different
      if (doc["tSlope"].as<double>() != this->tSlope || doc["tIntercept"].as<double>() != this->hIntercept)
      {

        this->tSlope = doc["tSlope"].as<double>();
        this->tIntercept = doc["tIntercept"].as<double>();
        // save for the future
        preferences.putDouble("tSlope", this->tSlope);
        preferences.putDouble("tIntercept", this->tIntercept);
      }
    }
    preferences.end();
  }
  else
  {
    client.end();
    return false;
  }

  client.end();

  return true;
}