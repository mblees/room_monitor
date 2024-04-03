#ifndef BME280_H
#define BME280_H

#include <Adafruit_BME280.h>

// does not use defines in code! Uses default I2C instead.
#define SDA_PIN 21
#define SCL_PIN 22

#define I2C_ADDRESS 0x76

#define SEALEVELPRESSURE_HPA (1013.25)

void init_bme280();
float read_temperature();
float read_humidity();
float read_pressure();
float read_altitude();

#endif // BME280_H