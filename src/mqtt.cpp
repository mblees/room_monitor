#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect();
uint8_t is_client_connected();

void init_mqtt()
{
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    #if ENABLE_DEBUG == 1
        Serial.println("\nWiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    #endif

    client.setServer(MQTT_SERVER, MQTT_PORT);
}

void reconnect()
{
    while (!client.connected())
    {
        #if ENABLE_DEBUG == 1
            Serial.print("Attempting MQTT connection...");
        #endif

        if (client.connect(CLIENT_ID, MQTT_NAME, MQTT_PASS))
        {
            #if ENABLE_DEBUG == 1
                Serial.println("connected");
            #endif
        }
        else
        {
            #if ENABLE_DEBUG == 1
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 1 second");
            #endif

            delay(1000);
        }
    }
}

uint8_t is_client_connected()
{
    return client.connected();
}

void mqtt_loop()
{
    if (!is_client_connected())
    {
        reconnect();
    }
    client.loop();
}

void send_mqtt_message(const char *topic, const char *message)
{
    client.publish(topic, message);
}