#include "mqtt.h"

const char *ssid = "KGB";
const char *password = "cLCXBX3hugb36tbD";

const char *mqtt_server = "192.168.0.226";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect();
uint8_t is_client_connected();

void init_mqtt()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_server, mqtt_port);
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        if (client.connect("ESP32Client"))
        {
            Serial.println("connected");

            client.subscribe("testTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");

            delay(5000);
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