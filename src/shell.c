#include "shell.h"
#include "szczos.h"

void shEcho(char* arg)
{
    sputchar('\n');
    sprint(arg);
    sputchar('\n');
}