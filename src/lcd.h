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

    static void print(int nPos, int nLine, const char *pszText);
    static void printInt(int nPos, int nLine, int nValue, const char *pszFormat = 0);
    static void printSatelliteIcon(int nCol, int nRow);
    static void printBatteryIcon(int nCol, int nRow, float nBatteryPercent);
    static void printSignalIcon(int nCol, int nRow, float nHDOP);
    static void printDegreesIcon(int nCol, int nRow);
    static void setCursor(int nPos, int nLine);
    static void clear();

private:
    static void printIcon(int nPos, int nLine, eIcons icon);
};