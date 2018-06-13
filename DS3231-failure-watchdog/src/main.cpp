#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);

uint8_t srtc;


void setup() {
  wdt_enable(WDTO_2S);

  Wire.begin();
  Wire.beginTransmission(0x68);
  int error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);
  if (error == 0) {
    Serial.println(": RTC1 found.");
    srtc=1;
  } else {
    Serial.println(": RTC1 not found.");
    srtc=0;
  } // if}

  if (srtc) rtc.begin();

}

void loop() {
    if(srtc) {
        Serial.println(rtc.getDateStr());
        wdt_reset();
    }
    
    delay(200);
}