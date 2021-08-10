#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} pixel;

int getSizeBmp(FILE *f);
void readInputBmpfile(pixel* RGB, int imageSize, unsigned char* bmpheader, FILE *f);
//void fileNames(char* outputFileName, char* outputNameRed, char* outputNameGreen, char* outputNameBlue);
void outputBMP(pixel* RGB, unsigned char* bmpheader, int imageSize);
void outputRGBRed(unsigned char* RGBRed, pixel* RGB, int imageSize);
char outputBMPFileName(char* outputFileName, char str[]);
int main(){
    FILE *f = fopen("rechthoek.bmp", "rb");
    if (f == NULL) {
        printf("something went wrong while opening file");
        exit(1);
    }
    int imageSize = 0;
    imageSize = getSizeBmp(f);
    int arraySize = imageSize/3;
    pixel* RGB = malloc(arraySize * sizeof(*RGB));
    unsigned char *bmpheader = malloc(54);
    readInputBmpfile(RGB, imageSize, bmpheader, f);
    outputBMP(RGB, bmpheader, imageSize);



  /*  printf("%d %d %d %d \n", bmpheader[2], bmpheader[3], bmpheader[4], bmpheader[5]);
    printf("imagesize %d \n", imageSize);
    printf("breedre * hoogte = %d\n", breedte*hoogte);
    printf("breedte %d hoogte %d", breedte, hoogte); // imagesize aanpassen */
    /*if (fp == NULL) {
        printf("something went wrong while opening file");
    }*/

   //fwrite(bmpheader, 1, 54, fp);
    //fwrite(RGB,sizeof(char), imageSize,fp);
    fclose(f);
    //fclose(fp);
    free(RGB);
    return 0;
}
int getSizeBmp(FILE *f){
    unsigned char bmpheader[54];
    fread(bmpheader, sizeof(unsigned char ), 54, f);
    unsigned int breedte = bmpheader[18] | bmpheader[19] << 8 | bmpheader[20] << 16 | bmpheader[21] << 24;
    unsigned int hoogte = bmpheader[22] | bmpheader[23] << 8 | bmpheader[24] << 16 | bmpheader[25] << 24;
    int imageSize = breedte * hoogte * 3;

    return imageSize;
}
void readInputBmpfile(pixel* RGB, int imageSize, unsigned char* bmpheader, FILE* f){
    rewind(f);
    unsigned char tempRGB[imageSize];
    fread(bmpheader, sizeof(unsigned char ), 54, f);
    fread(tempRGB, sizeof(unsigned char), imageSize, f);
    int  x = 0;
    int arraySize = imageSize/3;
    for(int i = 0; i < arraySize; i++){

        RGB[i].blue = tempRGB[x];
        RGB[i].green = tempRGB[x+1];
        RGB[i].red = tempRGB[x+2];
        x = x + 3;
    }


}
void outputBMP(pixel* RGB, unsigned char* bmpheader, int imageSize){
    char *outputFileName = malloc(50);
    printf("geef file naam in van outputfile zonder .bmp\n");
    gets(outputFileName);
    printf("getline werkt\n");
    unsigned char* RGBRed = malloc(imageSize * sizeof(*RGBRed));
    outputRGBRed(RGBRed, RGB, imageSize);

    char str[] = "Red.bmp";

    char* outputName1;

    outputBMPFileName(outputFileName, str);
    free(outputFileName);
    //createOutput();
}
void outputRGBRed(unsigned char* RGBRed, pixel* RGB, int imageSize){
    int x = 0;
    int j = imageSize / 3;
    for(int i = 0; i < j; i++ ){
        RGBRed[x] = 0;
        RGBRed[x+1] = 0;
        RGBRed[x+2] = 0;
        RGBRed[x+2] = RGB[i].red;
        x = x +3;
    }

}
char outputBMPFileName(char* outputFileName, char str[]){

    int sizeName = strlen(outputFileName) + strlen(str);

    char* outputName = (char*) malloc(sizeName);

    strcpy(outputName, outputFileName);
    printf("werkt\n");
    strcat(outputName, str);
    return 0;

}
/*void fileNames(char* outputFileNames, char* outputNameRed, char* outputNameGreen, char* outputNameBlue){
    printf("geef file name in zonder .bmp\n");

    gets(outputFileNames);
    char strRed[] = "Red.bmp";
    char strGreen[] = "Green.bmp";
    char strBlue[] = "Blue.bmp";
    int sizeOutput = strlen(outputFileNames) + strlen(strRed);
    outputNameRed = (char*) malloc(sizeOutput);
    sizeOutput = sizeOutput - strlen(strRed);
    sizeOutput = sizeOutput + strlen(strGreen);
    outputNameGreen = (char*) malloc(sizeOutput);
    sizeOutput = sizeOutput - strlen(strGreen);
    sizeOutput = sizeOutput + strlen(strBlue);
    outputNameBlue = (char*) malloc(sizeOutput);

    strcpy(outputNameRed, outputFileNames);
    strcat(outputNameRed, strRed);
    strcpy(outputNameGreen, outputFileNames);
    strcat(outputNameGreen, strGreen);
    strcpy(outputNameBlue, outputFileNames);
    strcat(outputNameBlue, strBlue);
    printf("%s\n", outputNameRed);
    printf("%s\n", outputNameGreen);
    printf("%s\n", outputNameBlue);

}*/

//https://www.includehelp.com/c-programs/c-program-to-create-a-file-file-handling-programs.aspx