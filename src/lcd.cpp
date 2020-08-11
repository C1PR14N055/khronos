
#include "LiquidCrystal.h"

#include <Arduino.h>
#include "icons.h"

#include "lcd.h"

// LiquidCrystal lcd(RS, E, D4, D5, D6, D7); + VCC - GND
LiquidCrystal lcd_(12, 11, 5, 4, 3, 2);

void lcd::init()
{
    // initialize lcd 16x2
    lcd_.begin(16, 2);
    // define custom icons
    lcd_.createChar((uint8_t)eIcons::_ICON_SATELLITE, ICON_SATELLITE);
    lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_0);
    lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_100);
    lcd_.createChar((uint8_t)eIcons::_ICON_DEGREES, ICON_DEGREES);
}

void lcd::print(int nPos, int nLine, const char *pszText)
{
    lcd_.setCursor(nPos, nLine);
    lcd_.print(pszText);
}

void lcd::printInt(int nPos, int nLine, int nValue, const char *pszFormat /*= NULL*/)
{
    char cc[32];
    sprintf(cc, (pszFormat) ? pszFormat : "%d", nValue);

    lcd_.setCursor(nPos, nLine);
    lcd_.print(cc);
}

void lcd::printIcon(int nPos, int nLine, eIcons icon)
{
    lcd_.setCursor(nPos, nLine);
    lcd_.write((uint8_t)icon);
}

void lcd::printSatelliteIcon(int nCol, int nRow) {
    lcd::printIcon(nCol, nRow, eIcons::_ICON_SATELLITE);
}

void lcd::printBatteryIcon(int nCol, int nRow, float nBatteryPercent)
{
    if (nBatteryPercent > 87.5) {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_100);
    }
    else if (nBatteryPercent > 62.5) {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_75);
    }
    else if (nBatteryPercent > 37.5) {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_50);
    }
    else if (nBatteryPercent > 12.5) {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_25);
    }
    else if (nBatteryPercent >= 0) {
        lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY, ICON_BATTERY_0);
    }
    lcd::printIcon(nCol, nRow, eIcons::_ICON_BATTERY);
}

void lcd::printSignalIcon(int nCol, int nRow, float nHDOP) {
    if (nHDOP > 20) {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_0);
    }
    else if (nHDOP > 10) {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_25);
    }
    else if (nHDOP > 5) {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_50);
    }
    else if (nHDOP > 2) {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_75);
    }
    else if (nHDOP >= 1) {
        lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL, ICON_SIGNAL_100);
    }
    lcd::printIcon(nCol, nRow, eIcons::_ICON_SIGNAL);
}

void lcd::printDegreesIcon(int nCol, int nRow) {
    lcd::printIcon(nCol, nRow, eIcons::_ICON_DEGREES);
}

void lcd::setCursor(int nPos, int nLine)
{
    lcd_.setCursor(nPos, nLine);
}

void lcd::clear()
{
    lcd_.clear();
}