#include "configHelper.h"
#include <SD.h>
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

  File file = SD_MMC.open(configFile, "r"); // add for lilyGo board

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, file);
  file.close();
  configObj::sd_close();

  if (error)
  {
    this->error = "Failed get Data";
    Serial.println(this->error);
    return false;
  }
  serializeJson(doc, Serial);
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
  JsonDocument doc;

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
  if (SD_MMC.exists(configFile + ".new"))
  {
    SD_MMC.remove(configFile + ".new");
  }

  File file;
  file = SD_MMC.open(configFile + ".new", FILE_WRITE); 
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

  String queryURL = String(APPAPI) + "/getEspFiles?filePrefix=" + String(APPUPDNAME);
  HTTPClient client;
  client.addHeader("X-Secret-Key", String(APPAPIKEY));
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

bool configObj::checkDeviceExist()
{
  HTTPClient client;

  JsonDocument doc;
  client.addHeader("X-Secret-Key", String(APPAPIKEY));
  String queryURL = String(APPAPI) + "/checkexist?u_id=" + String(boardID) + "&device_type=" + APPDEVTYPE;

  Serial.println("Check Exist " + queryURL);

  client.begin(netConfig, queryURL.c_str());

  int httpResponseCode = client.GET();
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
  if (httpResponseCode == 204) // code no content => info not exist
  {
    Serial.println("code no content => info not exist");
    signInfo(this->DeviceName);
  }
  else if (httpResponseCode == 200)
  { // info exist, check firm_ver
    Serial.println("info exist, check firm_ver");
    JsonDocument doc;
    deserializeJson(doc, payload);
    if (String(APPVERSION) != doc["firm_ver"])
    {
      updateFirmver();
    }
  }
  else
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = payload;
    Serial.println("Response " + payload);
  }

  client.end();
  // configObj::getLogo();
  return true;
}

bool configObj::signInfo(String sensor_id)
{
  HTTPClient client;
  client.addHeader("X-Secret-Key", String(APPAPIKEY));
  String queryURL = String(APPAPI) + "/data?key=" + String(APPAPIKEY);
  Serial.println("Sign " + queryURL);
  Serial.println("Sensor_id " + sensor_id);
  client.begin(netConfig, queryURL.c_str());
  client.addHeader("Content-Type", "application/json");
  JsonDocument doc;

  doc["u_id"] = String(boardID);
  doc["device_type"] = String(APPDEVTYPE);
  doc["sensor_id"] = sensor_id;
  doc["firm_ver"] = String(APPVERSION);

  String httpRequestData;
  serializeJson(doc, httpRequestData);
  int httpResponseCode = client.POST(httpRequestData);

  if (httpResponseCode > 0)
  {
    String response = client.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
    return true;
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    return false;
  }

  client.end();
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

  JsonDocument doc;
  client.addHeader("X-Secret-Key", String(APPAPIKEY));
  String queryURL = String(APPAPI) + "/data?u_id=" + String(boardID);

  Serial.println("Get Data " + queryURL);

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
    assignIfDifferent(this->LineNo, doc, "line_no");
    assignIfDifferent(this->DisplayName, doc, "display_name");

    if (needToUpdate)
    {
      configObj::SaveConfiguration();
    }

    preferences.begin("fData", false);
    // Update slopes and intercepts
    updatePreferencesIfDifferent("hSlope", "hIntercept", this->hSlope, this->hIntercept, doc);
    updatePreferencesIfDifferent("tSlope", "tIntercept", this->tSlope, this->tIntercept, doc);

    // Update temperature values
    updateTemperatureOrHumidity("temp_limit", "tlow", "thigh", this->tlow, this->thigh, doc);

    // Update humidity values
    updateTemperatureOrHumidity("humi_limit", "hlow", "hhigh", this->hlow, this->hhigh, doc);
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

void updatePreferencesIfDifferent(const char *slopeKey, const char *interceptKey, double &currentSlope, double &currentIntercept, const JsonDocument &doc)
{
  if (doc.containsKey(slopeKey))
  {
    double newSlope = doc[slopeKey].as<double>();
    double newIntercept = doc[interceptKey].as<double>();

    if (newSlope != currentSlope || newIntercept != currentIntercept)
    {
      currentSlope = newSlope;
      currentIntercept = newIntercept;

      preferences.putDouble(slopeKey, currentSlope);
      preferences.putDouble(interceptKey, currentIntercept);
    }
  }
}

void updateTemperatureOrHumidity(const char *docKey, const char *lowKey, const char *highKey, double &currentLow, double &currentHigh, const JsonDocument &doc)
{
  if (doc.containsKey(docKey))
  {
    String input = doc[docKey].as<String>();
    int hyphenIndex = input.indexOf('-');
    if (hyphenIndex != -1)
    {
      String firstPart = input.substring(0, hyphenIndex);
      String secondPart = input.substring(hyphenIndex + 1);

      double lowValue = firstPart.toDouble();
      double highValue = secondPart.toDouble();

      if (lowValue != currentLow || highValue != currentHigh)
      {
        currentLow = lowValue;
        currentHigh = highValue;

        preferences.putDouble(lowKey, currentLow);
        preferences.putDouble(highKey, currentHigh);
      }
    }
  }
}

void updateFirmver()
{
  HTTPClient client;
  client.addHeader("X-Secret-Key", String(APPAPIKEY));
  String queryURL = String(APPAPI) + "/firmware?&u_id=" + String(boardID);
  client.begin(netConfig, queryURL.c_str());
  client.addHeader("Content-Type", "application/json");
  JsonDocument doc;
  doc["firm_ver"] = String(APPVERSION);

  String httpRequestData;
  serializeJson(doc, httpRequestData);
  Serial.print(httpRequestData);
  int httpResponseCode = client.PUT(httpRequestData);

  if (httpResponseCode > 0)
  {
    String response = client.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }
  else
  {
    Serial.print("Error on sending PUT: ");
    Serial.println(httpResponseCode);
  }

  client.end();
}