#pragma once

#ifndef CONFIG_HELPER_H
#define CONFIG_HELPER_H

#include <Arduino.h>

class configObj {       // The class

  public:
    configObj(void) {
      // do nothing
    };
    // Access specifier
    String WIFIssid;        // Attribute (int variable)
    String WIFIpassword;  // Attribute (string variable)
    int    Lang;
    String LineNo;
    String Org;
    String Dept;
    String Room;
    String DisplayName;
    String MQTTUser;
    String MQTTPassword;
    String MQTTTopic;
    String MQTTBroker;
    String error;
    String DeviceName;

    // Specific data for this module. ExtraInformation
    double hSlope = 0;
    double hIntercept = 0;
    double tSlope = 0;
    double tIntercept = 0;
    String ntpServer = "CNSDC01.cn.globaltti.net";
    long  gmtOffset_sec = 28800; // 8 Hours, Shanghai
    int   daylightOffset_sec = 0;
    int    MQTTPort;
    bool isConfigAvailable();
    bool LoadConfiguration();
    bool SaveConfiguration();
    bool getDeviceID();
    bool getExtraInfo();
    void getNTP();
    void sd_config();
    void sd_close();
    bool getLogo();

  private:
    String wifiEncoded;
    String MQTTEncoded;
    String WIFIpasswordToUpdate;
    String MQTTpasswordToUpdate;




};



#endif 