#include "szczos.h"
#include "drivers/ps2.h"
#include "keyboard_layouts.h"
#include "str.h"

void kernel_main() {
    cls();

    sprint("Welcome To \\\x04Sz\\\x02""Cz\\\x01OS\\\x0f!\ntype help to see built-in commands\n\n> ");

    moveCursorToVGApos();

    uint16 typedchars = 0;
    char command[256];
    char* tokens[8];

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
                strtok(command, tokens, 8, 256);
                if (strcmp(tokens[0], "clear") == 0)
                {
                    cls();
                    setVGAx(0);
                    setVGAy(0);
                    sprint("> ");
                }
                else if (strcmp(tokens[0], "help") == 0) 
                {
                    sprint("\n help - help menu");
                    sprint("\n clear - clear screen");
                    sprint("\n power [reboot, off] - reboots or turns off the pc (depending on the flag)");
                    sprint("\n> ");
                }
                else if (strcmp(tokens[0], "power") == 0)
                {
                    if (strcmp(tokens[1], "reboot") == 0)
                    {
                        reboot();
                    }
                    else if (strcmp(tokens[1], "off") == 0)
                    {
                        shutdown();
                    }
                    else
                    {
                        sprint("\ninvalid syntax; use help to know flags");
                        sprint("\n>");
                    }
                }
                else
                {
                    sprint("\ncommand not found\n>");
                }
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