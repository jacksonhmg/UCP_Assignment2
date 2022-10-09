#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "macros.h"
#include "setup.h"
#include "gameloop.h"
#include "checkers.h"


void setupMap(char***map, int nR, int nC, int pR, int pC, int gR, int gC, char* argv[]) /*initialise first iteration of map*/
{
    int i,j, nRead, int1, int2;
    char c1;
    FILE* f1 = fopen(argv[1], "r");
    system("clear");
    *map = (char**)calloc(nR,sizeof(char*));
    if(f1 == NULL)
    {
        perror("Error opening f1");
    }
    for(i=0;i<nR;i++)
    {
        (*map)[i] = (char*)calloc(nC, sizeof(char));
    }
    for(i=0;i<nR;i++)
    {
        (*map)[i][nC-1] = '*';
    }
    for(i=0;i<nR;i++)
    {
        (*map)[i][0] = '*';
    }
    for(i=0;i<nC;i++)
    {
        (*map)[0][i] = '*';
    }
    for(i=0;i<nC;i++)
    {
        (*map)[nR-1][i] = '*';
    }
    
    for(i=0;i<nR;i++)
    {
        for(j=0;j<nC;j++)
        {
            if((*map)[i][j] == 0)
            {
                (*map)[i][j] =  ' '; /*create empty space look*/
            }
        }
    }

    (*map)[gR][gC] = 'G';
    (*map)[pR][pC] = 'P';



    nRead = fscanf(f1, "%d %d ", &i, &j);

    do
    {
        nRead = fscanf(f1, "%d %d %c ", &int1, &int2, &c1);
        if(nRead != EOF)
        {
            if(c1 == 'X')
            {
                int1 ++;
                int2 ++;
                if(!(int1 == pR && int2 == pC) && !(int1 == gR && int2 == gC))
                {
                    (*map)[int1][int2] = 'X';
                }
            }
        }

    } while (nRead != EOF);
    
    fclose(f1);
}


int setupGame(int argc, char* argv[]) 
{ /*used for initialising command line input, organising map setup, initialising game loop, everything set up wise*/
    char** map;
    
    int nR,nC,pR,pC,gR,gC,check;

    check = readMapFile(argv, &nR, &nC, &pR, &pC, &gR, &gC);
    
    printf("nR equals %d and nC equals %d \n", nR, nC);
    printf("pR equals %d and pC equals %d \n", pR, pC);
    printf("gR equals %d and gC equals %d \n", gR, gC);

    if(check)
    {
        setupMap(&map,nR,nC,pR,pC,gR,gC, argv);

        printMap(map,nR,nC);

        gameloop(map, nR, nC, pR, pC, gR, gC);
    }

    return 0;
}

int readMapFile(char* argv[], int *nR, int *nC, int *pR, int *pC, int *gR, int *gC)
{
    int nRead, int1, int2, xR, xC, check;
    char c1;
    FILE* f1 = fopen(argv[1], "r");
    check = 1;
    if(f1 == NULL)
    {
        perror("Error opening f1");
    }
    nRead = fscanf(f1, "%d %d ", &(*nR), &(*nC));
    *nR += 2;
    *nC += 2;
    

    if(*nR < 7 || *nC < 7) /*7 because the inside can't be smaller than 5 and 7 is the number of whole array including border*/
    {
        printf("Map size too small!\n");
        check = 0;
    }


    do
    {
        nRead = fscanf(f1, "%d %d %c ", &int1, &int2, &c1);
        if(nRead != EOF)
        {
            if(c1 == 'P')
            {
                *pR = int1 + 1;
                *pC = int2 + 1;
            }
            if(c1 == 'G')
            {
                *gR = int1 + 1;
                *gC = int2 + 1;
            }
            if(c1 == 'X')
            {
                xR = int1 + 1;
                xC = int2 + 1;
                if(xR > *nR - 2 || xC > *nC - 2)
                {
                    printf("X position placed outside of map area!\n");
                    check = 0;
                }
                if(xR < 1 || xC < 1)
                {
                    printf("Cannot enter negative numbers!\n");
                    check = 0;
                }
            }
        }
    } while (nRead != EOF);
    
    if(*nR < 2 || *nC < 2 || *pR < 1 || *pC < 1 || *gR < 1 || *gC < 1) /*numbers are higher than 0 because of the addition done above*/
    {
        printf("Cannot enter negative numbers!\n");
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
    
    fclose(f1);

    return check;
}