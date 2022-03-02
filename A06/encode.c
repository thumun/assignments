#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {

    char * filename;
    int width;
    int height;

    struct ppm_pixel * arrPx;

    char newFilename[32];
    char usrPhrase[1000];

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

    char * numChar = malloc(sizeof(char)*width*height*3 + 10);

    // testing output
    printf("Reading %s.ppm with width %d and height %d\n", filename, width, height);
    printf("Max number of characters in the image: %d\n", (width*height*3)/8);
    printf("Enter a phrase: ");
    scanf("%s", usrPhrase);

    // making new filename from old one
    strncpy(newFilename, filename, strlen(filename)-4);
    newFilename[strlen(filename)-4] = '\0';
    strcat(newFilename, "-neha-encoded.ppm");

    // adding encoding & writing to new file
    write_ppm(newFilename, arrPx, width, height, usrPhrase);
    printf("\nWriting file %s", newFilename);

    // free-ing
    free(arrPx);
    free(numChar);
    arrPx = NULL;
    numChar = NULL;

    return 0;
}

