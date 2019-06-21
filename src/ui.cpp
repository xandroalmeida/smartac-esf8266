#include "ui.h"
#include <Wire.h>
#include <LightChrono.h> 
#include "SSD1306Wire.h"

static SSD1306Wire display(0x3c, D1, D2);
static LightChrono uiChrono; 

static unsigned char getIcon(_status st) {
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

void ui_loop() 
{
    if (uiChrono.hasPassed(100, true)) {
        
    }
}
