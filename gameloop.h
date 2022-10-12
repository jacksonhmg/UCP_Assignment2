#include "macros.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

void printMap(mapStruct* map2);
int playerInput(int* pR, int* pC, int nR, int nC, char** map);
void xUpdate(mapStruct* map);
void optionsPrint();
void gameloop(mapStruct* map2);


#endif