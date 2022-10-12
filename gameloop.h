#include "macros.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

void printMap(mapStruct* map2);
int playerInput(int* pR, int* pC, int nR, int nC, char** map);
void xUpdate(char** map, int nR, int nC);
void optionsPrint();
void gameloop(mapStruct* map2);


#endif