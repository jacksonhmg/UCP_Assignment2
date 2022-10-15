#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gameloop.h"
#include "terminal.h"
#include "checkers.h"
#include "random.h"
#include "color.h"


void printMap(mapStruct* map2) /*for printing the map*/
{
    int i,j,colChck;
    system("clear");
    for(i=0;i<map2->nR;i++)
    {
        for(j=0;j<map2->nC;j++)
        {
            colChck = 0;
            if(i == map2->recentXR && j== map2->recentXC)
            {
                setBackground("red");
                colChck = 1;
            }
            if(i == map2->pR && j == map2->pC)
            {
                setForeground("blue");
                colChck = 1;
            }
            if(i == map2->gR && j == map2->gC)
            {
                setForeground("green");
                colChck = 1;
            }

            printf("%c",map2->map[i][j]);
            
            if(colChck)
            {
                setBackground("reset");
                setForeground("reset");
            }
        }
        printf("\n"); /*new line after each row to show 2d array effect*/
    }
}

int playerInput(LinkedList* list)
{
    char input;
    int check, valid;
    valid = 0;
    disableBuffer();
    scanf(" %c",&input);
    enableBuffer();
    if(input == 'a')
    {
        check = validatePW(list->pHead->pData, input) && validatePX(list->pHead->pData,input); /*if its possible to move to the position*/
        if(check){
            mapStruct* mapNew = (mapStruct*)malloc(sizeof(mapStruct));
            *mapNew = *(list->pHead->pData);
            transferMap(mapNew, list->pHead->pData);
            insertFirst(list,mapNew);
            #ifdef BORDERLESS
                if((list->pHead->pData->pC-1) == 0)
                {
                    (list->pHead->pData->pC) =list->pHead->pData->nC-1;
                }
            #endif
            (list->pHead->pData->pC)--;
            valid = 1;
        }
    }
    if(input == 'd')
    {
        check = validatePW(list->pHead->pData, input) && validatePX(list->pHead->pData,input);
        if(check){
            mapStruct* mapNew = (mapStruct*)malloc(sizeof(mapStruct));
            *mapNew = *(list->pHead->pData);
            transferMap(mapNew, list->pHead->pData);
            insertFirst(list,mapNew);
            #ifdef BORDERLESS
                if((list->pHead->pData->pC+1) ==list->pHead->pData->nC-1)
                {
                    (list->pHead->pData->pC) = 0;
                }
            #endif
            (list->pHead->pData->pC)++;
            valid = 1;
        }    
    }
    if(input == 's')
    {
        check = validatePW(list->pHead->pData, input) && validatePX(list->pHead->pData,input);
        if(check){
            mapStruct* mapNew = (mapStruct*)malloc(sizeof(mapStruct));
            *mapNew = *(list->pHead->pData);
            transferMap(mapNew, list->pHead->pData);
            insertFirst(list,mapNew);
            #ifdef BORDERLESS
                if((list->pHead->pData->pR+1) ==list->pHead->pData->nR-1)
                {
                    (list->pHead->pData->pR) = 0;
                }
            #endif
            (list->pHead->pData->pR)++;
            valid = 1;
        }  
    }
    if(input == 'w')
    {
        check = validatePW(list->pHead->pData, input) && validatePX(list->pHead->pData,input);
        if(check){
            mapStruct* mapNew = (mapStruct*)malloc(sizeof(mapStruct));
            *mapNew = *(list->pHead->pData);
            transferMap(mapNew, list->pHead->pData);
            insertFirst(list,mapNew);
            #ifdef BORDERLESS
                if((list->pHead->pData->pR-1) == 0)
                {
                    (list->pHead->pData->pR) =list->pHead->pData->nR-1;
                }
            #endif
            (list->pHead->pData->pR)--;
            valid = 1;
        }
    }
    if(input == 'u')
    {
        if(list->iSize > 1)
        {
            removeFirst(list, &freeStruct);
        }
    }
    return valid;
}

void xUpdate(mapStruct* map2)
{
    int xR, xC;
    xR = randoms(1,map2->nR-2); /*keep within box size*/
    xC = randoms(1,map2->nC-2);

    while(map2->map[xR][xC] != ' ') /*while the random spot is not empty, retry*/
    {
        xR = randoms(1,map2->nR-2);
        xC = randoms(1,map2->nC-2);
    }
    map2->recentXR = xR;
    map2->recentXC = xC;
    map2->map[xR][xC] = 'X';
}

void optionsPrint()
{
    printf("Press w to go up\n");
    printf("Press s to go down\n");
    printf("Press a to go left\n");
    printf("Press d to go right\n");
}

void gameloop(LinkedList* list) /*continuous function handling the game loop*/
{
    int valid, oldPR, oldPC;
    while(!winCond(list->pHead->pData) && !loseCond(list->pHead->pData)) /*while the player hasnt won or lost*/
    {
        optionsPrint();
        oldPR = list->pHead->pData->pR;
        oldPC = list->pHead->pData->pC;
        valid = playerInput(list);
        if(valid)
        {
            list->pHead->pData->map[oldPR][oldPC] = ' '; /*get rid of the old player spot so that xUpdate is not based on the OLD players position; 
            place it here so that we can address the old spot, get rid of it, then assign a new spot that xUpdate addresses*/
            list->pHead->pData->map[list->pHead->pData->pR][list->pHead->pData->pC] = 'P';
            xUpdate(list->pHead->pData);
        }
        printMap(list->pHead->pData);   
    }
    if(winCond(list->pHead->pData))
    {
        printf("You Win!\n");
        printf("Congratulations!\n");
    }
    freeLinkedList(list, &freeStruct);
}

void transferMap(mapStruct* mapNew, mapStruct* mapOld)
{
    int i, j;
    mapNew->map = (char**)calloc(mapOld->nR,sizeof(char*));
    for(i=0;i<mapOld->nR;i++)
    {
        (mapNew->map)[i] = (char*)calloc(mapOld->nC, sizeof(char));
    }
    for(i = 0; i < mapOld->nR; i++)
    {
        for(j = 0; j < mapOld->nC; j++)
        {
            mapNew->map[i][j] = mapOld->map[i][j];
        }
    }
}
