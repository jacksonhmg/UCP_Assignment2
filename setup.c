#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "macros.h"
#include "setup.h"
#include "gameloop.h"
#include "checkers.h"
#include "LinkedList.h"


void setupMap(mapStruct* map2, char* argv[]) /*initialise first iteration of map*/
{
    int i,j, nRead, int1, int2;
    char c1;
    FILE* f1 = fopen(argv[1], "r");
    system("clear");
    map2->map = (char**)calloc(map2->nR,sizeof(char*));
    if(f1 == NULL)
    {
        perror("Error opening f1");
    }
    for(i=0;i<map2->nR;i++)
    {
        (map2->map)[i] = (char*)calloc(map2->nC, sizeof(char));
    }
    for(i=0;i<map2->nR;i++)
    {
        (map2->map)[i][map2->nC-1] = '*';
    }
    for(i=0;i<map2->nR;i++)
    {
        (map2->map)[i][0] = '*';
    }
    for(i=0;i<map2->nC;i++)
    {
        (map2->map)[0][i] = '*';
    }
    for(i=0;i<map2->nC;i++)
    {
        (map2->map)[map2->nR-1][i] = '*';
    }
    
    for(i=0;i<map2->nR;i++)
    {
        for(j=0;j<map2->nC;j++)
        {
            if((map2->map)[i][j] == 0)
            {
                (map2->map)[i][j] =  ' '; /*create empty space look*/
            }
        }
    }

    (map2->map)[map2->gR][map2->gC] = 'G';
    (map2->map)[map2->pR][map2->pC] = 'P';

    map2->recentXR = -1;
    map2->recentXC = -1;


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
                if(!(int1 == map2->pR && int2 == map2->pC) && !(int1 == map2->gR && int2 == map2->gC))
                {
                    (map2->map)[int1][int2] = 'X';
                }
            }
        }

    } while (nRead != EOF);
    
    fclose(f1);
}


int setupGame(int argc, char* argv[]) 
{ /*used for initialising command line input, organising map setup, initialising game loop, everything set up wise*/
    LinkedList* list = NULL;
    mapStruct* map2 = (mapStruct*)malloc(sizeof(mapStruct));
    int check;
    list = createLinkedList();
    insertFirst(list, map2);

    check = readMapFile(argv, list->pHead->pData);

    if(check)
    {
        setupMap(list->pHead->pData, argv);

        printMap(list->pHead->pData);

        gameloop(list);
    }

    return 0;
}

int readMapFile(char* argv[], mapStruct* map2)
{
    int nRead, int1, int2, xR, xC, check;
    char c1;
    FILE* f1 = fopen(argv[1], "r");
    check = 1;
    if(f1 == NULL)
    {
        perror("Error opening f1");
    }
    nRead = fscanf(f1, "%d %d ", &map2->nR, &map2->nC);
    map2->nR += 2;
    map2->nC += 2;
    

    if(map2->nR < 7 || map2->nC < 7) /*7 because the inside can't be smaller than 5 and 7 is the number of whole array including border*/
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
                map2->pR = int1 + 1;
                map2->pC = int2 + 1;
            }
            if(c1 == 'G')
            {
                map2->gR = int1 + 1;
                map2->gC = int2 + 1;
            }
            if(c1 == 'X')
            {
                xR = int1 + 1;
                xC = int2 + 1;
                if(xR > map2->nR - 2 || xC > map2->nC - 2)
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
    
    if(map2->nR < 2 || map2->nC < 2 || map2->pR < 1 || map2->pC < 1 || map2->gR < 1 || map2->gC < 1) /*numbers are higher than 0 because of the addition done above*/
    {
        printf("Cannot enter negative numbers!\n");
        check = 0;
    }

    if(map2->pR > map2->nR - 2 || map2->pC > map2->nC - 2)
    {
        printf("Player position placed outside of map area!\n");
        check = 0;
    }
    if(map2->gR > map2->nR - 2 || map2->gC > map2->nC - 2)
    {
        printf("Goal position placed outside of map area!\n");
        check = 0;
    }
    
    fclose(f1);

    return check;
}