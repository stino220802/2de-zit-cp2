#include "personalLib.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
    char* inputFileName = malloc(80);
    if(argc == 2 && strcmp(argv[1], "--help") ==0 )
    {
        helpmenu();
        exit(1);
    }
    else if (argc == 3 && strcmp(argv[1], "-i") == 0) {
        strcpy(inputFileName, argv[2]);
        code(inputFileName);

    }
    return 0;
}