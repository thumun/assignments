#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include <string.h>

int main(int argc, char *argv[]) {
    int size = 480;
    float xmin = -2.0;
    float xmax = 0.47;
    float ymin = -1.12;
    float ymax = 1.12;
    int maxIterations = 1000;

    struct ppm_pixel *arrPx;

    // getting command line info
    int opt;
    while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
        switch (opt) {
            case 's':
                size = atoi(optarg);
                break;
            case 'l':
                xmin = atof(optarg);
                break;
            case 'r':
                xmax = atof(optarg);
                break;
            case 't':
                ymax = atof(optarg);
                break;
            case 'b':
                ymin = atof(optarg);
                break;
            case '?':
                printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]);
                break;
        }
    }
    printf("Generating mandelbrot with size %dx%d\n", size, size);
    printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
    printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

    // allocating space for array of pixels (for fractals)
    arrPx = (struct ppm_pixel *) malloc(size * size * sizeof(struct ppm_pixel));

    srand(time(0));

    // creating the palette based on maxIterations
    struct ppm_pixel *palette = (struct ppm_pixel *) malloc(maxIterations * sizeof(struct ppm_pixel));

    // generating rgb vals
    for (int i = 0; i < maxIterations; i++) {
        palette[i].red = rand() % 255;
        palette[i].green = rand() % 255;
        palette[i].blue = rand() % 255;
    }

    // computing fractals
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float xfrac = j / (float) size;
            float yfrac = i / (float) size;
            float x0 = xmin + xfrac * (xmax - xmin);
            float y0 = ymin + yfrac * (ymax - ymin);

            float x = 0;
            float y = 0;
            int iter = 0;

            while (iter < maxIterations && (x * x + y * y < 2 * 2)) {
                float xtmp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtmp;

                iter++;
            }

            if (iter < maxIterations) {
                arrPx[i * size + j].red = palette[iter].red;
                arrPx[i * size + j].blue = palette[iter].blue;
                arrPx[i * size + j].green = palette[iter].green;
            } else {
                arrPx[i * size + j].red = 0;
                arrPx[i * size + j].blue = 0;
                arrPx[i * size + j].green = 0;
            }
        }
    }

    printf("Computed mandelbrot set (%dx%d) in 0.%ld seconds\n", size, size, time(0));

    // making filename
    char filename[100];
    sprintf(filename, "mandelbrot-%d-%ld.ppm", size, time(0));

    // writing to new file
    write_ppm(filename, arrPx, size, size);
    printf("\nWriting file %s", filename);

}
