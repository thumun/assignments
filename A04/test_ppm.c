#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include <string.h>

// printing items in array (r, g, b values for each pixel)
void printArr(struct ppm_pixel ** arrPx, int w, int h){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            printf("(%u, %u, %u) \t", arrPx[i][j].red, arrPx[i][j].green, arrPx[i][j].blue);
        }
        printf("\n");
    }
}

// changed inputs so ca =n test with other ascii files
int main() {
    // todo: call read_ppm

    char filename[32];
    int width;
    int height;

    struct ppm_pixel ** arrPx;

    // input checker
//    if (argc != 2){
//        printf("usage:");
//        for (int i = 0; i < argc; i++){
//            printf(" %s", argv[i]);
//        }
//        return 1;
//    }

    //filename = argv[1];

    strcpy(filename, "feep-ascii.ppm");

    arrPx = read_ppm(filename, &width, &height);

    printf("Testing file %s: %d %d\n", filename, width, height);

    printArr(arrPx, width, height);

    // deallocating
    for(int i = 0; i < height; i++) {
        free(arrPx[i]);
    }

    free(arrPx);
    arrPx = NULL;

  return 0;
}

