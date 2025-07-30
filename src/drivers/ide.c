#include "ide.h"

void ideReadSector(uint32 lba, uint16* buffer)
{
    while ((inb(0x1F7) & 0x80));

    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, lba & 0xFF);
    outb(0x1F4, (lba >> 8) & 0xFF);
    outb(0x1F5, (lba >> 16) & 0xFF);

    outb(0x1F7, 0x20);

    while (!((inb(0x1F7) & 0x08)));

    for (int i = 0; i < 256; i++) {
        buffer[i] = inw(0x1F0);
    }
}

void ideIndentify(uint16* buffer)
{
    outb(0x1F6, 0xA0);
    outb(0x1F2, 0);
    outb(0x1F7, 0xEC);

    while (!(inb(0x1F7) & 0x08));

    for (int i = 0; i < 256; i++) {
        buffer[i] = inw(0x1F0);
    }
}

uint32 ideGetSize() {
    uint16 buf[256];
    ideIndentify(buf);
    return *((uint32*)(buf + 60));  // LBA28 max sectors at offset 60-61
}