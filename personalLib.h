#ifndef _personalLib_H_
#define _personalLib_H_
#include <stdio.h>

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} pixel;

void helpmenu();
void code(char* inputFileName);
int getSizeBmp(FILE *f);
void readInputBmpfile(pixel* RGB, int imageSize, unsigned char* bmpheader, FILE *f);
void outputBMP(pixel* RGB, unsigned char* bmpheader, int imageSize, char* inputFileName);
void removeBMPfromString(char* inputFileName);
char* outputBMPFileName(char* inputFileName, char str[]);
void createOutput(unsigned char* bmpheader, char* outputName, unsigned char* RGBout, int imageSize);
void outputRGBRed(unsigned char* RGBRed, pixel* RGB, int imageSize);
void outputRGBGreen(unsigned char* RGBGreen, pixel* RGB, int imageSize);
void outputRGBBlue(unsigned char* RGBBlue, pixel* RGB, int imageSize);
void outputRGBinverted(unsigned char* RGBinverted, pixel* RGB, int imageSize);


#endif