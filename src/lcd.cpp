
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
    lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY_0, ICON_BATTERY_0);
    lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY_25, ICON_BATTERY_25);
    lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY_50, ICON_BATTERY_50);
    lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY_75, ICON_BATTERY_75);
    lcd_.createChar((uint8_t)eIcons::_ICON_BATTERY_100, ICON_BATTERY_100);
    lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL_0, ICON_SIGNAL_0);
    lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL_25, ICON_SIGNAL_25);
    lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL_50, ICON_SIGNAL_50);
    lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL_75, ICON_SIGNAL_75);
    lcd_.createChar((uint8_t)eIcons::_ICON_SIGNAL_100, ICON_SIGNAL_100);
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

void lcd::setCursor(int nPos, int nLine)
{
    lcd_.setCursor(nPos, nLine);
}

void lcd::clear()
{
    lcd_.clear();
}