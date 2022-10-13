#include "macros.h"
#include "LinkedList.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

void printMap(mapStruct* map2);
int playerInput(mapStruct* map2);
void xUpdate(mapStruct* map);
void optionsPrint();
void gameloop(LinkedList* list);
void transferMap(mapStruct* mapNew, mapStruct* mapOld);


#endif