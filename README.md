# Temperature28LilyGo

## Overview

Temperature28LilyGo is an advanced IoT project for temperature and humidity monitoring using the LilyGo S3 (ESP32-S3) board and SHT20/30/40 sensors. This project combines robust hardware with sophisticated software features to create a versatile and secure monitoring solution.

## Key Features

- **Sensor Compatibility**: Works with SHT20, SHT30, and SHT40 temperature and humidity sensors
- **Wireless Connectivity**: Wi-Fi enabled for remote data transmission
- **MQTT Integration**: Publishes sensor data to an MQTT broker for easy integration with other systems
- **Secure Credential Management**: Automatic encryption of Wi-Fi and MQTT passwords
- **Device Management**: Flask-RESTX backend controls device ID and sensor calibration and supports over-the-air updates.
- **Flexible Configuration**: Uses JSON file on SD card for easy customization without reflashing

## Hardware Requirements

- LilyGo S3 (ESP32-S3) board
- SHT20, SHT30, or SHT40 temperature and humidity sensor
- Micro SD card for configuration storage

## Software Setup

### PlatformIO Configuration

Add the following to your `platformio.ini`:

```ini
build_flags = 
    '-DAPPVERSION="1.14"'
    '-DAPPUPDNAME="tempSensorLily"'
    '-DAPPENCKEY="your-encrypt-key"'
    '-DAPPDEVTYPE="TEMP"'
    '-DAPPAPIKEY="your-api-key"'
    '-DAPPAPI="http://example.com/api"'
    '-DAPPPMQTTDATATOPIC="/DATA/ESP32"'
    '-DAPPPMQTTSTSTOPIC="/ConnectStatus"'
    '-DAPPPMQTTCMDTOPIC="/ESP32TEMPCMD"'
```

Replace placeholder values with your actual settings.

### JSON Configuration

Create a `config.json` file on the SD card:

```json
{
  "wifi_ssid": "your-wifi-ssid",
  "wifi_pwd": "your-wifi-pass",
  "line_no": "0",
  "wifi_encoded": "N",
  "lang": 4,
  "org": "null",
  "mqtt_user": "mqttuser",
  "mqtt_pwd": "your-mqtt-pass",
  "mqtt_encoded": "N",
  "mqtt_broker": "192.168.0.100",
  "mqtt_port": 1883,
  "DeviceName": "null"
}
```

**Note**: On first boot, the system will encrypt `wifi_pwd` and `mqtt_pwd`, updating `wifi_encoded` and `mqtt_encoded` to "Y".

## Installation

1. **Wiring**:
   - Connect SHT sensor to LilyGo S3:
     - SDA to GPIO 21
     - SCL to GPIO 22

2. **Firmware**:
   - Clone this repository
   - Open in PlatformIO or Arduino IDE
   - Adjust code for your setup if needed
   - Flash to LilyGo S3 board

3. **Configuration**:
   - Create `config.json` with your settings
   - Save to micro SD card
   - Insert SD card into LilyGo S3

4. **OTA Setup**:
   - Set up Flask-RESTX backend (see [Backend Repository](https://github.com/khoapmd/flask-restx-backend-controller))
   - Ensure backend URL in `platformio.ini` is correct

## Usage

1. Power on the LilyGo S3 board
2. System will:
   - Encrypt credentials (first boot only)
   - Connect to Wi-Fi
   - Read, check and sync with the server then apply configuration
   - Check for OTA updates
   - Begin publishing data to MQTT broker

## Troubleshooting

- **Wi-Fi Issues**: Verify SSID and password in `config.json`
- **SD Card Problems**: Check wiring and JSON format
- **MQTT Errors**: Confirm broker settings and connectivity
- **OTA Failures**: Verify Flask-RESTX backend setup and connectivity

## Dependencies

- ESP32-S3 core libraries
- SD card library
- Wi-Fi and MQTT libraries
- SHT sensor library
- Encryption library
- Flask-RESTX backend for OTA

## Contributing

Contributions to Temperature28LilyGo are welcome!

## License

This project is licensed under the MIT License.
