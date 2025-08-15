/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-OLEDM1.12-1
Display is Hardward I2C 2-Wire I2C Interface
Tested and worked with:
Works with Arduino 1.6.0 IDE
Test OK : Arduino DUE,Arduino mega2560
****************************************************/
#include <Wire.h>
#include "er_oled.h"
#include "Arduino.h"

/*
  == Hardware connection for 4 PIN module==
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3
  *3. SCL    ->    SCL
  *4. SDA    ->    SDA

*/

uint8_t oled_buf[WIDTH * HEIGHT / 8];

void setup()
{
  Serial.begin(115200);
  delay(1000); // wait for serial to initialize
  Serial.print("OLED Example\n");
  Wire.begin();

  /* display an image of bitmap matrix */
  er_oled_begin();
}

void loop()
{
  er_oled_clear(oled_buf);
  er_oled_bitmap(0, 0, PIC1, 128, 128, oled_buf);
  er_oled_display(oled_buf);
  delay(3000);
  command(0xa7); //--set Negative display
  delay(3000);
  command(0xa6); //--set normal display

  er_oled_clear(oled_buf);
  er_oled_bitmap(0, 0, PIC2, 128, 128, oled_buf);
  er_oled_display(oled_buf);
  delay(3000);

  command(0xa7); //--set Negative display
  delay(3000);
  command(0xa6); //--set normal display

  er_oled_clear(oled_buf);
  er_oled_bitmap(0, 0, PIC3, 128, 128, oled_buf);
  er_oled_display(oled_buf);
  delay(3000);

  command(0xa7); //--set Negative display
  delay(3000);
  command(0xa6); //--set normal display

  er_oled_clear(oled_buf);
  er_oled_bitmap(0, 2, Signal816, 16, 8, oled_buf);
  er_oled_bitmap(24, 2, Bluetooth88, 8, 8, oled_buf);
  er_oled_bitmap(40, 2, Msg816, 16, 8, oled_buf);
  er_oled_bitmap(64, 2, GPRS88, 8, 8, oled_buf);
  er_oled_bitmap(90, 2, Alarm88, 8, 8, oled_buf);
  er_oled_bitmap(112, 2, Bat816, 16, 8, oled_buf);

  er_oled_string(10, 112, "www.buydisplay.com", 12, 1, oled_buf);

  er_oled_char3216(0, 60, '1', oled_buf);
  er_oled_char3216(16, 60, '2', oled_buf);
  er_oled_char3216(32, 60, ':', oled_buf);
  er_oled_char3216(48, 60, '3', oled_buf);
  er_oled_char3216(64, 60, '4', oled_buf);
  er_oled_char3216(80, 60, ':', oled_buf);
  er_oled_char3216(96, 60, '5', oled_buf);
  er_oled_char3216(112, 60, '6', oled_buf);

  er_oled_display(oled_buf);

  delay(3000);
}
