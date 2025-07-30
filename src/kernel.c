#include "szczos.h"
#include "drivers/ps2.h"
#include "keyboard_layouts.h"

void kernel_main() {
    cls();

    sprint("Welcome To \\\x04Sz\\\x02""Cz\\\x01OS\\\x0f!\n\n> ");

    moveCursorToVGApos();

    uint16 typedchars = 0;
    char command[256];

    for (uint16 i = 0; i <= 255; i++)
    {
        command[i] = '\0';
    }

    struct PS2deviceInfo keybdInfo;

    PS2keybdInfoInit(&keybdInfo);
    PS2keybdInit(&keybdInfo);

    while(1)
    {
        uint8 sc = PS2keybdRead(&keybdInfo);
        uint8 c = keylayout_us[sc];
        if (!(sc & 0x80)) {  // Ignore key releases
            if (c == '\b')
            {
                if (typedchars)
                {
                    if (getVGAx() != 0)
                    {
                        setVGAx(getVGAx() - 1);
                        sputchar(' ');
                        setVGAx(getVGAx() - 1);
                    }
                    else
                    {
                        setVGAx(VGA_WIDTH - 1);
                        setVGAy(getVGAy() - 1);
                        sputchar(' ');
                        setVGAx(VGA_WIDTH - 1);
                        setVGAy(getVGAy() - 1);
                    }
                    typedchars--;
                    command[typedchars] = '\0';
                }
            }
            else if (c == '\n')
            {
                sprint("\n> ");
                typedchars = 0;
                for (uint16 i = 0; i <= 255; i++)
                {
                    command[i] = '\0';
                }
            }
            else if (typedchars < 256)
            {
                sputchar(c);
                command[typedchars] = c;
                typedchars++;
            }
            moveCursorToVGApos();
        }
    }
}