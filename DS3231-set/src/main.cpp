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
  Serial.println("Input the date and time (YYMMDDhhmmss): ");


} // setup()

uint8_t parseDigits(char* str, uint8_t count)
{
    uint8_t val = 0;
    while(count-- > 0) val = (val * 10) + (*str++ - '0');
    return val;
}



void loop()
{
    static char buffer[12];
    static uint8_t char_idx = 0;

    if (char_idx == 12)
    {

        uint8_t year = parseDigits(buffer, 2);
        Serial.print(year);
        Serial.print(" ");
        uint8_t month = parseDigits(buffer + 2, 2);
        Serial.print(month);
        Serial.print(" ");
        uint8_t day = parseDigits(buffer + 4, 2);
        Serial.print(day);
        Serial.print(" ");

        uint8_t hour = parseDigits(buffer + 6, 2);
        Serial.print(hour);
        Serial.print(" ");
        uint8_t minute = parseDigits(buffer + 8, 2);
        Serial.print(minute);
        Serial.print(" ");
        uint8_t second = parseDigits(buffer + 10, 2);
        Serial.print(second);
        Serial.print(" ");

        // set the date and time

        for(int i = 0; i< N; i++) {
          clocks[i].setDate(day,month,2000+year);
          clocks[i].setTime(hour,minute,second);
        }

        Serial.println("OK ");

        char_idx = 0;
    }

    if (Serial.available())
    {
        buffer[char_idx++] = Serial.read();
    }
}
