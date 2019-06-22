#include "cloud.h"
#include "ui.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

static void callback(char* topic, byte* payload, unsigned int length) 
{
    String line2;
    for (unsigned int i = 0; i < length; i++) {
        line2.concat((char)payload[i]);
    }
    ui_data.line1 = String(topic);
    ui_data.line2 = line2;

}

static WiFiClient espClient;
static PubSubClient client("postman.cloudmqtt.com", 14716, callback, espClient);

static void cloud_reconnect()
{
    if (!client.connected())
    {
        ui_data.cloud_status = disconnected;
        String clientId = "ESP8266Client-" + ESP.getChipId();
        if (client.connect(clientId.c_str(), "zxiuzdba", "j3-jL9GPHUUO")) {
            ui_data.cloud_status = connected;
            client.publish("outTopic", "hello world");
            client.subscribe("inTopic");
        } else {
            ui_data.cloud_status = error;
            delay(100);
        }
    }
}

void cloud_loop() 
{
    cloud_reconnect();
    client.loop();
}

