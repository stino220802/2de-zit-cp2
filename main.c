#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
typedef struct TAGimageHeader
{
    // fileType moet een BM string zijn
    unsigned int fileSize;
    unsigned short fileReserverd1; // moet 0 zijn
    unsigned short fileReserverd2; // moet 0 zijn
    unsigned int fileOffset; // offset van de fileheader
}imageHeader;

typedef struct TAGinfoHeader
{
    unsigned int iSize; //grootte van deze structure
    long iWidth; // breedte afbeelding
    long iHeight; // hoogte afbeelding
    unsigned short iPlanes; // Geeft het vlakke attribuut van de bmp-image aan, uiteraard t
    unsigned short iCount; // het aantal bits dat gebruikt word door een pixel
    unsigned int iCompression; // beschrijft het type datacompressie
    unsigned int iSizeImage; // de grootte van de pixel data, moet gelijk zijn aan fileSize of fileOffset
    long iXPelsPerMeter; // horizontale resolutie in pixels per meter
    long iTPelsPerMeter; // verticale resolutie in pixels per meter
    unsigned int iClrUsed; // beschrijft het aantal kleur indexen in kleur tabel die gebruikt worden in de file
    unsigned int iClrImportant; // geeft het aantal kleur indexen dat belangrijk zijn in de image
}infoHeader;

typedef struct PixelInfo{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char rgbReserved; // moet 0 zijn
}pixelInfo;
infoHeader infoHEADER;
imageHeader fileHeader;
int main(){
    FILE* fp;
    fp = fopen("test.bmp", "rb");
    if(fp == NULL){
        printf("Something went wrong while trying to open\n");
        exit(EXIT_FAILURE);
    }
    unsigned short fileType;
    fread(&fileType, 1, sizeof (unsigned short), fp);
    if(fileType == 0x4d42){
        printf("fileType is correct\n");
        printf("file identifier = %d\n", fileType);
        fread(&fileHeader, 1, sizeof(imageHeader), fp);
        fread(&infoHEADER, 1, sizeof(infoHeader), fp);
        fclose(fp);
    }

    /* write the bmp file FILE *f;
    f = fopen("testoutput.bmp", "wb");
    fwrite(&fileHeader, 1, sizeof(imageHeader), f);
    fwrite(&infoHEADER, 1, sizeof(infoHeader), f);*/

    return 0;
}