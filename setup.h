#ifndef SETUP_H
#define SETUP_H

void setupMap(char***map, int nR, int nC, int pR, int pC, int gR, int gC, char* argv[]);
int setupGame(int argc, char* argv[]);
int readMapFile(char* argv[], int *nR, int *nC, int *pR, int *pC, int *gR, int *gC);

#endif