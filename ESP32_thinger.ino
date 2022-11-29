#define THINGER_SERIAL_DEBUG
#define enable_thinger
#include <ThingerESP32.h>
#include "arduino_secrets.h"
#include <TinyGPSPlus.h>
//#include <ThingerESP32OTA.h>
#define altitude_offset 1013.25

TinyGPSPlus gps;



ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

double lat = 0.0;
double lng = 0.0;
double gps_alt = 0.0;
double gps_speed = 0.0;

void setup() {
  // open serial for debugging
  Serial.begin(115200);

  pinMode(16, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["GPIO_16"] << digitalPin(16);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}





void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    lat = gps.location.lat();
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    lng = gps.location.lng();
    Serial.println();
    gps_alt = gps.altitude.meters();
    gps_speed = gps.speed.mph();
}

thing["location"] >> [](pson &out)
  {
    out["lat"] = gps.getLatitude();
    out["lon"] = gps.getLongitude();
    out["gps_mtr"] = gps_alt;
    out["gps_speed"] = gps_speed;
   
  };
