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

Button buttonA = {A_BUTTON_PIN, 0, false};
Button buttonB = {B_BUTTON_PIN, 0, false};
Button buttonC = {C_BUTTON_PIN, 0, false};

// variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;
unsigned long last_button_time = 0;
unsigned long lastButtonPressTime = 0;

void IRAM_ATTR buttonISR()
{
  uint32_t currentMillis = millis();

  if (currentMillis - lastButtonPressTime > DEBOUNCE_DELAY)
  {
    lastButtonPressTime = currentMillis;

    // Check which button was pressed
    if (digitalRead(buttonA.PIN) == LOW)
    {
      buttonA.numberKeyPresses++;
      buttonA.pressed = true;
    }
    else if (digitalRead(buttonB.PIN) == LOW)
    {
      buttonB.numberKeyPresses++;
      buttonB.pressed = true;
    }
    else if (digitalRead(buttonC.PIN) == LOW)
    {
      buttonC.numberKeyPresses++;
      buttonC.pressed = true;
    }
  }
}

void setup()
{
  // Setup Serial Communication
  Serial.begin(SERIAL_BAUD_RATE);
  delay(10); // wait for serial to initialize
  Serial.println("Tamagotchi-Bubby Booting...");

  // initialize the pushbutton pins as inputs:
  pinMode(buttonA.PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonA.PIN), buttonISR, FALLING);

  pinMode(buttonB.PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonB.PIN), buttonISR, FALLING);

  pinMode(buttonC.PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonC.PIN), buttonISR, FALLING);

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
  if (buttonA.pressed)
  {
    display.writeString("Button A pressed", 0, 20, FontSize::small);
    er_oled_display(display.oled_buf);
    buttonA.pressed = false;
  }
  if (buttonB.pressed)
  {
    display.writeString("Button B pressed", 0, 20, FontSize::small);
    er_oled_display(display.oled_buf);
    buttonB.pressed = false;
  }
  if (buttonC.pressed)
  {
    display.writeString("Button C pressed", 0, 20, FontSize::small);
    er_oled_display(display.oled_buf);
    buttonC.pressed = false;
  }
  posX++;
  if (posX >= WIDTH)
  {
    posX = 0;
  }
}
