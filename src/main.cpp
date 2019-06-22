#include <Arduino.h>

#include "clock.h"
#include "wifi.h"
#include "cloud.h"
#include "ui.h"


#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Samsung.h>

const uint16_t kIrLed = D3;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRSamsungAc ac(kIrLed);

void setup() {
  ac.begin();
  ac.off();
  ac.setFan(kSamsungAcFanLow);
  ac.setMode(kSamsungAcCool);
  ac.setTemp(25);
  ac.setSwing(false);

  ui_init();
  wifi_connect();
  clock_init();

//  MDNS.begin(deviceName.c_str());
//  MDNS.addService("smartboiler", "tcp", 80);
//  MDNS.addServiceTxt("smartboiler", "tcp", "vr", "1");
//  MDNS.addServiceTxt("smartboiler", "tcp", "pt", "http");
}

void loop() {
  ui_update();
  clock_loop();
  //cloud_loop();
  ac.on();
  ac.setMode(kSamsungAcCool);
  //ac.sendExtended();
  delay(10000);
}