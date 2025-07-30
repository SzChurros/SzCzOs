#ifndef ASMC
#define ASMC

#include "types.h"

uint8 inb(uint16 port);
void outb(uint16 port, uint8 data);
uint8 inw(uint16 port);
void outw(uint16 port, uint16 data);

#endif