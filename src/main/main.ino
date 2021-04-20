/*
LiquidCrystal Library - Hello World

 The circuit:
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* LCD VSS pin to ground
* LCD VCC pin to 5V
* 10K resistor / pott
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)

http://www.arduino.cc/en/Tutorial/LiquidCrystal

TODO:
- Galileo mode ENABLED
- Fancy animation
- Add I/O
- I/0 Secret combo ACM in morse
- I/0 Secret combo GPS in morse (with small random deviations)
- Add Li-ION battery support with charge / overdischarge / boost to 5V circuit
- Circuit & cables
- Case

Beitian dual BN-220 GPS:

PINOUT (Left to Right) with 2 holes face up:
1. GND
2. GPS TX
3. GPS RX
4. (3.0V - 5.5V, typical: 5V)

*/

#include "TinyGPSPlus.h"

#include "lcd.h"
#include "clockui.h"
#include "gpsui.h"

// The TinyGPS++ object
gpsUI gpsui;
clockUI clockui;
TinyGPSPlus gps;

void setup()
{
    lcd::init();

    // Set GPS
    gpsui.setGps(&gps);
    clockui.setGps(&gps);

    if (true)
    {
        gpsui.setEnabled(true);
    }
    else
    {
        clockui.setEnabled(true);
    }
}

void loop()
{
    // 30 FPS delay while constant read
    unsigned long start = millis();
    do
    {
        while (Serial1.available())
            gps.encode(Serial1.read());
    } while (millis() - start < 1000 / 30);

    gpsui.onLoop();
    clockui.onLoop();
}