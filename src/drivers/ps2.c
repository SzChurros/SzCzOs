#include "ps2.h"

void PS2keybdInfoInit(struct PS2deviceInfo* info)
{
    info->dataPort = 0x60;
    info->statusPort = 0x64;
}

void PS2keybdWaitWrite(struct PS2deviceInfo* info)
{
    while (inb(info->statusPort) & 0x02);  // Wait until input buffer is empty
}

uint8 PS2keybdRead(struct PS2deviceInfo* info)
{
    while (!(inb(info->statusPort) & 0x01)); // Wait for data
    return inb(info->dataPort);
}

void PS2keybdInit(struct PS2deviceInfo* info)
{
    PS2keybdWaitWrite(info);
    outb(info->dataPort, 0xF4); // Enable scanning
    while (PS2keybdRead(info) != 0xFA); // Wait for ACK (0xFA)
}