#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void charToBin(char letter, unsigned char * buffer){
    for (int i = 0; i < 8; i++){
        // gets each bit from the letter into a buffer via bit shifting & a mask
        buffer[i] = letter >> (7-i) & 0x01;
    }
}

void encodingMsg(struct ppm_pixel* pxs, int w, int h, const char * message){
    // allocating space for adding message in binary format
    unsigned char * msgBin = malloc(sizeof(message+1)*8);
    memset(msgBin, 0, sizeof(message+1)*8);

    // getting binary for each letter of the user input (message)
    for (int i = 0; i < strlen(message); i++){
        charToBin(message[i], &msgBin[i*8]);
    }

    char mask = 0xfe;

    // AND w/ mask in order to make the least significant bit always 0
    // OR w/ msgBin in order to set this least significant bit to the desired val
    for (int i = 0; i < w*h; i++){
        pxs[i].red = (pxs[i].red & mask) | msgBin[i*3];
        pxs[i].green = (pxs[i].green & mask) | msgBin[i*3+1];
        pxs[i].blue = (pxs[i].blue & mask) | msgBin[i*3+2];
    }

    // free-ing
    free(msgBin);
    msgBin = NULL;
}

int main(int argc, char** argv) {

    char * filename;
    int width;
    int height;

    char * usrPhrase;
    struct ppm_pixel * arrPx;

    char newFilename[32];

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
    printf("Reading %s.ppm with width %d and height %d\n", filename, width, height);
    printf("Max number of characters in the image: %d\n", (width*height*3)/8);

    // malloc'ing the space based on max num of char in image
    usrPhrase = malloc(sizeof(char)*(width*height*3)/8);

    printf("Enter a phrase: ");
    // now can read blank spaces
    scanf("%[^\n]%*c", usrPhrase);
    //scanf("%s", usrPhrase);
    //fgets(usrPhrase, sizeof(char)*(width*height*3)/8, stdin);

    //printf("testing statement: %s", usrPhrase);

    // making new filename from old one
    strncpy(newFilename, filename, strlen(filename)-4);
    newFilename[strlen(filename)-4] = '\0';
    strcat(newFilename, "-neha-encoded.ppm");

    // editing arrPx to add encoding
    encodingMsg(arrPx, width, height, usrPhrase);

    // writing to new file
    write_ppm(newFilename, arrPx, width, height);
    printf("Writing file %s", newFilename);

    // free-ing
    free(arrPx);
    free(usrPhrase);
    arrPx = NULL;
    usrPhrase = NULL;

    return 0;
}

