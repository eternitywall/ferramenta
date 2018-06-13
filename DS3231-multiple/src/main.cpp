/*
* Arduino DS3231 Real Time Clock Module Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
* DS3231 Library made by Henning Karlsen which can be found and downloaded from his website, www.rinkydinkelectronics.com.
*
*/
#include <Wire.h>
#include <DS3231.h>
#include "SoftI2CMaster.h"
#include "ssd1306.h"

DS3231  rtc1(SDA, SCL);
DS3231  rtc2(2, 3);
DS3231  rtc3(4, 5);
DS3231  rtc4(6, 7);
DS3231  rtc5(8, 9);
DS3231  rtc6(10, 11);
DS3231  rtc7(12, 13);
DS3231  rtc8(A0, A1);

const uint8_t N = 8;
DS3231 clocks[N] = {rtc1,rtc2,rtc3,rtc4,rtc5,rtc6,rtc7,rtc8};

void setup()
{
  for(int i = 0; i< N; i++) {
    clocks[i].begin();
  }

  Serial.begin(115200);
  Serial.println("LCD...");

  while (! Serial);

  ssd1306_128x64_i2c_init();

} // setup()


void loop() {
 
  unsigned long start = millis(); // grab current time

  for(uint8_t i = 0; i< N; i++) {
    Serial.print(i);
    Serial.print("-");

    ssd1306_printFixed (0,  i*8, clocks[i].getDateStr(), STYLE_NORMAL);
    ssd1306_printFixed (70,  i*8, clocks[i].getTimeStr(), STYLE_NORMAL);
    Serial.print(clocks[i].getDateStr());
    Serial.print("-");
    
    Serial.println(clocks[i].getTimeStr());

  }
  Serial.println();

  delay(200);
}
