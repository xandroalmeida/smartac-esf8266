#include "cloud.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

static void callback(char* topic, byte* payload, unsigned int length) 
{
}

static WiFiClient espClient;
static PubSubClient client("postman.cloudmqtt.com", 14716, callback, espClient);

void cloud_loop() 
{
    client.loop();
}

void cloud_connect()
{
    while (!client.connected())
    {
        String clientId = "ESP8266Client-" + ESP.getChipId();
        if (client.connect(clientId.c_str(), "zxiuzdba", "j3-jL9GPHUUO")) {
            client.publish("outTopic", "hello world");
            client.subscribe("inTopic");
        } else {
            Serial.print("failed to MQTT connect , rc=");
            Serial.print(client.state());
            delay(1000);
        }
    }
}