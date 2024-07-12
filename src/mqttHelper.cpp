using namespace std;

#include "mqttHelper.h"
#include "Preferences.h"

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

void mqttInit()
{
    mqttDisconnect();
    client.begin((cConf.MQTTBroker).c_str(),  cConf.MQTTPort, netMQTT);
}

void mqttDisconnect() {
    client.disconnect();
}

bool mqttIsConnected() {
    return client.connected();
}

void mqttConnect()
{
    client.setKeepAlive(60);
    mqttInit();
    
    setWill();
    int count = 0;
    // connect to MQTT
    Serial.print("\nconnecting MQTT...");
    Serial.println(cConf.MQTTUser);
    Serial.println(cConf.MQTTPassword);
    Serial.println(cConf.MQTTBroker);
    Serial.println(cConf.MQTTPort);
    while (!client.connect(boardID, (cConf.MQTTUser).c_str(), (cConf.MQTTPassword).c_str()) && count < 5)
    {
        count ++;
        Serial.print(".");
        delay(500);
    }
    delay(30);

    if (client.connected()) {
        sendConnectionAck();
        subscribeToIOTCommands();
        Serial.print("\nConnected!");
    }

    setMQTTIcon(client.connected());
}

void sendDataMQTT(float temp, float hum)
{
    char dataToSend[256];
    sprintf(dataToSend, "{\"boardID\":\"%s\",\"temperature\":%.8f,\"humidity\":%.8f,\"displayName\":\"%s\",\"org\":\"%s\",\"dept\":\"%s\",\"room\":\"%s\",\"line\":\"%s\",\"low_temp\":%d,\"high_temp\":%d,\"low_humid\":%d,\"high_humid\":%d}", 
        boardID, temp, hum, cConf.DisplayName, cConf.Org, cConf.Dept, cConf.Room, cConf.LineNo, 20, 25, 50, 90);
    Serial.println(dataToSend);
    // client.publish("/HouJieTempControl", dataToSend);
    client.publish(cConf.MQTTTopic, dataToSend);
    client.loop();
    delay(30);
}

void mqttCheckConnectivity() {
    if (!client.connected()) {
        mqttDisconnect();
        setMQTTIcon(false);
        mqttConnect();
        Serial.print("\nRe-Connecting MQTT...");

        mqttConnect();
    } else if (!_connected) {
        _connected = true;
        setMQTTIcon(true);
    }
}

void setWill() {
    char dataToSend[150];
    // set will
    sprintf(dataToSend, "{\"status\":\"%s\", \"client\": \"%s\", \"appver\": \"%s\"}", "out", boardID, String(APPVERSION));
    client.setWill("/ConnectStatus", dataToSend, true, 2);
}

void sendConnectionAck() {
    char dataToSend[150];
    // send connection ack
    sprintf(dataToSend, "{\"status\":\"%s\", \"client\": \"%s\", \"appver\": \"%s\"}", "in", boardID, String(APPVERSION));
    client.publish("/ConnectStatus", dataToSend, true, 2);
    delay(30);
}


void mqttLoop() {
    client.loop();
}

void messageReceived(String &topic, String &payload) {
    Serial.print(payload);
    if (payload == "RESTART") {
        client.disconnect();
        ESP.restart();
    }    
}

void subscribeToIOTCommands() {
    client.unsubscribe("/ESP32TempCMD");
    client.onMessage(messageReceived);
    client.subscribe("/ESP32TempCMD");
}


