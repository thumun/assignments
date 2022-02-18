#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// not used but keeping in case useful for future
//void lineParser(char * line, int * returnNum){
//    char intNum[4];
//    intNum[3] = '\0';
//    int countDigit = 0;
//    int countNumArr = 0;
//
//    line[strcspn(line, "\r\n")] = 0; // removes /r /n
//
//    for (int i = 0; i < strlen(line); i++){
//        if (line[i] != ' '){
//            intNum[countDigit] = line[i];
//            countDigit++;
//            intNum[countDigit] = '\0';
//        } else if ((line[i] == ' ' && intNum[0] != '\0')) {
//            returnNum[countNumArr] = atoi(intNum);
//            countNumArr++;
//            intNum[0] = '\0';
//            countDigit = 0;
//        }
//
//        if (i == strlen(line) - 1 && intNum[0] != '\0'){
//            returnNum[countNumArr] = atoi(intNum);
//        }
//    }
//}

// for reading ppm
struct ppm_pixel** read_ppm(const char* filename, int* w, int* h) {
    FILE * file;
    char line[1024];
    struct ppm_pixel ** arrPx;

    char magicNum[3];

    file = fopen(filename, "r");

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
            *w = atoi(&line[0]);
            *h = atoi(&line[2]);

        }
    }

    // allocating for array of pixels
    arrPx = (struct ppm_pixel **) malloc(sizeof (struct ppm_pixel*)* *h);

    if (arrPx == NULL){
        printf("unable to malloc. exiting");
        fclose(file);
        return NULL;
    }

    for(int i = 0; i < *h; i++) {
        arrPx[i] = (struct ppm_pixel *) malloc(sizeof(struct ppm_pixel)* *w);

        // checking malloc
        if (arrPx[i] == NULL){
            printf("unable to malloc. exiting");
            fclose(file);

            for (int j = 0; j < i; j++){
                free(arrPx[j]);
            }
            free(arrPx);
            arrPx = NULL;

            return NULL;
        }
    }

    // going through the file and putting every three numbers into a pixel
    // setting as r, g, and b
    for (int j = 0; j < *h; j++){
        for (int i = 0; i < *w; i++){
            fscanf(file, "%hhu %hhu %hhu", &arrPx[j][i].red, &arrPx[j][i].green,
                   &arrPx[j][i].blue);

        }
    }

    // deallocating
    fclose(file);
    file = NULL;

    return arrPx;
}

