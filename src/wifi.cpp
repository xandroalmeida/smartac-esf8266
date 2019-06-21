#include "wifi.h"
#include <WString.h>
#include <Ticker.h>
#include <WiFiManager.h>

static String deviceName;
Ticker ledTicker;

#define STATUS_LED D4

static void ledTick()
{
  digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
}

static void configModeCallback (WiFiManager *myWiFiManager) {
  ledTicker.attach(0.2, ledTick);
}

void wifi_connect() 
{
    ledTicker.attach(0.5, ledTick);
    pinMode(STATUS_LED, OUTPUT);
    deviceName = "SmartBedroom_";
    deviceName += String(ESP.getChipId(), HEX);
    WiFiManager wifiManager;
    wifiManager.setAPCallback(configModeCallback);
    if (!wifiManager.autoConnect(deviceName.c_str())) {
        Serial.println("failed to connect and hit timeout");
        ESP.reset();
        delay(1000);
    }

    ledTicker.detach();
    digitalWrite(STATUS_LED, LOW);
}
