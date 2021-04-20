
#include <LiquidCrystal.h>

#include <Arduino.h>
#include "icons.h"

#include "lcd.h"

// LiquidCrystal lcd(RS, E, D4, D5, D6, D7); + VCC - GND
LiquidCrystal lcd_(12, 11, 5, 4, 3, 2);

void lcd::init()
{
    // initialize lcd 16x2
    lcd_.begin(16, 2);
    // clear
    lcd_.clear();
    // define custom icons
    lcd_.createChar((uint8_t)eIcons::_ICON_SATELLITE, ICON_SATELLITE);
    lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_100);
    lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_100);
    lcd_.createChar((uint8_t)eIcons::_ICON_DEGREES, ICON_DEGREES);
}

void lcd::print(int nCol, int nRow, const char *pszText)
{
    lcd_.setCursor(nCol, nRow);
    lcd_.print(pszText);
}

void lcd::printInt(int nCol, int nRow, int nValue, const char *pszFormat /*= NULL*/)
{
    char cc[64];
    sprintf(cc, (pszFormat) ? pszFormat : "%d", nValue);

    lcd_.setCursor(nCol, nRow);
    lcd_.print(cc);
}

void lcd::printIcon(int nCol, int nRow, eIcons icon)
{
    lcd_.setCursor(nCol, nRow);
    lcd_.write((uint8_t)icon);
}

void lcd::printSatelliteIcon(int nCol, int nRow)
{
    lcd::printIcon(nCol, nRow, eIcons::_ICON_SATELLITE);
}

void lcd::printBatteryIcon(int nCol, int nRow, float fBatteryPercent)
{
    if (fBatteryPercent > 87.5)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_100);
    }
    else if (fBatteryPercent > 62.5)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_75);
    }
    else if (fBatteryPercent > 37.5)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_50);
    }
    else if (fBatteryPercent > 12.5)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_25);
    }
    else if (fBatteryPercent >= 0)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_0);
    }
    lcd::printIcon(nCol, nRow, eIcons::_ICON_BATTERY);
}

void lcd::printSignalIcon(int nCol, int nRow, float fHDOP)
{
    if (fHDOP > 20)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_0);
    }
    else if (fHDOP > 10)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_25);
    }
    else if (fHDOP > 5)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_50);
    }
    else if (fHDOP > 2)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_75);
    }
    else if (fHDOP >= 1)
    {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_100);
    }
    lcd::printIcon(nCol, nRow, eIcons::_ICON_SIGNAL);
}

// estimated time elapsed for arrival
void lcd::printArrivalTimeElapsed(int nCol, int nRow, float nSpeedMPS, int nDistanceKM)
{
    // if speed > 1 and less than 360 km/h
    if (nSpeedMPS > 1 && nSpeedMPS < 100)
    {
        int totalSeconds = (nDistanceKM * 1000) / nSpeedMPS;
        // max time should not exceed 9M:59S
        if (totalSeconds > 599)
        {
            totalSeconds = 599;
        }
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        // calculate stuff
        char cTimeForDistance[128];
        sprintf(cTimeForDistance, "%dM%02dS/%02dK", minutes, seconds, nDistanceKM);
        lcd::print(nCol, nRow, cTimeForDistance);
    }
    else
    {
        // infinity
        char cDistance[128];
        sprintf(cDistance, "-M--S/%02dK", nDistanceKM);
        lcd::print(nCol, nRow, cDistance);
    }
}

void lcd::printDegreesIcon(int nCol, int nRow)
{
    lcd::printIcon(nCol, nRow, eIcons::_ICON_DEGREES);
}

void lcd::setCursor(int nCol, int nRow)
{
    lcd_.setCursor(nCol, nRow);
}

void lcd::clear()
{
    lcd_.clear();
}