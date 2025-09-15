#include <Arduino.h>
#include <Display.h>
#include <DeviceConfig.h>

void Display::setupIconSlots()
{
    int length = sizeof(TOP_ICON_BITMAPS) / sizeof(TOP_ICON_BITMAPS[0]);
    for (size_t i = 0; i < length; i++)
    {
        // TOP
        IconSlotID id = IconSlotID(i);
        int height = ICON_HEIGHT;
        int width = ICON_WIDTH;

        int posXTop = this->topIcons.box.topLeft.x + ICON_PADDING_LEFT + ((i) * (ICON_WIDTH + ICON_PADDING_LEFT)) + (i != 0 ? (ICON_PADDING_RIGHT * i) : 0);
        int posYTop = TOP_ICON_SET_POS_Y + ICON_PADDING_TOP;
        this->topIcons.icons[id].slotID = id;
        this->topIcons.icons[id].box = Box(Coordinates(posXTop, posYTop), Dimensions(width, height));
        this->topIcons.icons[id].bitmap = TOP_ICON_BITMAPS[i];
        Serial.println("Icon Slot " + String(i) + ": PosX: " + String(posXTop) + ", PosY: " + String(posYTop) + ", Width: " + String(width) + ", Height: " + String(height));

        // BOTTOM
        int posXBottom = this->bottomIcons.box.topLeft.x + ICON_PADDING_LEFT + ((i) * (ICON_WIDTH + ICON_PADDING_LEFT)) + (i != 0 ? (ICON_PADDING_RIGHT * i) : 0);
        int posYBottom = BOTTOM_ICON_SET_POS_Y + ICON_PADDING_BOTTOM;
        int heightBottom = ICON_HEIGHT + ICON_PADDING_TOP + ICON_PADDING_BOTTOM;
        int widthBottom = ICON_WIDTH + ICON_PADDING_LEFT + ICON_PADDING_RIGHT;
        this->bottomIcons.icons[id].slotID = id;
        this->bottomIcons.icons[id].box = Box(Coordinates(posXBottom, posYBottom), Dimensions(width, height));
        this->bottomIcons.icons[id].bitmap = BOTTOM_ICON_BITMAPS[id];
    }
}

void Display::begin()
{
    this->setOffsetX(offsetX);
    this->setupIconSlots();
    Adafruit_SH1107::begin();
}

void Display::sendClockSettings()
{
    this->oled_command(0xD5);
    this->oled_command(this->oscFreq << 4 | this->divRatio);
}

void Display::setCursor(int x, int y)
{
    Adafruit_SH1107::setCursor(x, y);
}

void Display::setCursor(Coordinates pos)
{
    Adafruit_SH1107::setCursor(pos.x, pos.y);
}

void Display::setOffsetX(uint8_t offset)
{
    this->_page_start_offset = offset;
}

Coordinates Display::centerText(String text)
{
    int16_t x1, y1;
    uint16_t w, h;
    this->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int x = (this->width() - w) / 2;
    int y = (this->height() - h) / 2;
    return Coordinates(x, y);
}

void Display::clearCharacterBox()
{
    this->writeFillRect(this->characterBox.topLeft.x, this->characterBox.topLeft.y, this->characterBox.dimensions.width, this->characterBox.dimensions.height, SH110X_BLACK);
};

void Display::clearIcons(IconSetID id)
{
    Coordinates topleft = (id == ICON_SET_TOP) ? this->topIcons.box.topLeft : this->bottomIcons.box.topLeft;
    Dimensions dims = (id == ICON_SET_TOP) ? this->topIcons.box.dimensions : this->bottomIcons.box.dimensions;
    this->writeFillRect(topleft.x, topleft.y, dims.width, dims.height, SH110X_BLACK);
}
void Display::setIconSlotBitmap(IconSetID setID, IconSlotID slotID, const unsigned char *bitmap)
{
    if (setID == ICON_SET_TOP)
    {
        this->topIcons.icons[slotID].bitmap = bitmap;
    }
    else
    {
        this->bottomIcons.icons[slotID].bitmap = bitmap;
    }
}

void Display::drawIcon(IconSetID setID, IconSlotID slotID)
{
    IconSet *iconSet = (setID == ICON_SET_TOP) ? &this->topIcons : &this->bottomIcons;
    IconSlot *iconSlot = &iconSet->icons[slotID];
    if (iconSlot->bitmap != NULL)
    {
        this->drawBitmap(iconSlot->box.topLeft.x, iconSlot->box.topLeft.y, iconSlot->bitmap, iconSlot->box.dimensions.width, iconSlot->box.dimensions.height, SH110X_WHITE);
    }
    else
    {
        Serial.println("No bitmap set for this icon slot: Set: " + String(setID) + ", Slot: " + String(slotID));
    }
}
