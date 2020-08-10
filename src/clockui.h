#pragma once

#include "TinyGPS.h"

class clockUI
{
public:
    clockUI()
    {
        bEnabled = false;
        gps = NULL;
    };

public:
    void onLoop();

    void showClockData();

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