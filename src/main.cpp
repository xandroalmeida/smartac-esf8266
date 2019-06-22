#include <Arduino.h>

#include "clock.h"
#include "wifi.h"
#include "cloud.h"
#include "ui.h"

void setup() {
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  ui_init();
  wifi_connect();
  clock_init();
  //cloud_connect();

//  MDNS.begin(deviceName.c_str());
//  MDNS.addService("smartboiler", "tcp", 80);
//  MDNS.addServiceTxt("smartboiler", "tcp", "vr", "1");
//  MDNS.addServiceTxt("smartboiler", "tcp", "pt", "http");
}

void loop() {
  clock_loop();
  cloud_loop();
  ui_update();
  delay(10);
}