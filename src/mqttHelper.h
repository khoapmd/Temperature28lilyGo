#pragma once

#ifndef MQTT_HELPER_H
#define MQTT_HELPER_H

#include <MQTT.h>
//#include <WiFi.h>
#include "WiFiClient.h"
#include "configHelper.h"


void sendDataMQTT(float temp, float hum, float normal);
void setup_mqtt();
void reconnect();
void setup_wifi();
void mqttLoop();
void setWill();
void sendConnectionAck();

#endif 