#include <Wire.h>
#include "Arduino.h"
#include <DeviceConfig.h>
#include "Display.h"

Display display(&Wire);

struct Button
{
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {19, 0, false};
Button button2 = {18, 0, false};
Button button3 = {5, 0, false};

// variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;
unsigned long last_button_time = 0;

void IRAM_ATTR isr1()
{
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
    button1.numberKeyPresses++;
    button1.pressed = true;
    last_button_time = button_time;
  }
}
void IRAM_ATTR isr2()
{
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
    button2.numberKeyPresses++;
    button2.pressed = true;
    last_button_time = button_time;
  }
}
void IRAM_ATTR isr3()
{
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
    button3.numberKeyPresses++;
    button3.pressed = true;
    last_button_time = button_time;
  }
}

void setup()
{
  // Setup Serial Communication
  Serial.begin(SERIAL_BAUD_RATE);
  delay(10); // wait for serial to initialize
  Serial.println("Tamagotchi-Bubby Booting...");

  // initialize the pushbutton pins as inputs:
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr1, FALLING);

  pinMode(button2.PIN, INPUT_PULLUP);
  attachInterrupt(button2.PIN, isr2, FALLING);

  pinMode(button3.PIN, INPUT_PULLUP);
  attachInterrupt(button3.PIN, isr3, FALLING);

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
  if (button1.pressed)
  {
    Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
    button1.pressed = false;
  }
  if (button2.pressed)
  {
    Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
    button2.pressed = false;
  }
  if (button3.pressed)
  {
    Serial.printf("Button 3 has been pressed %u times\n", button3.numberKeyPresses);
    button3.pressed = false;
  }
  posX++;
  if (posX >= WIDTH)
  {
    posX = 0;
  }
}
