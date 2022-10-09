#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "checkers.h"

int validatePW(int nR, int nC, int pR, int pC, char input, char** map) /*validating against the walls*/
{
    int valid;
    valid = 1; /*valid unless told otherwise*/
    if(input == 'a')
    {
        if(pC-1 == 0)
        {
            valid = 0;

            #ifdef BORDERLESS
                if(validatePX(map,nR,nC,pR,nC-1,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif
            
        }
    }
    if(input == 'd')
    {
        if(pC+1 == nC-1)
        {
            valid = 0;
            
            #ifdef BORDERLESS
                if(validatePX(map,nR,nC,pR,0,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif

        }
    }
    if(input == 's')
    {
        if(pR+1 == nR-1)
        {
            valid = 0;
            #ifdef BORDERLESS
                if(validatePX(map,nR,nC,0,pC,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif

           
        }
    }
    if(input == 'w')
    {
        if(pR-1 == 0)
        {
            valid = 0;
            #ifdef BORDERLESS
                if(validatePX(map,nR,nC,nR-1,pC,input)) /*if there's no Xs on other side blocking the borderless wrap around*/
                {
                    valid = 1;
                }
            #endif
        }
    }
    return valid;
}

int validatePX(char**map, int nR, int nC, int pR, int pC, char input) /*validating against the Xs*/
{
    int valid;
    valid = 1;
    if(input == 'a')
    {
        if(map[pR][pC-1] == 'X')
        {
            valid = 0;
        }
    }
    if(input == 'd')
    {
        if(map[pR][pC+1] == 'X')
        {
            valid = 0;
        }
    }
    if(input == 's')
    {
        if(map[pR+1][pC] == 'X')
        {
            valid = 0;
        }
    }
    if(input == 'w')
    {
        if(map[pR-1][pC] == 'X')
        {
            valid = 0;
        }
    }
    return valid;
}

int winCond(int pR, int pC, int gR, int gC)
{
    return (pR == gR && pC == gC) ? 1 : 0;
}


int loseCond(int pR, int pC, int gR, int gC, int nR, int nC,char** map)
{
    int check = 0;

    /*checking if possible to move at all, if not possible to move then check = 1 and therefore lose*/
    if(!(validatePW(nR, nC, pR, pC, 'w',map) && validatePX(map,nR,nC,pR,pC,'w')) &&
    !(validatePW(nR, nC, pR, pC, 'a',map) && validatePX(map,nR,nC,pR,pC,'a')) &&
    !(validatePW(nR, nC, pR, pC, 's',map) && validatePX(map,nR,nC,pR,pC,'s')) && 
    !(validatePW(nR, nC, pR, pC, 'd',map) && validatePX(map,nR,nC,pR,pC,'d')))
    {
        check = 1;
    }

    /* checking if goal is surrounded by Xs or *'s or both */
    if((map[gR-1][gC] == 'X' || map[gR-1][gC] == '*') && 
    (map[gR+1][gC] == '*' || map[gR+1][gC] == 'X') && 
    (map[gR][gC-1] == '*' || map[gR][gC-1] == 'X') && 
    (map[gR][gC+1] == '*' || map[gR][gC+1] == 'X'))
    {
        check = 1;
    }
    if(check)
    {
        printf("\n");
        printf("You Lose!\n");
        printf("Unlucky!\n");
    }
    return check;
}

int inputCheck(int *nR,int *nC,int *pR,int *pC,int *gR,int *gC, int argc, char* argv[]) /*validating user input*/
{
    int check;
    check = 1;
    if(argc < 7)
    {
        printf("Please run in the format of: './escape <map-row> <map-col> <player-row> <player-col> <goal-row> <goal-col>\n");
        check = 0;
    }
    if(check)
    {   
        /* i add to all the inputs below so that, for example, "0,0" for player position equals the top left corner inside the box 
        and that "15,15" equals the size inside the box not including border*/
        *nR = atoi(argv[1]) +2;
        *nC = atoi(argv[2]) +2;
        *pR = atoi(argv[3]) +1;
        *pC = atoi(argv[4]) +1;
        *gR = atoi(argv[5]) +1;
        *gC = atoi(argv[6]) +1;

        if(*nR < 2 || *nC < 2 || *pR < 1 || *pC < 1 || *gR < 1 || *gC < 1) /*numbers are higher than 0 because of the addition done above*/
        {
            printf("Cannot enter negative numbers!\n");
            check = 0;
        }

        if(*nR < 7 || *nC < 7) /*7 because the inside can't be smaller than 5 and 7 is the number of whole array including border*/
        {
            printf("Map size too small!\n");
            check = 0;
        }
        if(*pR > *nR - 2 || *pC > *nC - 2)
        {
            printf("Player position placed outside of map area!\n");
            check = 0;
        }
        if(*gR > *nR - 2 || *gC > *nC - 2)
        {
            printf("Goal position placed outside of map area!\n");
            check = 0;
        }
    }
    return check;
}