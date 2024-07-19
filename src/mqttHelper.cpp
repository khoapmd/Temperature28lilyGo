using namespace std;
#include <WiFi.h>
#include "mqttHelper.h"
#include "Preferences.h"
#include "main.h"
#include <esp_task_wdt.h>

extern configObj cConf;
WiFiClient netMQTT;
MQTTClient client(256);
extern char boardID[23];
bool _connected = false;
void setWill();
void sendConnectionAck() ;

// from screen.
extern void setMQTTIcon(boolean bConnected);
void subscribeToIOTCommands();

void setup_wifi()
{

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(cConf.WIFIssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(cConf.WIFIssid, cConf.WIFIpassword);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    printWifiInfo();
}

void reconnect()
{
    setMQTTIcon(false);
    startWatchDog();
    Serial.print("Checking Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("Connected!");
    Serial.print("Attempting MQTT connection...");
    // client.setCleanSession(true);
    while (!client.connect(boardID, cConf.MQTTUser.c_str(), cConf.MQTTPassword.c_str()))
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("Connected!");
    sendConnectionAck();
    client.subscribe(String(APPPMQTTCMDTOPIC) + "/#");
}

void messageReceived(String &topic, String &payload)
{
    Serial.println("Incoming: " + topic + " - " + payload);

    if (topic.equals(String(APPPMQTTCMDTOPIC)) || topic.equals(String(APPPMQTTCMDTOPIC) + "/" + String(boardID)))
    {
        // Check if the message is "RESTART"
        if (payload.equals("RESTART"))
        {
            ESP.restart();
        }
    }
}

void setup_mqtt()
{
    client.begin(cConf.MQTTBroker.c_str(), 1883, netMQTT);
    client.onMessage(messageReceived);
    setWill();
}

void mqttLoop()
{
    if (!client.connected())
    {
        reconnect();
    }
    esp_task_wdt_reset();
    client.loop();
}

void setWill()
{
    char dataToSend[72];
    // set will
    snprintf(dataToSend, sizeof(dataToSend), "{\"status\":\"%s\", \"client\": \"%s\", \"appver\": \"%s\"}", "disconnected", boardID, String(APPVERSION));
    client.setWill(String(APPPMQTTSTSTOPIC).c_str(), dataToSend, true, 2);
}

void sendConnectionAck()
{
    char dataToSend[72];
    // send connection ack
    snprintf(dataToSend, sizeof(dataToSend), "{\"status\":\"%s\", \"client\": \"%s\", \"appver\": \"%s\"}", "connected", boardID, String(APPVERSION));
    client.publish(String(APPPMQTTSTSTOPIC), dataToSend, true, 2);
    setMQTTIcon(true);
}
void sendDataMQTT(float temp, float hum, float normal)
{
    char dataToSend[256];
    sprintf(dataToSend, "{\"boardID\":\"%s\",\"temperature\":%.8f,\"humidity\":%.8f,\"normalized\":%.8f,\"displayName\":\"%s\",\"org\":\"%s\",\"dept\":\"%s\",\"room\":\"%s\",\"line\":\"%s\"}", 
        boardID, temp, hum, normal, cConf.DisplayName, cConf.Org, cConf.Dept, cConf.Room, cConf.LineNo);
    Serial.println(dataToSend);
    // client.publish("/HouJieTempControl", dataToSend);
    client.publish(cConf.MQTTTopic, dataToSend);
    client.loop();
    delay(30);
}


