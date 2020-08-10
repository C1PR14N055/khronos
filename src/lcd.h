#pragma once

enum eIcons
{
    _ICON_SATELLITE,
    _ICON_BATTERY_0,
    _ICON_BATTERY_25,
    _ICON_BATTERY_50,
    _ICON_BATTERY_75,
    _ICON_BATTERY_100,
    _ICON_SIGNAL_0,
    _ICON_SIGNAL_25,
    _ICON_SIGNAL_50,
    _ICON_SIGNAL_75,
    _ICON_SIGNAL_100,
    _ICON_DEGREES,
};

class lcd
{
public:
    static void init();

    static void print(int nPos, int nLine, const char *pszText);
    static void printInt(int nPos, int nLine, int nValue, const char *pszFormat = 0);
    static void printIcon(int nPos, int nLine, eIcons icon);
    static void setCursor(int nPos, int nLine);
    static void clear();
};