/*
LiquidCrystal Library - Hello World

Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
library works with all LCD displays that are compatible with the
Hitachi HD44780 driver. There are many of them out there, and you
can usually tell them by the 16-pin interface.

This sketch prints "Hello World!" to the LCD
and shows the time.

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
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)

http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

/*

TODO:
- Split into multiple files / libraries
- Integrate with GPS
- Galileo mode ENABLED
- Fancy animation
- Custom icons / chars in bytes
- Add I/O
- I/0 Secret combo ACM in morse
- I/0 Secret combo GPS in morse (with small random deviations)
- Add Li-ION battery support with charge / overdischarge / boost to 5V circuit
- Circuit & cables
- Case


Beitian dual BN-220 GPS:

PINOUT (Left to Right):
1. GND
(3.0V - 5.5V, typical: 5V)

*/

// include the library code:'
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "TinyGPS.h"

#include "clockui.h"
#include "gpsui.h"
#include "lcd.h"

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(RS, E, D4, D5, D6, D7); + VCC - GND
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/**
 * Connect GPS RX to Arduino TX
 * Connect GPS TX to Arduino RX
 * Set Serial1 baud rate to 9600
*/

// The TinyGPS++ object
lcd lcdInstance;
gpsUI gpsui;
clockUI clockui;
TinyGPSPlus gps;
// void initGPS()
// {
//     //Serial.begin(9600);
//     // Serial1.begin(GPS_BAUD);
// }
//static void printDateTime(TinyGPSDate &d, TinyGPSTime &t);

void setup()
{
    // set up the LCD's number of columns and rows:
    // lcd.begin(16, 2);
    // lcd.createChar(0, ICON_SATELLITE);
    // lcd.createChar(1, ICON_BATTERY_50);
    // lcd.createChar(2, ICON_DEGREES);
    // lcd.createChar(3, ICON_SIGNAL_EXCELENT);
    // lcd.home();
    // Print a message to the LCD.
    // lcd.print("K120 H180 A450");
    //initGPS();

    lcd::init();
    //Set GPS
    gpsui.setGps(&gps);
    clockui.setGps(&gps);

    gpsui.SetEnable(true);
    //    clockui.SetEnable(true);
}

void loop()
{
    if (Serial1.available())
        gps.encode(Serial1.read());

    gpsui.OnLoop();
    clockui.OnLoop();

    // printStuff();

    // if (false) {

    //     showDateTime();
    // }
    // else {
    //     showGPSData();
    // }
    // // set the cursor to column 0, line 1
    // lcd.setCursor(0, 0);
    // // print the number of seconds since reset:
    // String s = "30S/K   ";
    // s += (millis() / 100);
    // lcd.prvoid initGPS()
// {
//     //Serial.begin(9600);
//     // Serial1.begin(GPS_BAUD);
// }int(s);
    // lcd.print(" ");
}