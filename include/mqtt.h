#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>

void init_mqtt();
void mqtt_loop();
void send_mqtt_message(const char *topic, const char *message);

#endif // MQTT_H