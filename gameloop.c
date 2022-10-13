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

int playerInput(mapStruct* map2)
{
    char input;
    int check, valid;
    valid = 0;
    disableBuffer();
    scanf(" %c",&input);
    enableBuffer();
    if(input == 'a')
    {
        check = validatePW(map2, input) && validatePX(map2,input); /*if its possible to move to the position*/
        if(check){
            #ifdef BORDERLESS
                if((map2->pC-1) == 0)
                {
                    (map2->pC) =map2->nC-1;
                }
            #endif
            (map2->pC)--;
            valid = 1;
        }
    }
    if(input == 'd')
    {
        check = validatePW(map2, input) && validatePX(map2,input);
        if(check){
            #ifdef BORDERLESS
                if((map2->pC+1) ==map2->nC-1)
                {
                    (map2->pC) = 0;
                }
            #endif
            (map2->pC)++;
            valid = 1;
        }    
    }
    if(input == 's')
    {
        check = validatePW(map2, input) && validatePX(map2,input);
        if(check){
            #ifdef BORDERLESS
                if((map2->pR+1) ==map2->nR-1)
                {
                    (map2->pR) = 0;
                }
            #endif
            (map2->pR)++;
            valid = 1;
        }  
    }
    if(input == 'w')
    {
        check = validatePW(map2, input) && validatePX(map2,input);
        if(check){
            #ifdef BORDERLESS
                if((map2->pR-1) == 0)
                {
                    (map2->pR) =map2->nR-1;
                }
            #endif
            (map2->pR)--;
            valid = 1;
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

void gameloop(mapStruct* map2) /*continuous function handling the game loop*/
{
    int valid, i;
    while(!winCond(map2) && !loseCond(map2)) /*while the player hasnt won or lost*/
    {
        optionsPrint();
        map2->map[map2->pR][map2->pC] = ' '; /*get rid of the old player spot so that xUpdate is not based on the OLD players position; 
        place it here so that we can address the old spot, get rid of it, then assign a new spot that xUpdate addresses*/
        valid = playerInput(map2);
        map2->map[map2->pR][map2->pC] = 'P';
        if(valid)
        {
            xUpdate(map2);
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
