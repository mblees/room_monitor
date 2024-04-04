#include "lm393_photo_sensor.h"

void init_lm393()
{
    pinMode(lm393_data_pin, INPUT);
}

uint8_t is_light_on()
{
    if (analogRead(lm393_data_pin) < 500)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

float read_photo_diode_value()
{
    float sensor_value = analogRead(lm393_data_pin);
    if (sensor_value == 0)
    {
        return 0;
    }
    else
    {
        return (sensor_value / ADC_RESOLUTION) * 100; // return brightness in percent
    }
}