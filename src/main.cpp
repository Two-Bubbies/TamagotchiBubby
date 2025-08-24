#include <Wire.h>
#include "Arduino.h"
#include <DeviceConfig.h>
#include "Display.h"

Display display(&Wire);

void setup()
{
  // Setup Serial Communication
  Serial.begin(SERIAL_BAUD_RATE);
  delay(10); // wait for serial to initialize
  Serial.println("Tamagotchi-Bubby Booting...");

  // Setup I2C Bus
  Wire.setPins(SDA_PIN, SCL_PIN);
  Wire.begin();
  Wire.setClock(I2C_FREQUENCY);

  // Start OLED Display
  display.begin();
}

int posX = 0;

void loop()
{
  display.writeString("Tamagotchi Bubby", posX, 0, FontSize::small);
  er_oled_display(display.oled_buf);
  er_oled_clear(display.oled_buf);
  // posX++;
  // if (posX >= WIDTH)
  // {
  //   posX = 0;
  // }
}
