#include "clockui.h"
#include "TinyGPS.h"
#include "gpsui.h"

#include "lcd.h"

void clockUI::onLoop()
{
    if (!bEnabled)
        return;

    showClockData();
}

void clockUI::showClockData()
{
    TinyGPSTime t = gps->time;
    char tt[32];
    sprintf(tt, "TIME: %02d:%02d:%02d ", (t.hour() + 3) % 24, t.minute(), t.second());
    lcd::print(0, 0, tt);

    lcd::printIcon(15, 0, _ICON_BATTERY_50);

    TinyGPSDate d = gps->date;
    char dd[32];
    sprintf(dd, "DATE: %02d/%02d/%02d ", d.day(), d.month(), d.year());
    lcd::print(0, 1, dd);
}