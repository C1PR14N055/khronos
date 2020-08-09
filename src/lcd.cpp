
#include "LiquidCrystal.h"

#include <Arduino.h>
#include "icons.h"

#include "lcd.h"

LiquidCrystal lcd_(12, 11, 5, 4, 3, 2);

void lcd::init()
{
    lcd_.begin(16, 2);
    lcd_.createChar((uint8_t)eIcons::ICON_SAT, ICON_SATELLITE);
    lcd_.createChar(1, ICON_BATTERY_50);
    lcd_.createChar(2, ICON_DEGREES);
    lcd_.createChar(3, ICON_SIGNAL_EXCELENT);
    lcd_.home();
}

void lcd::print(int nPos, int nLine, const char* pszText)
{
    lcd_.setCursor(nPos, nLine);
    lcd_.print(pszText);
}

void lcd::printInt(int nPos, int nLine, int nValue, const char* pszFormat /*= NULL*/)
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