#include "szczos.h"
#include "types.h"

uint8 vga_x = 0;
uint8 vga_y = 0;

volatile uint16 *vga_buf = (volatile uint16*)0xB8000;

void setVGAx(uint8 x)
{
    vga_x = x;
}

void setVGAy(uint8 y)
{
    vga_y = y;
}

void setVGA(uint8 x, uint8 y)
{
    vga_x = x;
    vga_y = y;
}

uint8 getVGAx()
{
    return vga_x;
}

uint8 getVGAy()
{
    return vga_y;
}

void moveCursorToVGApos()
{
    outb(0x3D4, 0x0F);          // Low byte index
    outb(0x3D5, (uint8)(vga_pos() & 0xFF));  
    outb(0x3D4, 0x0E);          // High byte index
    outb(0x3D5, (uint8)((vga_pos() >> 8) & 0xFF));
}

uint16 vga_pos()
{
    return vga_x + VGA_WIDTH * vga_y;
}

uint16 c_vga_pos(uint8 x, uint8 y)
{
    return x + VGA_WIDTH * y;
}

// merges C0 and C1 to C0C1
uint16 MERGE_2_UINT8_T(uint8 C0, uint8 C1)
{
    return (C1 << 8) | C0;
}

bool NEW_LINE_CHECK()
{
    if (vga_x == VGA_WIDTH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void SHIFT_SCREEN_ONE_LINE_DOWN()
{
    for (vga_y = 1; vga_y < VGA_HEIGHT; vga_y++)
    {
        for (vga_x = 0; vga_x < VGA_WIDTH; vga_x++)
        {
            vga_buf[c_vga_pos(vga_x, vga_y - 1)] = vga_buf[vga_pos()];
        }
    }
    vga_y = VGA_HEIGHT - 1;
    for (vga_x = 0; vga_x < VGA_WIDTH; vga_x++)
    {
        vga_buf[vga_pos()] = m2ui8(' ', 0x00);
    }
    vga_x = 0;
}

void NEW_LINE()
{
    vga_x = 0;
    vga_y++;

    if (vga_y == VGA_HEIGHT)
    {
        vga_y--;
        shft();
    }
}

void CLEAR_SCREEN()
{
    for (int i = 0; i < 2000; i++)
    {
        vga_buf[i] = 0x0020; // space black on black
    }
}

// prints c-style string of defined color to vga buffer
void csprint(const char *string, uint8 color) 
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        switch (string[i])
        {
        case '\n':
            nline();
        break;
        case '\t':
            vga_buf[vga_pos()] = m2ui8(' ', color);
            vga_x++;

            if (nlinec())
            {
                nline();
                continue;
            }

            vga_buf[vga_pos()] = m2ui8(' ', color);
            vga_x++;

            if (nlinec())
            {
                nline();
                continue;
            }

            vga_buf[vga_pos()] = m2ui8(' ', color);
            vga_x++;
        break;
        case '\\':
            i++;
            color = string[i];
        break;
        default:
            vga_buf[vga_pos()] = m2ui8(string[i], color);
            vga_x++;

            if (nlinec())
            {
                nline();
            }
        break;
        }
    }
}

void putchar(uint8 chr, uint8 color)
{
    switch (chr)
        {
        case '\n':
            nline();
        break;
        case '\t':
            vga_buf[vga_pos()] = m2ui8(' ', color);
            vga_x++;

            if (nlinec())
            {
                nline();
            }

            vga_buf[vga_pos()] = m2ui8(' ', color);
            vga_x++;

            if (nlinec())
            {
                nline();
            }

            vga_buf[vga_pos()] = m2ui8(' ', color);
            vga_x++;

            if (nlinec())
            {
                nline();
            }
        break;
        default:
            vga_buf[vga_pos()] = m2ui8(chr, color);
            vga_x++;

            if (nlinec())
            {
                nline();
            }
        break;
        }
}