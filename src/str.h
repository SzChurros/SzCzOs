#ifndef STR
#define STR

#include "types.h"

int strcmp(const char* a, const char* b) {
    while (*a && *b && *a == *b) { 
        a++;
        b++;
    }
    return *a - *b;
}

void strtok(char* dat, char** dest, uint8 maxlen, uint16 strlen)
{
    uint8 toknum = 0;
    uint8 charpos = 0;
    for (int i = 0; i < strlen; i++)
    {
        if (dat[i] == '\0')
        {
            dest[toknum][charpos] = '\0';
            return;
        }
        else if (dat[i] == ' ')
        {
            dest[toknum][charpos] = '\0';
            toknum++;
            if (toknum == maxlen)
                return;
            charpos = 0;
        }
        else
        {
            dest[toknum][charpos] = dat[i];
            charpos++;
        }
    }
}

#endif