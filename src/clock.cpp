#include "clock.h"
#include "ui.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP, "a.ntp.br",  -60*60*3);


void clock_init() 
{
    timeClient.begin();
    ui_data.ntp_status = disconnected;
    clock_loop();
}

void clock_loop() {
  ui_data.ntp_status = timeClient.update() ? connected : disconnected;
}

String clock_getFormattedTime() {
    return timeClient.getFormattedTime();
}