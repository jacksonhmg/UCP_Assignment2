#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "setup.h"
#include "random.h"

int main(int argc, char* argv[])
{
    initRandom();
    setupGame(argc, argv);
    
    return 0;
}