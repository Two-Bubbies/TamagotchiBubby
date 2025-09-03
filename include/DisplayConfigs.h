#pragma once
#ifndef DisplayConfigs_h
#define DisplayConfigs_h

#include <Arduino.h>
#include "Images/icons.h"

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
// Default display clock settings
static const OscillatorFrequency OSC_FREQ = OSC_POR;
static const DivideRatio DIVIDE_RATIO = DR_POR;

// Offset for SH1107 display
static const uint8_t OLED_X_OFFSET = 0; // 96? Actual device needs 0, simulator requires 96

// Icon  settings
static const uint8_t ICON_WIDTH = 16;
static const uint8_t ICON_HEIGHT = 16;
static const uint8_t ICON_PADDING_TOP = 4;
static const uint8_t ICON_PADDING_BOTTOM = 4;
static const uint8_t ICON_PADDING_LEFT = 8;
static const uint8_t ICON_PADDING_RIGHT = 8;

// top
static const uint8_t TOP_ICON_SET_POS_X = 0;
static const uint8_t TOP_ICON_SET_POS_Y = 0;
static const uint8_t TOP_ICON_SET_WIDTH = 128;
static const uint8_t TOP_ICON_SET_HEIGHT = 24;

// bottom
static const uint8_t BOTTOM_ICON_SET_POS_X = 0;
static const uint8_t BOTTOM_ICON_SET_POS_Y = 104;
static const uint8_t BOTTOM_ICON_SET_WIDTH = 128;
static const uint8_t BOTTOM_ICON_SET_HEIGHT = 24;

// Character box settings
static const uint8_t CHARACTER_BOX_POS_X = 0;
static const uint8_t CHARACTER_BOX_POS_Y = 20;
static const uint8_t CHARACTER_BOX_WIDTH = 128;
static const uint8_t CHARACTER_BOX_HEIGHT = 80;

// TOP ICON BITMAPS
static const unsigned char *TOP_ICON_SLOT_A_BITMAP = logo16_glcd_bmp;
static const unsigned char *TOP_ICON_SLOT_B_BITMAP = logo16_glcd_bmp;
static const unsigned char *TOP_ICON_SLOT_C_BITMAP = logo16_glcd_bmp;
static const unsigned char *TOP_ICON_SLOT_D_BITMAP = logo16_glcd_bmp;
static const unsigned char *TOP_ICON_BITMAPS[] = {TOP_ICON_SLOT_A_BITMAP, TOP_ICON_SLOT_B_BITMAP, TOP_ICON_SLOT_C_BITMAP, TOP_ICON_SLOT_D_BITMAP};
// Bottom ICON BITMAPS
static const unsigned char *BOTTOM_ICON_SLOT_A_BITMAP = logo16_glcd_bmp;
static const unsigned char *BOTTOM_ICON_SLOT_B_BITMAP = logo16_glcd_bmp;
static const unsigned char *BOTTOM_ICON_SLOT_C_BITMAP = logo16_glcd_bmp;
static const unsigned char *BOTTOM_ICON_SLOT_D_BITMAP = logo16_glcd_bmp;
static const unsigned char *BOTTOM_ICON_BITMAPS[] = {BOTTOM_ICON_SLOT_A_BITMAP, BOTTOM_ICON_SLOT_B_BITMAP, BOTTOM_ICON_SLOT_C_BITMAP, BOTTOM_ICON_SLOT_D_BITMAP};

#endif // DisplayConfigs_h