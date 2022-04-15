#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "calculate_mandelbrot.h"
#include <string.h>

int main(int argc, char *argv[]) {
    int size = 480;
    float xmin = -2.0;
    float xmax = 0.47;
    float ymin = -1.12;
    float ymax = 1.12;
    int maxIterations = 1000;

    double timer = 0.0;

    struct timeval tstart, tend;
    struct ppm_pixel * arrPx;
    struct ppm_pixel * palette;

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
    palette = (struct ppm_pixel *) malloc(maxIterations * sizeof(struct ppm_pixel));

    // generating rgb vals
    for (int i = 0; i < maxIterations; i++) {
        palette[i].red = rand() % 255;
        palette[i].green = rand() % 255;
        palette[i].blue = rand() % 255;
    }

    gettimeofday(&tstart, NULL);

    computeMandelbrot(arrPx, palette, size, 0, 0, size, size, xmin, xmax, ymin, ymax, maxIterations);

    gettimeofday(&tend, NULL);
    timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;

    printf("Computed mandelbrot set (%dx%d) in %g seconds\n", size, size, timer);

    // making filename
    char filename[100];
    sprintf(filename, "mandelbrot-%d-%ld.ppm", size, time(0));

    // writing to new file
    write_ppm(filename, arrPx, size, size);
    printf("\nWriting file %s", filename);

    free(arrPx);
    free(palette);

    arrPx = NULL;
    palette = NULL;

}