#pragma once

#include "TinyGPS.h"

class gpsUI
{
public:
    gpsUI();

public:
    void onLoop();

    void showGPSData();
    void printDebugLogs();

    void setEnabled(bool bFlag)
    {
        bEnabled = bFlag;
    }

    void setGps(TinyGPSPlus *pGps)
    {
        gps = pGps;
    }

protected:
    bool bEnabled;
    TinyGPSPlus *gps;
};