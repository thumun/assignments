#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {

    FILE * file = NULL;
    char line[1024];
    char magicNum[3];

    struct ppm_pixel * arrPx = NULL;

    file = fopen(filename, "rb");

    // file pointer test
    if (file == NULL) {
        printf("Cannot open file: %s", filename); // print error
        return NULL;
    }

    while (strncmp(fgets(line, sizeof(line), file), "255", 3) != 0) {
        // getting magic number
        if (line[0] == 'P'){
            strncpy(magicNum, line, 2);
            // skipping lines with comments or blanks
        } else if (line[0] == '#' || line[0] == ' '){
            continue;
        } else {
            // getting & setting width & height
            sscanf(line, "%d %d", w, h);

        }
    }

    // if P3 then re-opening as not binary
    if (strcmp(magicNum, "P3") == 0){
        fclose(file);
        fopen(filename, "r");

        while (strncmp(fgets(line, sizeof(line), file), "255", 3) != 0) {
            // getting magic number
            if (line[0] == 'P'){
                strncpy(magicNum, line, 2);
                // skipping lines with comments or blanks
            } else if (line[0] == '#' || line[0] == ' '){
                continue;
            } else {
                // getting & setting width & height
                sscanf(line, "%d %d", w, h);

            }
        }
    }

    arrPx = (struct ppm_pixel *) malloc(*h * *w * sizeof(struct ppm_pixel));

    if (arrPx == NULL){
        printf("malloc failed");
        return NULL;
    }

    // reading stuff in file & putting them as ppm_pixel in the array
    fread(arrPx, sizeof(struct ppm_pixel), *h * *w, file);

    fclose(file);
    file = NULL;

    return arrPx;
}

void charToBin(char letter, unsigned char * buffer){
    for (int i = 0; i < 8; i++){
        // gets each bit from the letter into a buffer via bit shifting & a mask
        buffer[i] = letter >> (7-i) & 0x01;
        //printf("%d", letter >> (7-i) & 0x01);
    }
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h, const char * message) {

    FILE * fp = NULL;

    unsigned char * msgBin = malloc(sizeof(message+1)*8);
    memset(msgBin, 0, sizeof(message+1)*8);

    for (int i = 0; i < strlen(message); i++){
        charToBin(message[i], &msgBin[i*8]);

//        for (int j = 0; j < 8; j++){
//            printf("%d", msgBin[i*8 +j]);
//        }
//        printf("\n");
    }

//    for (int i = 0; i < w*h; i++){
//        pxs[i].red = pxs[i].red | msgBin[i*3];
//        pxs[i].blue = pxs[i].blue | msgBin[i*3+1];
//        pxs[i].green = pxs[i].green | msgBin[i*3+2];
//
//    }

    // file that's being written to
    fp = fopen(filename, "w+");

    // adding header info
    fputs("P6\n", fp);
    fprintf(fp, "%d %d\n", w, h);
    fputs("255\n", fp);

    fclose(fp);

    // opening up file again to add encoded pixel info
    fp = fopen(filename, "ab"); // writing to file

    fwrite(pxs, sizeof(struct ppm_pixel), h * w, fp);

    fclose(fp);
    free(msgBin);

    msgBin = NULL;
    fp=NULL;

}
