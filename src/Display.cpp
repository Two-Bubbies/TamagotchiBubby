#include <Arduino.h>
#include <Wire.h>
#include "Display.h"

Display::Display(TwoWire *wire = &Wire)
{
    this->wire = wire;
}

void Display::begin()
{
    er_oled_begin();
}

void Display::updateScreen()
{
    er_oled_display(this->oled_buf);
}

void Display::turnOff()
{
    command(0xAE);
}

void Display::sendClockSettings()
{
    command(0xd5);
    // TODO is this right?
    command((this->oscFreq & this->divRatio));
    Serial.println((this->oscFreq << 4 | this->divRatio), BIN);
}

void Display::setOscillatorFrequency(OscillatorFrequency freq)
{
    this->oscFreq = freq;
}

void Display::setDivideRatio(DivideRatio ratio)
{
    this->divRatio = ratio;
}

void Display::setNegative()
{
    command(0xa7);
}
void Display::setPositive()
{
    command(0xA6);
}
void Display::clear()
{
    er_oled_clear(this->oled_buf);
}

void Display::writeString(String str, uint8_t posX, uint8_t posY, FontSize fontSize)
{
    er_oled_string(posX, posY, str.c_str(), fontSize, 1, this->oled_buf);
}

// command(0xd5); // Set Frame Frequency
// command(0x50); // 104Hz