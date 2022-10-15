#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "checkers.h"

int validatePW(mapStruct* map2, char input) /*validating against the walls*/
{
    int valid;
    valid = 1; /*valid unless told otherwise*/
    if(input == 'a')
    {
        if(map2->pC-1 == 0)
        {
            valid = 0;

            #ifdef BORDERLESS
                if(validatePX(map2,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif
            
        }
    }
    if(input == 'd')
    {
        if(map2->pC+1 == map2->nC-1)
        {
            valid = 0;
            
            #ifdef BORDERLESS
                if(validatePX(map2,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif

        }
    }
    if(input == 's')
    {
        if(map2->pR+1 == map2->nR-1)
        {
            valid = 0;
            #ifdef BORDERLESS
                if(validatePX(map2,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif

           
        }
    }
    if(input == 'w')
    {
        if(map2->pR-1 == 0)
        {
            valid = 0;
            #ifdef BORDERLESS
                if(validatePX(map2,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif
        }
    }
    return valid;
}

int validatePX(mapStruct* map2, char input) /*validating against the Xs*/
{
    int valid;
    valid = 1;
    if(input == 'a')
    {
        if(map2->map[map2->pR][map2->pC-1] == 'X')
        {
            valid = 0;
        }
    }
    if(input == 'd')
    {
        if(map2->map[map2->pR][map2->pC+1] == 'X')
        {
            valid = 0;
        }
    }
    if(input == 's')
    {
        if(map2->map[map2->pR+1][map2->pC] == 'X')
        {
            valid = 0;
        }
    }
    if(input == 'w')
    {
        if(map2->map[map2->pR-1][map2->pC] == 'X')
        {
            valid = 0;
        }
    }
    return valid;
}

int winCond(mapStruct* map2)
{
    return (map2->pR == map2->gR && map2->pC == map2->gC) ? 1 : 0;
}


int loseCond(mapStruct* map2)
{
    int check = 0;

    /*checking if possible to move at all, if not possible to move then check = 1 and therefore lose*/
    if(!(validatePW(map2, 'w') && validatePX(map2,'w')) &&
    !(validatePW(map2, 'a') && validatePX(map2,'a')) &&
    !(validatePW(map2, 's') && validatePX(map2,'s')) && 
    !(validatePW(map2, 'd') && validatePX(map2,'d')))
    {
        check = 1;
    }

    /* checking if goal is surrounded by Xs or *'s or both */
    if((map2->map[map2->gR-1][map2->gC] == 'X' || map2->map[map2->gR-1][map2->gC] == '*') && 
    (map2->map[map2->gR+1][map2->gC] == '*' || map2->map[map2->gR+1][map2->gC] == 'X') && 
    (map2->map[map2->gR][map2->gC-1] == '*' || map2->map[map2->gR][map2->gC-1] == 'X') && 
    (map2->map[map2->gR][map2->gC+1] == '*' || map2->map[map2->gR][map2->gC+1] == 'X'))
    {
        check = 1;
    }
    if(check)
    {
        printf("You Lose!\n");
        printf("Unlucky!\n");
        printf("\n");
    }
    return check;
}