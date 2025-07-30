#ifndef SZCZOS
#define SZCZOS

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define sbuf vga_buf
#define cls CLEAR_SCREEN
#define shft SHIFT_SCREEN_ONE_LINE_DOWN
#define m2ui8 MERGE_2_UINT8_T
#define nline NEW_LINE
#define nlinec NEW_LINE_CHECK

#define sprint(string) csprint(string, 0x0F)
#define sputchar(chr) putchar(chr, 0x0F)

#include "graphics/vga_colors.h"
#include "types.h"
#include "asmc.h"

void setVGAx(uint8 x);
void setVGAy(uint8 y);
uint8 getVGAx();
uint8 getVGAy();
void setVGA(uint8 x, uint8 y);

void moveCursorToVGApos();

uint16 vga_pos();
uint16 c_vga_pos(uint8 x, uint8 y);
// merges C0 and C1 to C0C1
uint16 MERGE_2_UINT8_T(uint8 C0, uint8 C1);

bool NEW_LINE_CHECK();

void SHIFT_SCREEN_ONE_LINE_DOWN();
void NEW_LINE();
void CLEAR_SCREEN();
// prints c-style string of defined color to vga buffer
void csprint(const char *string, uint8 color);
void putchar(uint8 chr, uint8 color);

void reboot();
void shutdown();

#endif