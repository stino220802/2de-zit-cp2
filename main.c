#include "personalLib.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * Als extra heb ik ervoor gezorgd dat dit project bmp images van elke grote kan lezen dus breedte en hoogte maken niet uit.
 * Ook heb ik nog een inverted file toegevoegd met de pixels geinverteerd
 */
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