/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#include <Wire.h>
#include "er_oled.h"
#include "Arduino.h"

void I2C_Write_Byte(uint8_t value, uint8_t Cmd)
{
    uint8_t Addr = 0x3c;
    Wire.beginTransmission(Addr);
    Wire.write(Cmd);
    Wire.write(value);
    Wire.endTransmission();
}

void er_oled_begin()
{
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, HIGH);
    delay(10);
    digitalWrite(OLED_RST, LOW);
    delay(10);

    command(0xAE); //--turn off oled panel
    command(0xd5); // Set Frame Frequency
    command(0x50); // 104Hz
    command(0x20); // Set Memory Addressing Mode
    command(0x81); // Set Contrast Control
    command(0x4f);
    command(0xad); // Set DC/DC off
    command(0x8a);

    command(0xC0);
    command(0xA0);

    command(0xdc); // Set Display Start Line
    command(0x00);
    command(0xd3); // Set Display Offset
    command(0x00);
    command(0xd9); // Set Discharge / Pre-Charge Period
    command(0x22);
    command(0xdb); // Set Vcomh voltage
    command(0x35);

    command(0xa8); // Set Multiplex Ration
    command(0x7f);

    command(0xa4); // Set Entire Display OFF/ON
    command(0xa6); // Set Normal/Reverse Display

    command(0xAF); // Display ON
}

void er_oled_clear(uint8_t *buffer)
{
    int i;
    for (i = 0; i < WIDTH * HEIGHT / 8; i++)
    {
        buffer[i] = 0;
    }
}

void er_oled_pixel(int x, int y, char color, uint8_t *buffer)
{
    if (x > WIDTH || y > HEIGHT)
        return;
    if (color)
        buffer[x + (y / 8) * WIDTH] |= 1 << (y % 8);
    else
        buffer[x + (y / 8) * WIDTH] &= ~(1 << (y % 8));
}

void er_oled_char1616(uint8_t x, uint8_t y, uint8_t chChar, uint8_t *buffer)
{
    uint8_t i, j;
    uint8_t chTemp = 0, y0 = y, chMode = 0;

    for (i = 0; i < 32; i++)
    {
        chTemp = pgm_read_byte(&Font1612[chChar - 0x30][i]);
        for (j = 0; j < 8; j++)
        {
            chMode = chTemp & 0x80 ? 1 : 0;
            er_oled_pixel(x, y, chMode, buffer);
            chTemp <<= 1;
            y++;
            if ((y - y0) == 16)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

void er_oled_char(unsigned char x, unsigned char y, char acsii, char size, char mode, uint8_t *buffer)
{
    unsigned char i, j, y0 = y;
    char temp;
    unsigned char ch = acsii - ' ';
    for (i = 0; i < size; i++)
    {
        if (size == 12)
        {
            if (mode)
                temp = pgm_read_byte(&Font1206[ch][i]);
            else
                temp = ~pgm_read_byte(&Font1206[ch][i]);
        }
        else
        {
            if (mode)
                temp = pgm_read_byte(&Font1608[ch][i]);
            else
                temp = ~pgm_read_byte(&Font1608[ch][i]);
        }
        for (j = 0; j < 8; j++)
        {
            if (temp & 0x80)
                er_oled_pixel(x, y, 1, buffer);
            else
                er_oled_pixel(x, y, 0, buffer);
            temp <<= 1;
            y++;
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

void er_oled_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t *buffer)
{
    while (*pString != '\0')
    {
        if (x > (WIDTH - Size / 2))
        {
            x = 0;
            y += Size;
            if (y > (HEIGHT - Size))
            {
                y = x = 0;
            }
        }

        er_oled_char(x, y, *pString, Size, Mode, buffer);
        x += Size / 2;
        pString++;
    }
}

void er_oled_char3216(uint8_t x, uint8_t y, uint8_t chChar, uint8_t *buffer)
{
    uint8_t i, j;
    uint8_t chTemp = 0, y0 = y, chMode = 0;

    for (i = 0; i < 64; i++)
    {
        chTemp = pgm_read_byte(&Font3216[chChar - 0x30][i]);
        for (j = 0; j < 8; j++)
        {
            chMode = chTemp & 0x80 ? 1 : 0;
            er_oled_pixel(x, y, chMode, buffer);
            chTemp <<= 1;
            y++;
            if ((y - y0) == 32)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

void er_oled_bitmap(uint8_t x, uint8_t y, const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t *buffer)
{
    uint8_t i, j, byteWidth = (chWidth + 7) / 8;
    for (j = 0; j < chHeight; j++)
    {
        for (i = 0; i < chWidth; i++)
        {
            if (pgm_read_byte(pBmp + j * byteWidth + i / 8) & (128 >> (i & 7)))
            {
                er_oled_pixel(x + i, y + j, 1, buffer);
            }
        }
    }
}

void er_oled_display(uint8_t *pBuf)
{
    uint8_t page, i;
    for (page = 0; page < PAGES; page++)
    {
        command(0xB0 + page); /* set page address */
        command(0x00);        /* set low column address */
        command(0x10);        /* set high column address */
        for (i = 0; i < WIDTH; i++)
        {
            data(pBuf[i + page * WIDTH]); // write data one
        }
    }
}
