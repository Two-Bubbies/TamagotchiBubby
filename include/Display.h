#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <er_oled.h>

// TODO: what is mode?
enum FontSize
{
    small = 12,
    large = 16
};

class Display
{
public:
    Display(TwoWire *wire);
    void begin();
    void setNegative();
    void setPositive();
    void clear();
    void writeString(String str, uint8_t posX, uint8_t posY, FontSize fontSize = FontSize::small);
    uint8_t oled_buf[WIDTH * HEIGHT / 8];

private:
    TwoWire *wire;
    // uint8_t oled_buf[WIDTH * HEIGHT / 8];
};

#endif // DISPLAY_H
