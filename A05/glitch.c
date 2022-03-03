#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void addGlitch(struct ppm_pixel* pxs, int w, int h){
    // basic bit shift (with rand)
//    for (int i = 0; i < w*h; i++){
//        pxs[i].red = pxs[i].red << rand()%2;
//        pxs[i].blue = pxs[i].blue << rand()%2;
//        pxs[i].green = pxs[i].green << rand()%2;
//
//    }

    //half and half
    for (int i = 0; i < (w*h)/2; i++){
        pxs[i].red = pxs[i].red << rand()%2;
        pxs[i].blue = pxs[i].blue << rand()%2;
        pxs[i].green = pxs[i].green << (rand()%2)/8;

    }

    for (int i = (w*h)/2; i < w*h; i++){
        pxs[i].red = pxs[i].red << rand()%2;
        pxs[i].blue = pxs[i].blue << 2*rand()%2;
        pxs[i].green = pxs[i].green << rand()%2;

    }
}

int main(int argc, char** argv) {
    char * filename;
    char newFilename [32];
    int width;
    int height;

    struct ppm_pixel * arrPx;

    // input checker
    if (argc != 2){
        printf("usage:");
        for (int i = 0; i < argc; i++){
            printf(" %s", argv[i]);
        }
        return 1;
    }

    filename = argv[1];


    // reading the file & getting pixel data as array
    arrPx = read_ppm(filename, &width, &height);
    printf("Reading %s with width %d and height %d\n", filename, width, height);

    // making new filename from old one
    strncpy(newFilename, filename, strlen(filename)-4);
    newFilename[strlen(filename)-4] = '\0';
    strcat(newFilename, "-glitch.ppm");

    // adding glithc
    addGlitch(arrPx, width, height);

    //writing to new file
    write_ppm(newFilename, arrPx, width, height);
    printf("Writing file %s\n", newFilename);

    // free-ing stuff
    free(arrPx);
    arrPx = NULL;

    return 0;
}
