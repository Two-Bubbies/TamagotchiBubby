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

class Display
{
public:
    Display(TwoWire *wire);
    void begin();

    //----Commands-----
    void write();
    void clear();
    void turnOff();
    // Clocks
    void setOscillatorFrequency(OscillatorFrequency freq);
    void setDivideRatio(DivideRatio ratio);
    void sendClockSettings();

    // Display Modes
    void setNegative();
    void setPositive();
    //--------------

    // Writing to Buffer
    void writeString(String str, uint8_t posX, uint8_t posY, FontSize fontSize = FontSize::small);

private:
    TwoWire *wire;
    uint8_t oled_buf[WIDTH * HEIGHT / 8];
    OscillatorFrequency oscFreq = OSC_POR;
    DivideRatio divRatio = DR_POR;
    void sendClockSettings();
};

#endif // DISPLAY_H
