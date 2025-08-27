#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <DeviceConfig.h>

enum OscillatorFrequency
{
    OSC_MINUS_25 = 0x0, // -25%
    OSC_MINUS_20 = 0x1, // -20%
    OSC_MINUS_15 = 0x2, // -15%
    OSC_MINUS_10 = 0x3, // -10%
    OSC_MINUS_5 = 0x4,  // -5%
    OSC_POR = 0x5,      // ƒOSC (POR)
    OSC_PLUS_5 = 0x6,   // +5%
    OSC_PLUS_10 = 0x7,  // +10%
    OSC_PLUS_15 = 0x8,  // +15%
    OSC_PLUS_20 = 0x9,  // +20%
    OSC_PLUS_25 = 0xA,  // +25%
    OSC_PLUS_30 = 0xB,  // +30%
    OSC_PLUS_35 = 0xC,  // +35%
    OSC_PLUS_40 = 0xD,  // +40%
    OSC_PLUS_45 = 0xE,  // +45%
    OSC_PLUS_50 = 0xF   // +50%
};

enum DivideRatio
{
    DR_POR = 1,
    DR_2 = 2,
    DR_3 = 3,
    DR_4 = 4,
    DR_5 = 5,
    DR_6 = 6,
    DR_7 = 7,
    DR_8 = 8,
    DR_9 = 9,
    DR_10 = 10,
    DR_11 = 11,
    DR_12 = 12,
    DR_13 = 13,
    DR_14 = 14,
    DR_15 = 15,
    DR_16 = 16
};

class CursorPosition
{
public:
    CursorPosition(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

class Display : public Adafruit_SH1107
{
    using Adafruit_SH1107::Adafruit_SH1107;

public:
    void setCursor(CursorPosition pos);
    void setCursor(int x, int y);
    void setOffsetX(uint8_t offset);
    void begin(uint8_t offsetX = 96);
    CursorPosition centerText(String text);
    // TODO: If we have a center position w/ just the character,
    // doesn't make sense to clear the whole screen
    // when we want to just clear the center character, or the icons etc.
    void clearCenter();
    void clearIcons();
};

#endif // DISPLAY_H
