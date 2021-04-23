#include "TinyGPSPlus.h"

#include "lcd.h"
#include "clockui.h"
#include "gpsui.h"

// The TinyGPS++ object
gpsUI gpsui;
clockUI clockui;
TinyGPSPlus gps;

void setup()
{
    lcd::init();

    // Set GPS
    gpsui.setGps(&gps);
    clockui.setGps(&gps);

    if (true)
    {
        gpsui.setEnabled(true);
    }
    else
    {
        clockui.setEnabled(true);
    }
}

void loop()
{
    // 30 FPS delay while constant read
    unsigned long start = millis();
    do
    {
        while (Serial1.available())
            gps.encode(Serial1.read());
    } while (millis() - start < 1000 / 30);

    gpsui.onLoop();
    clockui.onLoop();
}