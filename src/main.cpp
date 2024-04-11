#include "mqtt.h"
#include "bme280.h"
#include "lm393_photo_sensor.h"
#include "individual_setup.h"
#include <time.h>

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define mS_TO_S_FACTOR 1000    /* Conversion factor for milliseconds to seconds */
#define TIME_TO_SLEEP 20        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount;

void do_work(void);

void setup()
{
  uint16_t start_time = millis();

  Serial.begin(9600);
  Serial.println("Arrived in setup()");

  init_mqtt();
  init_bme280();
  init_lm393();

  do_work();
  
  Serial.println("Going to sleep now");
  uint16_t time_awake = millis() - start_time;
  Serial.println("Total time awake: " + String(time_awake) + "ms");

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR - (time_awake * mS_TO_S_FACTOR));
  delay(200); // without this the deep sleep doesnt work properly
  esp_deep_sleep_start();
}

void loop()
{
  Serial.println("Arrived in loop()");
}

void do_work()
{
  mqtt_loop();

  bootCount++;
  Serial.println("Boot number: " + String(bootCount));

  // Read sensor data
  float temperature = read_temperature();
  float humidity = read_humidity();
  float pressure = read_pressure();
  float altitude = read_altitude();
  float light_status = read_photo_diode_value();

  // Create a message string to send to Serial Monitor
  char sensor_data_msg[100];
  snprintf(sensor_data_msg, 100, "Temperature: %.2f°C, Humidity: %.2f%%, Pressure: %.2fhPa, Altitude: %.2fm, Light Status: %.2f%", temperature, humidity, pressure, altitude, light_status);
  Serial.println(sensor_data_msg);

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
}
