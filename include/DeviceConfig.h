#ifndef DeiviceConfig_h
#define DeiviceConfig_h
#include <Arduino.h>

const int SERIAL_BAUD_RATE = 115200; // Serial communication baud rate
const int I2C_FREQUENCY = 800000;    // I2C communication frequency in Hz (max)

//-----------------Pin Mapping-------------------

// OLED Pins
const byte SDA_PIN = 21; // I2C data pin for OLED display
const byte SCL_PIN = 22; // I2C clock pin for OLED display

// Buttons -TODO define pins

// const byte A_BUTTON_PIN = ;
// const byte B_BUTTON_PIN = ;
// const byte C_BUTTON_PIN = ;
// const byte D_BUTTON_PIN = ;

//----------------------------------------------

#endif // DeiviceConfig_h