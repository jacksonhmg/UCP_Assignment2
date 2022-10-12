#include "macros.h"

#ifndef SETUP_H
#define SETUP_H

void setupMap(mapStruct* map2, char* argv[]);
int setupGame(int argc, char* argv[]);
int readMapFile(char* argv[], mapStruct* map2);

#endif