#pragma once

enum eIcons
{
    _ICON_SATELLITE,
    _ICON_BATTERY,
    _ICON_SIGNAL,
    _ICON_DEGREES,
};

class lcd
{
public:
    static void init();

    static void print(int nCol, int nRow, const char *pszText);
    static void printInt(int nCol, int nRow, int nValue, const char *pszFormat = 0);
    static void printSatelliteIcon(int nCol, int nRow);
    static void printBatteryIcon(int nCol, int nRow, float fBatteryPercent);
    static void printSignalIcon(int nCol, int nRow, float fHDOP);
    static void printDegreesIcon(int nCol, int nRow);
    static void setCursor(int nCol, int nRow);
    static void clear();

private:
    static void printIcon(int nCol, int nRow, eIcons icon);
};