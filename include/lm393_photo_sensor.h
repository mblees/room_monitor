#ifndef LM393_PHOTO_SENSOR_H
#define LM393_PHOTO_SENSOR_H

#include <arduino.h>

#define lm393_data_pin 4
#define ADC_RESOLUTION 4095

void init_lm393();
uint8_t is_light_on();

#endif // LM393_PHOTO_SENSOR_H