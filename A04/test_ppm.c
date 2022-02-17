#include <stdio.h>
#include "read_ppm.h"
#include <string.h>

void printArr(struct ppm_pixel ** arrPx, int w, int h){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            printf("(%u, %u, %u) \t", arrPx[i][j].red, arrPx[i][j].green, arrPx[i][j].blue);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    // todo: call read_ppm

    char * filename;
    int width;
    int height;

    struct ppm_pixel ** arrPx;

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

    printf("Testing file %s: %d %d\n", filename, width, height);

    printArr(arrPx, width, height);

  return 0;
}

