#ifndef IDE
#define IDE

#include "../types.h"
#include "../asmc.h"

void ideReadSector(uint32 lba, uint16* buffer);
void ideIndentify(uint16* buffer);

uint32 ideGetSize();

#endif