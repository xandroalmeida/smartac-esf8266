#include "wifi.h"
#include "ui.h"
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
  ui_data.wifi_status = not_configured;
  ledTicker.attach(0.2, ledTick);
  ui_update(true);
}

void wifi_connect() 
{
    ui_data.wifi_status = disconnected;
    ui_update(true);
    pinMode(STATUS_LED, OUTPUT);
    ledTicker.attach(0.5, ledTick);
    deviceName = "SmartBedroom_";
    deviceName += String(ESP.getChipId(), HEX);
    WiFiManager wifiManager;
    wifiManager.setAPCallback(configModeCallback);
    if (!wifiManager.autoConnect(deviceName.c_str())) {
        Serial.println("failed to connect and hit timeout");
        ui_data.wifi_status = disconnected;
        ESP.reset();
        delay(1000);
    }

    ledTicker.detach();
    ui_data.wifi_status = connected;
    digitalWrite(STATUS_LED, LOW);
    ui_update(true);
}
