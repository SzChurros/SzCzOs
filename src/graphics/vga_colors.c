#include "vga_colors.h"

unsigned char VGA_TEXT(enum VGA_COLOR fg, enum VGA_COLOR bg)
{
    //return fg + bg * 16;
    return (bg << 4) | fg;
}