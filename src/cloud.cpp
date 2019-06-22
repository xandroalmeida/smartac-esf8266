#include "cloud.h"
#include "ui.h"
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
        ui_data.cloud_status = disconnected;
        ui_update(true);
        String clientId = "ESP8266Client-" + ESP.getChipId();
        if (client.connect(clientId.c_str(), "zxiuzdba", "j3-jL9GPHUUO")) {
            ui_data.cloud_status = connected;
            ui_update(true);
            client.publish("outTopic", "hello world");
            client.subscribe("inTopic");
        } else {
            ui_data.cloud_status = error;
            ui_update(true);
            delay(1000);
        }
    }
}