#ifndef DeiviceConfig_h
#define DeiviceConfig_h
#include <Arduino.h>

const int SERIAL_BAUD_RATE = 115200; // Serial communication baud rate
const int I2C_FREQUENCY = 400000;    // I2C communication frequency in Hz (max)
const int DEBOUNCE_DELAY = 250;

//-----------------Pin Mapping-------------------

// OLED Pins
const byte SDA_PIN = 21; // I2C data pin for OLED display
const byte SCL_PIN = 22; // I2C clock pin for OLED display

// Buttons

const byte A_BUTTON_PIN = 19;
const byte B_BUTTON_PIN = 18;
const byte C_BUTTON_PIN = 5;

// Screen Settings
const int OLED_WIDTH = 128;  // OLED display width, in pixels
const int OLED_HEIGHT = 128; // OLED display height, in pixels
const int OLED_RST_PIN = 4;  // OLED reset pin (or -1 if sharing
const uint8_t OLED_X_OFFSET = 96;

//----------------------------------------------

#endif // DeiviceConfig_h