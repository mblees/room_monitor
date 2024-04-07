#include "mqtt.h"
#include "bme280.h"
#include "lm393_photo_sensor.h"

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ; // time to get serial running
  delay(1000);

  init_mqtt();
  init_bme280();
  init_lm393();
}

void loop()
{
  mqtt_loop();

  // Send Sensor Data every 5 seconds
  static unsigned long lastMillis = 0;
  if (millis() - lastMillis > 5000)
  {
    lastMillis = millis();

    // Read sensor data
    float temperature = read_temperature();
    float humidity = read_humidity();
    float pressure = read_pressure();
    float altitude = read_altitude();
    float light_status = read_photo_diode_value();

    // Create a message string to send via MQTT
    char sensor_data_msg[100];
    snprintf(sensor_data_msg, 100, "Temperature: %.2f°C, Humidity: %.2f%%, Pressure: %.2fhPa, Altitude: %.2fm, Light Status: %.2f%", temperature, humidity, pressure, altitude, light_status);
    Serial.println(sensor_data_msg);

    // Publish sensor data to MQTT topic
    send_mqtt_message("Room1", sensor_data_msg);
  }
}
