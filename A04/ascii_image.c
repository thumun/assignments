#include <stdio.h>
#include "read_ppm.h"

// ADJUST WIDTH AND HEIGHT OF IMAGE!!
void terribleMethod(float intensity){
    char weird = '%';

    if (intensity <= 255.0 && intensity > 225.0){
        printf(" ");
    } else if (intensity <= 225.0 && intensity > 200.0){
        printf(".");
    } else if (intensity <= 200.0 && intensity > 175.0){
        printf(",");
    } else if (intensity <= 175.0 && intensity > 150.0){
        printf(":");
    } else if (intensity <= 150.0 && intensity > 125.0){
        printf(";");
    } else if (intensity <= 125.0 && intensity > 100.0){
        printf("o");
    } else if (intensity <= 100.0 && intensity > 75.0){
        printf("*");
    } else if (intensity <= 75.0 && intensity > 50.0){
        printf("%c", weird);
    } else if (intensity <= 50.0 && intensity > 25.0){
        printf("#");
    } else if (intensity <= 25.0){
        printf("@");
    }
}

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

    float intensity;

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            intensity = (arrPx[i][j].red + arrPx[i][j].green + arrPx[i][j].blue);
            intensity = intensity / 3;
            //printf("intensity: %f\n", intensity);
            terribleMethod(intensity);
        }
    }

    return 0;
}

