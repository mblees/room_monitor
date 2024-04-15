#include "mqtt.h"
#include "bme280.h"
#include "lm393_photo_sensor.h"
#include "individual_setup.h"
#include "deep_sleep.h"
#include <time.h>

RTC_DATA_ATTR int bootCount;
uint16_t start_time = 0;

void publish_sensor_data(void);
void setup()
{
  start_time = millis();

  Serial.begin(9600);
  #if DEBUG_ENABLE == 1
    Serial.println("Arrived in setup()");
  #endif

  init_mqtt();
  init_bme280();
  init_lm393();
  mqtt_loop();

  publish_sensor_data();
  deep_sleep(start_time);
}

void loop()
{
  // loop is never called cause of deep sleep
}

void publish_sensor_data()
{
  bootCount++;
  #if DEBUG_ENABLE == 1
    Serial.println("Boot number: " + String(bootCount));
  #endif

  // Read sensor data
  float temperature = read_temperature();
  float humidity = read_humidity();
  float pressure = read_pressure();
  float altitude = read_altitude();
  float light_status = read_photo_diode_value();

  // Create a message string to send to Serial Monitor
  char sensor_data_msg[MAX_MESSAGE_LENGTH];
  snprintf(sensor_data_msg, MAX_MESSAGE_LENGTH, "Temperature: %.2f°C, Humidity: %.2f%%, Pressure: %.2fhPa, Altitude: %.2fm, Light Status: %.2f%", temperature, humidity, pressure, altitude, light_status);
  #if DEBUG_ENABLE == 1
    Serial.println(sensor_data_msg);
  #endif
  // Publish sensor data to MQTT topics
  char mqtt_msg[10];

  dtostrf(temperature, 4, 2, mqtt_msg); // Convert float to string
  send_mqtt_message(MQTT_TOPIC_TEMPERATURE, mqtt_msg);

  dtostrf(humidity, 4, 2, mqtt_msg);
  send_mqtt_message(MQTT_TOPIC_HUMIDITY, mqtt_msg);

  dtostrf(pressure, 6, 2, mqtt_msg);
  send_mqtt_message(MQTT_TOPIC_PRESSURE, mqtt_msg);

  dtostrf(altitude, 6, 2, mqtt_msg);
  send_mqtt_message(MQTT_TOPIC_ALTITUDE, mqtt_msg);

  dtostrf(light_status, 4, 2, mqtt_msg);
  send_mqtt_message(MQTT_TOPIC_LIGHT_STATUS, mqtt_msg);

  if(bootCount == 1){
    send_mqtt_message(MQTT_TOPIC_BOOT_RESET, "1");
  }
}

