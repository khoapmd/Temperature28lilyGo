#pragma once

#ifndef MQTT_HELPER_H
#define MQTT_HELPER_H

#include <MQTT.h>
//#include <WiFi.h>
#include "WiFiClient.h"
#include "configHelper.h"


void sendDataMQTT(float temp, float hum);
void mqttInit();
void mqttConnect();
void mqttCheckConnectivity();
void mqttLoop();
void mqttDisconnect();
bool mqttIsConnected();

#endif 