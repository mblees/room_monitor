#include "lm393_photo_sensor.h"

void init_lm393()
{
    pinMode(lm393_data_pin, INPUT);
}

uint8_t is_light_on()
{
    if (analogRead(lm393_data_pin) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}