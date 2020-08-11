#pragma once

#include "TinyGPSPlus.h"

class gpsUI
{
public:
    gpsUI();

public:
    void onLoop();

    void render();

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