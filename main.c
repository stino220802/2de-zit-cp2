#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} pixel;

void helpmenu();
int getSizeBmp(FILE *f);
void readInputBmpfile(pixel* RGB, int imageSize, unsigned char* bmpheader, FILE *f);
void outputBMP(pixel* RGB, unsigned char* bmpheader, int imageSize, char* inputFileName);
void removeBMPfromString(char* inputFileName);
void outputRGBRed(unsigned char* RGBRed, pixel* RGB, int imageSize);
char* outputBMPFileName(char* inputFileName, char str[]);
void createOutput(unsigned char* bmpheader, char* outputName, unsigned char* RGBout, int imageSize);
void outputRGBGreen(unsigned char* RGBGreen, pixel* RGB, int imageSize);
void outputRGBBlue(unsigned char* RGBBlue, pixel* RGB, int imageSize);

int main(int argc, char** argv){
    char* inputFileName = malloc(80);
    if(argc == 2 && strcmp(argv[1], "--help") ==0 )
    {
        helpmenu();
        exit(1);
    }
    else if (argc == 3 && strcmp(argv[1], "-i") == 0) {
                strcpy(inputFileName, argv[2]);
            }


    FILE *f = fopen(inputFileName, "rb");
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

    outputBMP(RGB, bmpheader, imageSize,inputFileName);

    fclose(f);
    free(inputFileName);
    free(RGB);
    return 0;
}
void helpmenu(){
    printf("-i met daarachter de inputfile\n ");

    printf("voorbeeld\n");
    printf("./splitchannels -i meme.bmp\n");
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
void outputBMP(pixel* RGB, unsigned char* bmpheader, int imageSize, char* inputFileName){
    removeBMPfromString(inputFileName);
    char strRed[] = "_red.bmp";
    char strGreen[] = "_green.bmp";
    char strBlue[] = "_blue.bmp";

    unsigned char* RGBout = malloc(imageSize * sizeof(*RGBout));
    char* outputName;

    //rood
    outputRGBRed(RGBout, RGB, imageSize);
    outputName = outputBMPFileName(inputFileName, strRed); //voor rood
    createOutput(bmpheader , outputName, RGBout, imageSize ); // voor rood

    //groen
    outputRGBGreen(RGBout, RGB, imageSize);
    outputName = outputBMPFileName(inputFileName, strGreen); //voor groen
    createOutput(bmpheader, outputName, RGBout, imageSize);//voor groen

    //blauw
    outputRGBBlue(RGBout, RGB, imageSize);
    outputName = outputBMPFileName(inputFileName, strBlue);
    createOutput(bmpheader, outputName, RGBout, imageSize);

    free(outputName);
    free(RGBout);
}
void removeBMPfromString(char* inputFileName){
    int a = strlen(inputFileName);

    inputFileName[a-1] = '\0';
    inputFileName[a-2] = '\0';
    inputFileName[a-3] = '\0';
    inputFileName[a-4] = '\0';

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
char* outputBMPFileName(char* inputFileName, char str[]){

    int sizeName = strlen(inputFileName) + strlen(str);

    char* outputName = (char*) malloc(sizeName);
    strcpy(outputName, inputFileName);
    strcat(outputName, str);
    return outputName;

}

void createOutput(unsigned char* bmpheader, char* outputName, unsigned char* RGBout, int imageSize){

    FILE *fp;
    fp = fopen(outputName, "wb");
    if(fp == NULL){
        printf("file does not create\n");
        exit(0);
    }
    printf("file created succesfully\n");
    fwrite(bmpheader, 1, 54, fp);
    fwrite(RGBout, sizeof(unsigned char), imageSize, fp);
    printf("output  finished\n");
    fclose(fp);


}
void outputRGBGreen(unsigned char* RGBGreen, pixel* RGB, int imageSize){
    int x = 0;
    int j = imageSize / 3;
    for(int i = 0; i < j; i++ ){
        RGBGreen[x] = 0;
        RGBGreen[x+1] = 0;
        RGBGreen[x+2] = 0;
        RGBGreen[x+1] = RGB[i].green;
        x = x +3;
    }

}
void outputRGBBlue(unsigned char* RGBBlue, pixel* RGB, int imageSize){
    int x = 0;
    int j = imageSize / 3;
    for(int i = 0; i < j; i++){
        RGBBlue[x] = 0;
        RGBBlue[x+1] = 0;
        RGBBlue[x+2] = 0;
        RGBBlue[x] = RGB[i].blue;
        x = x + 3;
    }
}


//https://www.includehelp.com/c-programs/c-program-to-create-a-file-file-handling-programs.aspx