#pragma once

#include "TinyGPSPlus.h"

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

    void render();

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