#include "clockui.h"
#include "TinyGPS.h"
#include "gpsui.h"

#include "lcd.h"

void clockUI::OnLoop()
{
    if (!bEnabled)
        return;

    showDateTime();
}

void clockUI::showDateTime()
{
    TinyGPSDate d = gps->date;
    char dd[32];
    sprintf(dd, "DATE: %02d/%02d/%02d ", d.day(), d.month(), d.year());
    lcd::print(0, 0, dd);
    //    lcd.setCursor(0, 0);
     //   lcd.print(dd);

    TinyGPSTime t = gps->time;
    char tt[32];
    sprintf(tt, "TIME:   %02d:%02d:%02d ", (t.hour() + 3) % 24, t.minute(), t.second());
    //lcd.setCursor(0, 1);
    lcd::print(0, 1, tt);
}