#include "ui.h"
#include "clock.h"
#include <Wire.h>
#include <LightChrono.h> 
#include "SSD1306Wire.h"

static SSD1306Wire display(0x3c, D1, D2);
static LightChrono uiChrono; 
st_ui_data ui_data = {off, off, off};

static char getIcon(_status st) {
    unsigned char icon = '?';
    switch (st)
    {
    case on:
        icon =  '*';
        break;
    case off:
        icon =  'o';
        break;
    case not_configured:
        icon =  '!';
        break;
    case connected:
        icon =  '#';
        break;
    case disconnected:
        icon =  '_';
        break;
    case error:
        icon =  'E';
        break;
    default:
        break;
    }
    return icon;
}

void ui_init()
{
    display.init();
    display.flipScreenVertically();
}

void ui_update(bool force_update) 
{
    if (uiChrono.hasPassed(100, true) || force_update) {
        String line1 = "wf ";
        line1 += getIcon(ui_data.wifi_status);
        line1 += " nt ";
        line1 += getIcon(ui_data.ntp_status);
        line1 += " cl ";
        line1 += getIcon(ui_data.cloud_status);

        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 0, clock_getFormattedTime());

        display.setFont(ArialMT_Plain_16);
        display.drawString(0, 10, line1);
        display.display();
    }
}
