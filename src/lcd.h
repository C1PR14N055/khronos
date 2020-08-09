#pragma once

enum eIcons
{
    ICON_SAT, //ICON_SATELLITE
    ICON_BATT_50, //ICON_BATTERY_50
    ICON_DEG, //ICON_DEGREES
    ICON_SIGNAL, //ICON_SIGNAL_EXCELENT
};

class lcd
{
public:

    static void init();

    static void print(int nPos, int nLine, const char* pszText);
    static void printInt(int nPos, int nLine, int nValue, const char* pszFormat = 0);
    static void printIcon(int nPos, int nLine, eIcons icon);
    static void setCursor(int nPos, int nLine);
    static void clear();
};