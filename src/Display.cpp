#include <Arduino.h>
#include <Display.h>
#include <DeviceConfig.h>

void Display::begin(uint8_t offsetX)
{
    this->setOffsetX(offsetX);
    Adafruit_SH1107::begin();
}
void Display::setCursor(int x, int y)
{
    Adafruit_SH1107::setCursor(x, y);
}

void Display::setCursor(CursorPosition pos)
{
    Adafruit_SH1107::setCursor(pos.x, pos.y);
}

void Display::setOffsetX(uint8_t offset)
{
    this->_page_start_offset = offset;
}

CursorPosition Display::centerText(String text)
{
    int16_t x1, y1;
    uint16_t w, h;
    this->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int x = (this->width() - w) / 2;
    int y = (this->height() - h) / 2;
    return CursorPosition(x, y);
}