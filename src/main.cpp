#include "mqtt.h"
#include "bme280.h"
#include "lm393_photo_sensor.h"

void setup()
{
  Serial.begin(9600);
  
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

    // Create a message string to send to Serial Monitor
    char sensor_data_msg[100];
    snprintf(sensor_data_msg, 100, "Temperature: %.2f°C, Humidity: %.2f%%, Pressure: %.2fhPa, Altitude: %.2fm, Light Status: %.2f%", temperature, humidity, pressure, altitude, light_status);
    Serial.println(sensor_data_msg);

    // Publish sensor data to MQTT topics
    char mqtt_msg[10];
    
    dtostrf(temperature, 4, 2, mqtt_msg); // Convert float to string
    send_mqtt_message("esp01/temperature", mqtt_msg);

    dtostrf(humidity, 4, 2, mqtt_msg);
    send_mqtt_message("esp01/humidity", mqtt_msg);

    dtostrf(pressure, 6, 2, mqtt_msg);
    send_mqtt_message("esp01/pressure", mqtt_msg);

    dtostrf(altitude, 6, 2, mqtt_msg);
    send_mqtt_message("esp01/altitude", mqtt_msg);

    dtostrf(light_status, 4, 2, mqtt_msg);
    send_mqtt_message("esp01/light_status", mqtt_msg);
  }
}
