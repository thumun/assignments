#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void lineParser(char * line, int * returnNum){
    char intNum[4];
    intNum[3] = '\0';
    int countDigit = 0;
    int countNumArr = 0;

    line[strcspn(line, "\r\n")] = 0; // removes /r /n

    for (int i = 0; i < strlen(line); i++){
        if (line[i] != ' '){
            intNum[countDigit] = line[i];
            countDigit++;
            intNum[countDigit] = '\0';
        } else if ((line[i] == ' ' && intNum[0] != '\0')) {
            returnNum[countNumArr] = atoi(intNum);
            countNumArr++;
            intNum[0] = '\0';
            countDigit = 0;
        }

        if (i == strlen(line) - 1 && intNum[0] != '\0'){
            returnNum[countNumArr] = atoi(intNum);
        }
    }
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel** read_ppm(const char* filename, int* w, int* h) {
    FILE * file;
    char line[100];
    struct ppm_pixel ** arrPx;
    int * returnNum = (int*) malloc(sizeof(int)*(*w * 3));

    file = fopen(filename, "r");

    // file pointer test
    if (file == NULL) {
        printf("Cannot open file: %s", filename); // print error
        return NULL;
    }

    int lineCount = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == 'P' || line[0] == '#'){ // change to comp with P3
            continue;
        }

        if (lineCount == 0){
            *w = atoi(&line[0]);
            *h = atoi(&line[2]);

//            printf("width: %d\n", *w);
//            printf("height: %d\n", *h);
        } else if (lineCount == 1){ // skipping 255
            arrPx = (struct ppm_pixel **) malloc(sizeof (struct ppm_pixel*)* *h);
            for(int i = 0; i < *w; i++) {
                arrPx[i] = (struct ppm_pixel *) malloc(sizeof(struct ppm_pixel)* *w);
            }
        } else {
            lineParser(line, returnNum);
            for (int i = 0; i < *w; i++) {
                arrPx[lineCount-2][i].red = (unsigned char)returnNum[i*3];
                arrPx[lineCount-2][i].green = (unsigned char)returnNum[i*3 + 1];
                arrPx[lineCount-2][i].blue = (unsigned char)returnNum[i*3 + 2];

            }
        }

        lineCount++;
    }

    // CHECK DEALLOCATION

    fclose(file);
    file = NULL;

    free(returnNum);
    returnNum = NULL;

    return arrPx;
}

