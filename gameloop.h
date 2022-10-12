#include "macros.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

void printMap(mapStruct* map2);
int playerInput(mapStruct* map2);
void xUpdate(mapStruct* map);
void optionsPrint();
void gameloop(mapStruct* map2);


#endif