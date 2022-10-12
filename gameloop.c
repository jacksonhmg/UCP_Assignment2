#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gameloop.h"
#include "terminal.h"
#include "checkers.h"
#include "random.h"


void printMap(mapStruct* map2) /*for printing the map*/
{
    int i,j;
    system("clear");
    for(i=0;i<map2->nR;i++)
    {
        for(j=0;j<map2->nC;j++)
        {
                printf("%c",map2->map[i][j]);
        }
        printf("\n"); /*new line after each row to show 2d array effect*/
    }
}

int playerInput(int* pR, int* pC, int nR, int nC, char** map)
{
    char input;
    int check, valid;
    valid = 0;
    disableBuffer();
    scanf(" %c",&input);
    enableBuffer();
    if(input == 'a')
    {
        check = validatePW(nR, nC, *pR, *pC, input,map) && validatePX(map,nR,nC,*pR,*pC,input); /*if its possible to move to the position*/
        if(check){
            #ifdef BORDERLESS
                if((*pC-1) == 0)
                {
                    (*pC) = nC-1;
                }
            #endif
            (*pC)--;
            valid = 1;
        }
    }
    if(input == 'd')
    {
        check = validatePW(nR, nC, *pR, *pC, input,map) && validatePX(map,nR,nC,*pR,*pC,input);
        if(check){
            #ifdef BORDERLESS
                if((*pC+1) == nC-1)
                {
                    (*pC) = 0;
                }
            #endif
            (*pC)++;
            valid = 1;
        }    
    }
    if(input == 's')
    {
        check = validatePW(nR, nC, *pR, *pC, input,map) && validatePX(map,nR,nC,*pR,*pC,input);
        if(check){
            #ifdef BORDERLESS
                if((*pR+1) == nR-1)
                {
                    (*pR) = 0;
                }
            #endif
            (*pR)++;
            valid = 1;
        }  
    }
    if(input == 'w')
    {
        check = validatePW(nR, nC, *pR, *pC, input,map) && validatePX(map,nR,nC,*pR,*pC,input);
        if(check){
            #ifdef BORDERLESS
                if((*pR-1) == 0)
                {
                    (*pR) = nR-1;
                }
            #endif
            (*pR)--;
            valid = 1;
        }
    }
    return valid;
}

void xUpdate(char** map, int nR, int nC)
{
    int xR, xC;
    xR = randoms(1,nR-2); /*keep within box size*/
    xC = randoms(1,nC-2);

    while(map[xR][xC] != ' ') /*while the random spot is not empty, retry*/
    {
        xR = randoms(1,nR-2);
        xC = randoms(1,nC-2);
    }
    map[xR][xC] = 'X';
}

void optionsPrint()
{
    printf("Press w to go up\n");
    printf("Press s to go down\n");
    printf("Press a to go left\n");
    printf("Press d to go right\n");
}

void gameloop(mapStruct* map2) /*continuous function handling the game loop*/
{
    int valid, i;
    while(!winCond(map2) && !loseCond(map2)) /*while the player hasnt won or lost*/
    {
        optionsPrint();
        map2->map[map2->pR][map2->pC] = ' '; /*get rid of the old player spot so that xUpdate is not based on the OLD players position; 
        place it here so that we can address the old spot, get rid of it, then assign a new spot that xUpdate addresses*/
        valid = playerInput(&(map2->pR),&(map2->pC),map2->nR,map2->nC,map2->map);
        map2->map[map2->pR][map2->pC] = 'P';
        if(valid)
        {
            xUpdate(map2->map, map2->nR, map2->nC);
        }
        printMap(map2);
    }
    if(winCond(map2))
    {
        printf("You Win!\n");
        printf("Congratulations!\n");
    }
    
    for(i = 0; i < map2->nR; i++)
    {
        free(map2->map[i]);
    }
    free(map2->map);
}
