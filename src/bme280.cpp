#include "bme280.h"

Adafruit_BME280 bme; // I2C

uint8_t init_bme280()
{
    unsigned status;
    status = bme.begin(I2C_ADDRESS, &Wire);
    if (!status)
    {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x");
        Serial.println(bme.sensorID(), 16);
        return 0;
    }
    return 1;
}

float read_temperature()
{
    return bme.readTemperature();
}

float read_humidity()
{
    return bme.readHumidity();
}

float read_pressure()
{
    return bme.readPressure() / 100.0F;
}

float read_altitude()
{
    return bme.readAltitude(SEALEVELPRESSURE_HPA);
}