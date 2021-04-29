#include "TinyGPSPlus.h"

#include "lcd.h"
#include "clockui.h"
#include "gpsui.h"

enum FUNCTION_MODES
{
  CLOCK = 0,
  GPS = 1,
  SWITCHING = 2,
};

// default mode (clock)
FUNCTION_MODES mode;
// Pin A0 connected to reed (magnetic switch)
const int REED_PIN = A0;
// RGB LED pins
const int LED_R_PIN = A1;
const int LED_G_PIN = A2;
const int LED_B_PIN = A3;
// ADC VCC BAT for Vumeter
const int ADC_VCC_BAT = A4;

// The TinyGPS++ object
gpsUI gpsui;
clockUI clockui;
TinyGPSPlus gps;

float getBatteryVoltage()
{
  // 5V max = 1023, divided by precision 1024 (10 bit ADC)
  float v_bat = analogRead(ADC_VCC_BAT);
  v_bat = 5 * v_bat / 1024;
  Serial.print("VCC BAT: ");
  Serial.print(v_bat);
  Serial.println("V");

  return v_bat;
}

void lightLED(bool light)
{
  digitalWrite(LED_BUILTIN, light ? HIGH : LOW);
}

// R - lred G - green B - blue, start = start millis(), time = total todo
void lightRGB(bool R, bool G, bool B)
{
  digitalWrite(LED_R_PIN, R ? HIGH : LOW);
  digitalWrite(LED_G_PIN, G ? HIGH : LOW);
  digitalWrite(LED_B_PIN, B ? HIGH : LOW);
}

// main.ino render access to LCD
void postRender()
{
  float v_bat_percent = getBatteryVoltage() * 100 / 5;
  // Battery level
  lcd::printBatteryIcon(15, 0, v_bat_percent);
}

void setup()
{
  // init magnetic switch pin as input
  pinMode(REED_PIN, INPUT_PULLUP);

  // init digital pin LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // init RGB LED pins as outputs
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  // init ADC
  pinMode(ADC_VCC_BAT, INPUT);

  // init LCD
  lcd::init();

  // lcd clear screen
  lcd::clear();

  // Set GPS instance available to gpsui and clockui
  gpsui.setGps(&gps);
  clockui.setGps(&gps);

  // se default to CLOCK
  mode = FUNCTION_MODES::CLOCK;
  gpsui.setEnabled(false);
  clockui.setEnabled(true);
}

void loop()
{
  FUNCTION_MODES prevMode = mode;
  // Read the state of the switch
  int proximity = digitalRead(REED_PIN);
  // switch timer
  unsigned long switchStart = millis();
  // If the pin reads low for 5 seconds, the switch is closed
  while (proximity == LOW && millis() - switchStart <= 5000)
  {
    // waiting for 5 seconds while magnet still close
    proximity = digitalRead(REED_PIN);
    // blink RGB
    lightRGB(false, false, true);
  }

  // If the timer passed the 5 second mark
  if (millis() - switchStart >= 5000)
  {
    // lcd clear screen
    lcd::clear();
    
    // toggle modes
    switch (prevMode)
    {
      case FUNCTION_MODES::SWITCHING:
        // nothing
        break;
      case FUNCTION_MODES::CLOCK:
        mode = FUNCTION_MODES::GPS;
        clockui.setEnabled(false);
        gpsui.setEnabled(true);
        Serial.print("Switch closed, GPS ENABLED");
        break;
      case FUNCTION_MODES::GPS:
        mode = FUNCTION_MODES::CLOCK;
        gpsui.setEnabled(false);
        clockui.setEnabled(true);
        Serial.print("Switch opened, CLOCK ENABLED");
        break;
      default:
        mode = FUNCTION_MODES::CLOCK;
        break;
    }
  }

  // 30 FPS delay while constant read
  unsigned long gpsStart = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - gpsStart < 1000 / 10);

  // gps main loop
  gpsui.onLoop();
  // clock main loop
  clockui.onLoop();

  // post-render => battery info
  postRender();
  // show RGB LED status
  if (mode == FUNCTION_MODES::CLOCK){
    lightRGB(true, false, false);
  } else if (mode == FUNCTION_MODES::GPS){
    lightRGB(false, true, false);
  }
  
}
