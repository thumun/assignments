#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

// printing the items in array (print characters)
void printArr(char ** arr, int w, int h){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

// setting a character for intensity input
char * charSet(float intensity){

    if (intensity <= 255.0 && intensity > 225.0){
        return (" ");
    } else if (intensity <= 225.0 && intensity > 200.0){
        return (".");
    } else if (intensity <= 200.0 && intensity > 175.0){
        return(",");
    } else if (intensity <= 175.0 && intensity > 150.0){
        return(":");
    } else if (intensity <= 150.0 && intensity > 125.0){
        return(";");
    } else if (intensity <= 125.0 && intensity > 100.0){
        return("o");
    } else if (intensity <= 100.0 && intensity > 75.0){
        return("*");
    } else if (intensity <= 75.0 && intensity > 50.0){
        return("%");
    } else if (intensity <= 50.0 && intensity > 25.0){
        return ("#");
    } else{
        return ("@");
    }
}

int main(int argc, char** argv) {
    char * filename;
    int width;
    int height;

    struct ppm_pixel ** arrPx;
    char ** outputArr;
    char * temp;

    // input checker - change
    if (argc != 2){
        printf("usage:");
        for (int i = 0; i < argc; i++){
            printf(" %s", argv[i]);
        }
        return 1;
    }

    filename = argv[1];

    arrPx = read_ppm(filename, &width, &height);

    // check this!!
    outputArr = (char **) malloc(sizeof (char*)* height);

    if (outputArr == NULL){
        printf("Malloc failed");
        return 1;
    }

    for(int i = 0; i < height; i++) {
        outputArr[i] = (char *) malloc(sizeof(char)*width);

        if (outputArr[i] == NULL){
            printf("Malloc failed");

            for (int j = 0; j < i; j++){
                free(outputArr[j]);
            }
            return 1;
        }
    }

    float intensity;

    // getting intensity for each pixel
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            intensity = (arrPx[i][j].red + arrPx[i][j].green + arrPx[i][j].blue);
            intensity = intensity / 3;
            temp = charSet(intensity);
            outputArr[i][j] = *temp;
        }
    }

    printArr(outputArr, width, height);

    // deallocating
    for(int i = 0; i < height; i++) {
        free(arrPx[i]);
    }

    free(arrPx);
    arrPx = NULL;

    for(int i = 0; i < height; i++) {
        free(outputArr[i]);
    }
    free(outputArr);
    outputArr = NULL;

    return 0;
}

