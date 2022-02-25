#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// printing items in array (r, g, b values for each pixel)
void printArr(struct ppm_pixel * arrPx, int w, int h){
    for (int i = 0; i < w*h; i++){
        printf("(%u, %u, %u) \t", arrPx[i].red, arrPx[i].green, arrPx[i].blue);

        // adding new line when going to next column
        if ((i+1)%h == 0){
            printf("\n");
        }
    }
}

int main(int argc, char** argv) {

    char * filename;
    int width;
    int height;

    struct ppm_pixel * arrPx;

    // input checker - change
    if (argc != 2){
        printf("usage:");
        for (int i = 0; i < argc; i++){
            printf(" %s", argv[i]);
        }
        return 1;
    }

    filename = argv[1];

    // reading data as array of pixels
    arrPx = read_ppm(filename, &width, &height);

    // testing output
    printf("Testing file %s: %d %d\n", filename, width, height);
    printArr(arrPx, width, height);

    // free-ing
    free(arrPx);
    arrPx = NULL;

    return 0;
}

