#include <Wire.h>
#include "Arduino.h"
#include <DeviceConfig.h>
#include "Display.h"

struct Button
{
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button buttonA = {A_BUTTON_PIN, 0, false};
Button buttonB = {B_BUTTON_PIN, 0, false};
Button buttonC = {C_BUTTON_PIN, 0, false};
Display display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RST_PIN);

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

Coordinates cursorPos(16, 64);

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
  display.clearDisplay();
  display.setCursor(0, 64);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.print("Tamagotchi-Bubby");
  display.display();
  delay(1000);
  display.drawIcon(ICON_SET_TOP, ICON_SLOT_A);
  display.drawIcon(ICON_SET_TOP, ICON_SLOT_B);
  display.drawIcon(ICON_SET_TOP, ICON_SLOT_C);
  display.drawIcon(ICON_SET_TOP, ICON_SLOT_D);
  display.drawIcon(ICON_SET_BOTTOM, ICON_SLOT_A);
  display.drawIcon(ICON_SET_BOTTOM, ICON_SLOT_B);
  display.drawIcon(ICON_SET_BOTTOM, ICON_SLOT_C);
  display.drawIcon(ICON_SET_BOTTOM, ICON_SLOT_D);
  display.display();
}

void loop()
{
  if (buttonA.pressed)
  {
    buttonA.pressed = false;
    display.clearDisplay();
    const String message = "Button A pressed";
    display.setCursor(display.centerText(message));
    display.print(message);
    display.display();
  }
  if (buttonB.pressed)
  {
    buttonB.pressed = false;
    display.clearDisplay();
    const String message = "Button B pressed";
    display.setCursor(display.centerText(message));
    display.print(message);
    display.display();
  }
  if (buttonC.pressed)
  {
    buttonC.pressed = false;
    display.clearDisplay();
    const String message = "Button C pressed";
    display.setCursor(display.centerText(message));
    display.print(message);
    display.display();
  }
}
