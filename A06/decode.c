#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// getting the least significant bit of each rgb val via modulus 2
void getBits(struct ppm_pixel * arrPx, int w, int h, char * numChar){

    for (int i = 0; i < w*h; i++){
        if (arrPx[i].red % 2 == 0){
            numChar[i*3] = '0';
        } else {
            numChar[i*3] = '1';
        }

        if (arrPx[i].green % 2 == 0){
            numChar[i*3+1] = '0';
        } else {
            numChar[i*3+1] = '1';
        }

        if (arrPx[i].blue % 2 == 0){
            numChar[i*3+2] = '0';
        } else {
            numChar[i*3+2] = '1';
        }
    }

    // making sure that length of string multiple of 8
    // so ascii works properly

    int remainder = w*h*3 % 8;

    for(int i = 0; i < remainder; i++){
        numChar[w*h*3 + i] = '0';
    }
    numChar[w*h*3+remainder] = '\0';
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

    char * numChar = malloc(sizeof(char)*width*height*3 + 10);

    getBits(arrPx, width, height, numChar);

    // testing output
    printf("Reading %s.ppm with width %d and height %d\n", filename, width, height);
    printf("Max number of characters in the image: %d\n", (width*height*3)/8);

    // logic for printing the message
    for (int i = 0; i < strlen(numChar); i++){

        // char is 8 bits
        if (i%8 == 0){

            // temp array to get the 8 bits that make up the char
            char digits[9];
            strncpy(digits, &numChar[i], 8);
            digits[8] = '\0';

            // getting the binary format
            char temp = strtol(digits, 0, 2);
            printf("%c", temp);

            if (temp == '\0'){
                break;
            }
        }
    }

    // free-ing
    free(arrPx);
    free(numChar);
    arrPx = NULL;
    numChar = NULL;

    return 0;
}

