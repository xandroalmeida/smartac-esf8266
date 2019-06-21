#include "clock.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>

static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP, -60*60*3);

static time_t getNtpTime() {
  timeClient.update();
  return timeClient.getEpochTime();
}

void clock_init() 
{
    timeClient.begin();
    setSyncProvider(getNtpTime);
    setSyncInterval(300);
}

String clock_getFormattedTime() {
    return timeClient.getFormattedTime();
}