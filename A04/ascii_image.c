#include <stdio.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  // todo

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

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    float intensity;

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            intensity = (1/3) * (arrPx[i][j].red+arrPx[i][j].green+arrPx[i][j].blue);

            // now if cases to see what to print
        }
    }

    return 0;
}

