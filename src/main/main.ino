#include "TinyGPSPlus.h"

#include "lcd.h"
#include "clockui.h"
#include "gpsui.h"

enum FUNCTION_MODES
{
  CLOCK = 0,
  GPS = 1,
};

FUNCTION_MODES mode = FUNCTION_MODES::CLOCK;
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

  gpsui.setEnabled(false);
  clockui.setEnabled(true);

}

void loop()
{
  int proximity = digitalRead(REED_PIN); // Read the state of the switch
  // switch timer
  unsigned long switchStart = millis();
  while (proximity == LOW && millis() - switchStart <= 5000) // If the pin reads low, the switch is closed.
  {
    proximity = digitalRead(REED_PIN); 
    // waiting for 5 seconds
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
  

  if (millis() - switchStart >= 5000) {
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
  }

  // 30 FPS delay while constant read
  unsigned long gpsStart = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - gpsStart < 1000 / 30);

  gpsui.onLoop();
  clockui.onLoop();
}
