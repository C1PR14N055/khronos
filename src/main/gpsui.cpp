#include "gpsui.h"

#include "lcd.h"

static const uint32_t USB_BAUD = 9600;
static const uint32_t GPS_BAUD = 9600;

gpsUI::gpsUI()
{
    // Initialize
    bEnabled = false;

    gps = NULL;

    Serial.begin(USB_BAUD);  // USB serial
    Serial1.begin(GPS_BAUD); // GPS serial
}

void gpsUI::printDebugLogs()
{

    static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

    Serial.print("Sats: ");
    Serial.println(gps->satellites.value());

    Serial.print("HDOP: ");
    Serial.println(gps->hdop.hdop());

    Serial.print("Lat: ");
    Serial.print(gps->location.lat());
    Serial.print(" Lng: ");
    Serial.println(gps->location.lng());

    char cDate[128];
    sprintf(cDate, "Date: %02d/%02d/%04d", gps->date.day(), gps->date.month(), gps->date.year());
    Serial.println(cDate);
    char cTime[128];
    sprintf(cTime, "Time: %02d:%02d", gps->time.hour(), gps->time.minute());
    Serial.println(cTime);

    Serial.print("Alt: ");
    Serial.println(gps->altitude.meters());

    Serial.print("Course: ");
    Serial.println(gps->course.deg());

    Serial.print("Cardinal: ");
    Serial.println(gps->course.isValid() ? TinyGPSPlus::cardinal(gps->course.deg()) : "---");

    Serial.print("Speed km/h: ");
    Serial.println(gps->speed.kmph());

    unsigned long distanceKmToLondon =
        (unsigned long)TinyGPSPlus::distanceBetween(
            gps->location.lat(),
            gps->location.lng(),
            LONDON_LAT,
            LONDON_LON) /
        1000;

    Serial.print("Dist. to London: ");
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

    Serial.println("-----------------------------------");

    if (millis() > 5000 && gps->charsProcessed() < 10)
    {
        Serial.println(F("No GPS data received!"));
    }
}

void gpsUI::render()
{
    // Speed in KM/H
    lcd::printInt(0, 0, gps->speed.kmph(), "%03dKH");

    // Course + degrees icon
    lcd::printInt(6, 0, (int)gps->course.deg(), "%03d");
    lcd::printDegreesIcon(9, 0);

    // Nr. SATs + icon
    char cSats[64];
    sprintf(cSats, "%02d", gps->satellites.value());
    lcd::print(11, 0, cSats);
    lcd::printSatelliteIcon(13, 0);

    // HDOP (Horizontal dilution of precission)
    lcd::printSignalIcon(14, 0, (float)gps->hdop.hdop());

    // Battery level
    lcd::printBatteryIcon(15, 0, 50.7);

    // Time
    char cTimee[64];
    sprintf(cTimee, "%02d:%02d",
            gps->time.isValid() ? gps->time.minute() : 0,
            gps->time.isValid() ? gps->time.second() : 0);
    lcd::print(0, 1, cTimee);

    // Time / distance
    lcd::printArrivalTimeElapsed(7, 1, gps->speed.isValid() ? gps->speed.mps() : 0, nDistanceForATEkm);
}

int start = 0;
void gpsUI::onLoop()
{
    if (!bEnabled)
        return;

    int seconds = millis() / 1000;
    if (seconds > start + 5)
    {
        switch (nDistanceForATEkm)
        {
        case 1:
            nDistanceForATEkm = 3;
            break;
        case 3:
            nDistanceForATEkm = 5;
            break;
        case 5:
            nDistanceForATEkm = 10;
            break;
        case 10:
            nDistanceForATEkm = 20;
            break;
        default:
            nDistanceForATEkm = 1;
            break;
        }

        start = seconds;
    }

    // printDebugLogs();
    render();
}