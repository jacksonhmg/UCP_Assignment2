#include "macros.h"

#ifndef CHECKERS_H
#define CHECKERS_H

int validatePW(mapStruct* map2, char input);
int validatePX(mapStruct* map2, char input);
int winCond(mapStruct* map2);
int loseCond(mapStruct* map2);
int inputCheck(int *nR,int *nC,int *pR,int *pC,int *gR,int *gC, int argc, char* argv[]);

#endif