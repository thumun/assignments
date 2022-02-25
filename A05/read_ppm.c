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

//            *w = atoi(&line[0]);
//            *h = atoi(&line[2]);

        }
    }

    arrPx = (struct ppm_pixel *) malloc(*h * *w * sizeof(struct ppm_pixel));

    if (arrPx == NULL){
        printf("malloc failed");
        return NULL;
    }

    fread(arrPx, sizeof(struct ppm_pixel), *h * *w, file);

    fclose(file);
    file = NULL;

    return arrPx;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {

    FILE * fp = NULL;

    printf("filename: %s\n", filename);

    // basic bit shift (rand)
//    for (int i = 0; i < w*h; i++){
//        pxs[i].red = pxs[i].red << rand()%2;
//        pxs[i].blue = pxs[i].blue << rand()%2;
//        pxs[i].green = pxs[i].green << rand()%2;
//
//    }

 //half and half
    for (int i = 0; i < (w*h)/2; i++){
        pxs[i].red = pxs[i].red << rand()%2;
        pxs[i].blue = pxs[i].blue << rand()%2;
        pxs[i].green = pxs[i].green << (rand()%2)/8;

    }

    for (int i = (w*h)/2; i < w*h; i++){
        pxs[i].red = pxs[i].red << rand()%2;
        pxs[i].blue = pxs[i].blue << 2*rand()%2;
        pxs[i].green = pxs[i].green << rand()%2;

    }



    fp = fopen(filename, "w+");

    fputs("P6\n", fp);
    fprintf(fp, "%d %d\n", w, h);
    fputs("255\n", fp);

    fclose(fp);

    fp = fopen(filename, "ab"); // writing to file

    //strcat(newFilename, "-glitch.ppm");

    fwrite(pxs, sizeof(struct ppm_pixel), h * w, fp);

    fclose(fp);

}
