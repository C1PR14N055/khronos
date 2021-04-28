#include "TinyGPSPlus.h"

#include "lcd.h"
#include "clockui.h"
#include "gpsui.h"

enum FUNCTION_MODES
{
    CLOCK = 0,
    GPS = 1,
};

FUNCTION_MODES mode = CLOCK;
const int REED_PIN = A0; // Pin A0 connected to reed (magnetic switch)

// The TinyGPS++ object
gpsUI gpsui;
clockUI clockui;
TinyGPSPlus gps;

void setup()
{
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(REED_PIN, INPUT_PULLUP);

    // init LCD
    lcd::init();

    // Set GPS instance available to gpsui and clockui
    gpsui.setGps(&gps);
    clockui.setGps(&gps);

    if (mode == FUNCTION_MODES::CLOCK)
    {
        gpsui.setEnabled(true);
    }
    else
    {
        clockui.setEnabled(true);
    }
}

void blinky()
{
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
    int proximity = digitalRead(REED_PIN); // Read the state of the switch
    // switch timer
    unsigned long start = millis();
    while (proximity == LOW && millis() - start < 5000) // If the pin reads low, the switch is closed.
    {
        // waiting for 5 seconds
        blinky();
        delay(10);
    }

    if (mode == FUNCTION_MODES::CLOCK)
    {
        mode = FUNCTION_MODES::GPS;
        clockui.setEnabled(false);
        gpsui.setEnabled(true);
        Serial.print("Switch closed, GPS ENABLED");
    }
    else
    {
        mode = FUNCTION_MODES::CLOCK;
        gpsui.setEnabled(false);
        clockui.setEnabled(true);
        Serial.print("Switch opened, CLOCK ENABLED");
    }

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
