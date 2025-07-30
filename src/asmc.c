#include "asmc.h"

uint8 inb(uint16 port) {
    uint8 data;
    asm volatile ("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

void outb(uint16 port, uint8 data) {
    asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
}

uint8 inw(uint16 port) {
    uint8 data;
    asm volatile ("inw %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

void outw(uint16 port, uint16 data) {
    asm volatile ("outw %0, %1" :: "a"(data), "Nd"(port));
}