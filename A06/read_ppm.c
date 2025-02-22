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

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {

    FILE * fp = NULL;

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
    fp=NULL;

}
