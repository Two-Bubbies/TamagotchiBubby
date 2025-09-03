#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <DeviceConfig.h>
#include <DisplayConfigs.h>
class Coordinates
{
public:
    Coordinates(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

class Dimensions
{
public:
    Dimensions(int width, int height) : width(width), height(height) {}
    int width;
    int height;
};

class Box
{
public:
    Box(Coordinates topLeftPos, Dimensions dims) : topLeft(topLeftPos), dimensions(dims) {}
    Coordinates topLeft;
    Dimensions dimensions;
};

enum IconSlotID
{
    ICON_SLOT_A = 0,
    ICON_SLOT_B = 1,
    ICON_SLOT_C = 2,
    ICON_SLOT_D = 3,

};

enum IconSetID
{
    ICON_SET_TOP = 0,
    ICON_SET_BOTTOM = 1
};

class IconSlot
{
public:
    IconSlot(Box box = Box(Coordinates(0, 0), Dimensions(16, 16))) : box(box) {};
    IconSlotID slotID;
    Box box;
    const unsigned char *bitmap = NULL;
};

class IconSet
{
public:
    IconSet(IconSetID id = ICON_SET_TOP, Box box = Box(Coordinates(0, 0), Dimensions(128, 16))) : id(id), box(box) {};
    Box box;
    IconSetID id;
    IconSlot icons[4] = {};
};

class Display : public Adafruit_SH1107
{
    using Adafruit_SH1107::Adafruit_SH1107;

public:
    void begin();
    void setOffsetX(uint8_t offset);
    // Clock settings
    void voidsetOScillatorFrequency(OscillatorFrequency freq) { this->oscFreq = freq; };
    void setDivideRatio(DivideRatio ratio) { this->divRatio = ratio; };
    void sendClockSettings();
    // Drawing and text functions
    void setCursor(Coordinates pos);
    void setCursor(int x, int y);
    void setIconSlotBitmap(IconSetID setID, IconSlotID slotID, const unsigned char *bitmap);
    void drawIcon(IconSetID setID, IconSlotID slotID);
    void clearCharacterBox();
    void clearIcons(IconSetID id);
    // Helpers
    Coordinates centerText(String text);

private:
    uint8_t offsetX = OLED_X_OFFSET;
    OscillatorFrequency oscFreq = OSC_FREQ;
    DivideRatio divRatio = DIVIDE_RATIO;
    Box characterBox = Box(Coordinates(CHARACTER_BOX_POS_X, CHARACTER_BOX_POS_Y), Dimensions(CHARACTER_BOX_WIDTH, CHARACTER_BOX_HEIGHT));
    IconSet topIcons = IconSet(ICON_SET_TOP, Box(Coordinates(TOP_ICON_SET_POS_X, TOP_ICON_SET_POS_Y), Dimensions(TOP_ICON_SET_WIDTH, TOP_ICON_SET_HEIGHT)));
    IconSet bottomIcons = IconSet(ICON_SET_BOTTOM, Box(Coordinates(BOTTOM_ICON_SET_POS_X, BOTTOM_ICON_SET_POS_Y), Dimensions(BOTTOM_ICON_SET_WIDTH, BOTTOM_ICON_SET_HEIGHT)));
    void setupIconSlots();
};

#endif // DISPLAY_H
