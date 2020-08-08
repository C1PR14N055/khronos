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
2. TX -> Goes to arduino RX
3. RX -> Goes to arduino TX
4. VCC (3.0V - 5.5V, typical: 5V)

*/

// include the library code:
#include <LiquidCrystal.h>
#include <TinyGPS++.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(RS, E, D4, D5, D6, D7); + VCC - GND
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte iconSat[] ={
    B10011,
    B01111,
    B00110,
    B01010,
    B00001,
    B00000,
    B00000,
    B00000,
};

byte BATTERY_0[] ={
    B01110,
    B11011,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111,
    B00000
};

byte BATTERY_25[] ={
    B01110,
    B11011,
    B10001,
    B10001,
    B10001,
    B11111,
    B11111,
    B00000
};

byte BATTERY_50[] ={
    B01110,
    B11011,
    B10001,
    B10001,
    B11111,
    B11111,
    B11111,
    B00000
};

byte BATTERY_75[] ={
    B01110,
    B11011,
    B10001,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000
};

byte BATTERY_100[] ={
    B01110,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

byte SIGNAL_NONE[] ={
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
};

byte SIGNAL_LOW[] ={
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B01000,
    B00000
};

byte SIGNAL_MODERATE[] ={
    B00000,
    B00000,
    B00000,
    B00000,
    B00100,
    B00100,
    B01100,
    B00000
};

byte SIGNAL_GOOD[] ={
    B00000,
    B00000,
    B00010,
    B00010,
    B00110,
    B00110,
    B01110,
    B00000
};

byte SIGNAL_EXCELENT[] ={
    B00001,
    B00001,
    B00011,
    B00011,
    B00111,
    B00111,
    B01111,
    B00000
};

byte DEGREES[] ={
    B01110,
    B01010,
    B01110,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
};




/**
 * Connect GPS RX to Arduino TX
 * Connect GPS TX to Arduino RX
 * Set Serial1 baud rate to 9600
*/

static const uint32_t GPS_BAUD = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

void initGPS()
{
    Serial.begin(9600);
    Serial1.begin(GPS_BAUD);
}

void printStuff()
{

    Serial.println(F("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
    Serial.println(F("           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
    Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));

    static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

    printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
    printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
    printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
    printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
    printInt(gps.location.age(), gps.location.isValid(), 5);
    printDateTime(gps.date, gps.time);
    printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
    printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
    printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
    printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);

    unsigned long distanceKmToLondon =
        (unsigned long)TinyGPSPlus::distanceBetween(
            gps.location.lat(),
            gps.location.lng(),
            LONDON_LAT,
            LONDON_LON
        ) / 1000;

    printInt(distanceKmToLondon, gps.location.isValid(), 9);

    double courseToLondon =
        TinyGPSPlus::courseTo(
            gps.location.lat(),
            gps.location.lng(),
            LONDON_LAT,
            LONDON_LON
        );

    printFloat(courseToLondon, gps.location.isValid(), 7, 2);

    const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

    printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

    printInt(gps.charsProcessed(), true, 6);
    printInt(gps.sentencesWithFix(), true, 10);
    printInt(gps.failedChecksum(), true, 9);
    Serial.println();
    Serial.println();
    Serial.println();


    smartDelay(1000);

    if (millis() > 5000 && gps.charsProcessed() < 10) {
        Serial.println(F("No GPS data received: check wiring"));
    }
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
    unsigned long start = millis();
    do
    {
        while (Serial1.available())
            gps.encode(Serial1.read());
    } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
    if (!valid)
    {
        while (len-- > 1)
            Serial.print('*');
        Serial.print(' ');
    }
    else
    {
        Serial.print(val, prec);
        int vi = abs((int)val);
        int flen = prec + (val < 0.0 ? 2 : 1); // . and -
        flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
        for (int i = flen; i < len; ++i)
            Serial.print(' ');
    }
    smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
    char sz[32] = "*****************";
    if (valid)
        sprintf(sz, "%ld", val);
    sz[len] = 0;
    for (int i = strlen(sz); i < len; ++i)
        sz[i] = ' ';
    if (len > 0)
        sz[len - 1] = ' ';
    Serial.print(sz);
    smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
    if (!d.isValid())
    {
        Serial.print(F("********** "));
    }
    else
    {
        char sz[32];
        sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
        Serial.print(sz);
    }

    if (!t.isValid())
    {
        Serial.print(F("******** "));
    }
    else
    {
        char sz[32];
        sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
        Serial.print(sz);
    }

    printInt(d.age(), d.isValid(), 5);
    smartDelay(0);
}

static void printStr(const char *str, int len)
{
    int slen = strlen(str);
    for (int i = 0; i < len; ++i)
        Serial.print(i < slen ? str[i] : ' ');
    smartDelay(0);
}

void showDateTime() {
    TinyGPSDate d = gps.date;
    char dd[32];
    sprintf(dd, "DATE: %02d/%02d/%02d ", d.day(), d.month(), d.year());
    lcd.setCursor(0, 0);
    lcd.print(dd);

    TinyGPSTime t = gps.time;
    char tt[32];
    sprintf(tt, "TIME:   %02d:%02d:%02d ", (t.hour() + 3) % 24, t.minute(), t.second());
    lcd.setCursor(0, 1);
    lcd.print(tt);
}

void showGPSData() {
    lcd.setCursor(0, 0);
    char ss[4];
    sprintf(ss, "%003dK", (int)gps.speed.kmph());
    lcd.print(ss);

    TinyGPSCourse c = gps.course;
    lcd.setCursor(6, 0);
    char cc[32];
    sprintf(cc, "%003d^", (int)c.deg());
    lcd.print(cc);

    lcd.setCursor(12, 0);
    lcd.print(gps.satellites.value());
    lcd.setCursor(13, 0);
    lcd.write(byte(0));

    lcd.setCursor(14, 0);
    lcd.write(byte(3));

    lcd.setCursor(15, 0);
    lcd.write(byte(1));

    lcd.setCursor(14, 1);
    lcd.write(byte(2));
}

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.createChar(0, iconSat);
    lcd.createChar(1, BATTERY_50);
    lcd.createChar(2, DEGREES);
    lcd.createChar(3, SIGNAL_EXCELENT);
    lcd.home();
    // Print a message to the LCD.
    // lcd.print("K120 H180 A450");
    initGPS();
}

void loop()
{
    printStuff();

    if (false) {

        showDateTime();
    }
    else {
        showGPSData();
    }
    // // set the cursor to column 0, line 1
    // lcd.setCursor(0, 0);
    // // print the number of seconds since reset:
    // String s = "30S/K   ";
    // s += (millis() / 100);
    // lcd.print(s);
    // lcd.print(" ");
}