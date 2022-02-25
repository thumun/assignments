#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"


int main(int argc, char** argv) {
    char * filename;
    char newFilename [32];
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

    //strcpy(filename, "feep-raw.ppm");

    arrPx = read_ppm(filename, &width, &height);

    printf("Reading %s with width %d and height %d\n", filename, width, height);


    strncpy(newFilename, filename, strlen(filename)-4);
    newFilename[strlen(filename)-4] = '\0';

    strcat(newFilename, "-glitch.ppm");

    write_ppm(newFilename, arrPx, width, height);

    printf("Writing file %s\n", newFilename);

    free(arrPx);
    arrPx = NULL;

    return 0;
}
