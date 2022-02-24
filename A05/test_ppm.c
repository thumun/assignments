#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// printing items in array (r, g, b values for each pixel)
void printArr(struct ppm_pixel * arrPx, int w, int h){
    for (int i = 0; i < w*h; i++){
        printf("(%u, %u, %u) \t", arrPx[i].red, arrPx[i].green, arrPx[i].blue);

        if ((i+1)%h == 0){
            printf("\n");
        }
    }

//    for (int i = 0; i < h; i++){
//        for (int j = 0; j < w; j++){
//            printf("(%u, %u, %u) \t", arrPx[i][j].red, arrPx[i][j].green, arrPx[i][j].blue);
//        }
//        printf("\n");
//    }
}

int main(int argc, char** argv) {

//    struct ppm_pixel pixel;
//    pixel.red = 100;
//    pixel.green = 200;
//    pixel.blue = 50;
//
//    printf(" pixel before %d\n", pixel.red);
//
//    ((unsigned char*)&pixel)[0] = 150;
//    printf(" pixel after %d\n", pixel.red);

    char filename[32];
    int width;
    int height;

    struct ppm_pixel * arrPx;


    strcpy(filename, "feep-raw.ppm");

    arrPx = read_ppm(filename, &width, &height);
    printArr(arrPx, width, height);

    free(arrPx);

  return 0;
}

