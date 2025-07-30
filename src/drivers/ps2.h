#ifndef DRIVER_PS2
#define DRIVER_PS2

#include "../types.h"
#include "../asmc.h"

struct PS2deviceInfo
{
    uint8 dataPort;
    uint8 statusPort;
};

void PS2keybdInfoInit(struct PS2deviceInfo* info);

void PS2keybdWaitWrite(struct PS2deviceInfo* info);
uint8 PS2keybdRead(struct PS2deviceInfo* info);
void PS2keybdInit(struct PS2deviceInfo* info);

#endif