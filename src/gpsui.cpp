#include "gpsui.h"

#include "lcd.h"

static const uint32_t GPS_BAUD = 9600;

gpsUI::gpsUI()
{
    // Initialize
    bEnabled = false;

    gps = NULL;

    Serial.begin(9600); // usb serial
    Serial1.begin(GPS_BAUD);
}

void gpsUI::printDebugLogs()
{

    static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

    // TODO: print int / double / float
    Serial.print("Sats: ");
    Serial.println(gps->satellites.value());

    Serial.print("HDOP: ");
    Serial.println(gps->hdop.hdop());

    Serial.print("Lat: ");
    Serial.print(gps->location.lat());
    Serial.print(" Lng: ");
    Serial.println(gps->location.lng());

    char cDate[16];
    sprintf(cDate, "Date: %02d/%02d/%04d", gps->date.day(), gps->date.month(), gps->date.year());
    Serial.println(cDate);
    char cTime[16];
    sprintf(cTime, "Time: %02d:%02d", gps->time.hour(), gps->time.minute());
    Serial.println(cTime);

    Serial.print("Alt: ");
    Serial.println(gps->altitude.meters());

    Serial.print("Course: ");
    Serial.println(gps->course.deg());

    Serial.print("Cardinal: ");
    Serial.println(gps->course.isValid() ? TinyGPSPlus::cardinal(gps->course.deg()) : "---");

    Serial.print("Speed: ");
    Serial.print(gps->speed.kmph());

    unsigned long distanceKmToLondon =
        (unsigned long)TinyGPSPlus::distanceBetween(
            gps->location.lat(),
            gps->location.lng(),
            LONDON_LAT,
            LONDON_LON) /
        1000;

    Serial.print("Dist. to Londond: ");
    Serial.println(distanceKmToLondon);

    double courseToLondon =
        TinyGPSPlus::courseTo(
            gps->location.lat(),
            gps->location.lng(),
            LONDON_LAT,
            LONDON_LON);

    Serial.print("Course to London: ");
    Serial.println(courseToLondon);

    const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

    Serial.print("Cardinal to London: ");
    Serial.println(gps->location.isValid() ? cardinalToLondon : "---");

    Serial.print("Chars. processed: ");
    Serial.println(gps->charsProcessed());

    Serial.print("Sentences with fix: ");
    Serial.println(gps->sentencesWithFix());

    Serial.print("Failed checksum: ");
    Serial.println(gps->failedChecksum());

    if (millis() > 5000 && gps->charsProcessed() < 10)
    {
        Serial.println(F("No GPS data received!"));
    }
}

void gpsUI::showGPSData()
{
    // Speed in KM/H
    lcd::printInt(0, 0, gps->speed.kmph(), "%03dK");

    // Degrees
    TinyGPSCourse c = gps->course;
    lcd::printInt(6, 0, (int)c.deg(), "%03d");

    // Nr. SATs + icon
    char cSats[2];
    sprintf(cSats, "%02d", gps->satellites.value());
    lcd::printInt(10, 0, cSats);
    lcd::printIcon(12, 0, eIcons::_ICON_SATELLITE);
    // HDOP
    lcd::printIcon(13, 1, eIcons::_ICON_SIGNAL_0);
    // Battery level
    lcd::printIcon(14, 1, eIcons::_ICON_BATTERY_0);
}

void gpsUI::onLoop()
{
    if (!bEnabled)
        return;

    printDebugLogs();
    showGPSData();
}