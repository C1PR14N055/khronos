#include "clockui.h"

#include "lcd.h"

void clockUI::render()
{
    char cTime[16];
    sprintf(cTime, "TIME: %02d:%02d:%02d ", gps->time.hour(), gps->time.minute(), gps->time.second());
    lcd::print(0, 0, cTime);

    char cDate[16];
    sprintf(cDate, "DATE: %02d/%02d/%02d ", gps->date.day(), gps->date.month(), gps->date.year());
    lcd::print(0, 1, cDate);
}

void clockUI::onLoop()
{
    if (!bEnabled)
        return;

    render();
}