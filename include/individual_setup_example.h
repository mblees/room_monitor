#ifndef INDIVIDUAL_SETUP_H
#define INDIVIDUAL_SETUP_H

// to get this to work you need to create a file called individual_setup.h in the include folder

#define DEBUG_ENABLE 1          // Change this to 1 to enable debugging
#define TIME_TO_SLEEP 20        // Time ESP32 will go to sleep (in seconds)

#define SSID ""
#define PASSWORD ""

#define MQTT_SERVER ""
#define MQTT_PORT 1883  //most likely to be 1883

#define CLIENT_ID ""  // does not really have an impact
#define MQTT_NAME ""
#define MQTT_PASS ""

#define MQTT_ESP_ID "esp_0x"

#define MQTT_TOPIC_TEMPERATURE  MQTT_ESP_ID"/temperature"
#define MQTT_TOPIC_HUMIDITY     MQTT_ESP_ID"/humidity"
#define MQTT_TOPIC_PRESSURE     MQTT_ESP_ID"/pressure"
#define MQTT_TOPIC_ALTITUDE     MQTT_ESP_ID"/altitude"
#define MQTT_TOPIC_LIGHT_STATUS MQTT_ESP_ID"/light_status"

#endif // INDIVIDUAL_SETUP_H
