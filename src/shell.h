#ifndef SHELL
#define SHELL

#include "types.h"

void shEcho(char* arg);
//returns amount of tokens
uint8 shTokenize(char* command, char* args[8]);

#endif