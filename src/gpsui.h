#pragma once

#include "TinyGPS.h"

class gpsUI
{
public:
    gpsUI();

public:
    void OnLoop();

    void showGPSData();
    void printStuff();

    void SetEnable(bool bFlag) {
        bEnabled=bFlag;
    }

    void setGps(TinyGPSPlus *pGps) {
        gps = pGps;
    }

protected:
    bool bEnabled;
    TinyGPSPlus *gps;
};