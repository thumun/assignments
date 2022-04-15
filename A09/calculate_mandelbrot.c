#include <stdio.h>
#include <stdlib.h>
#include "calculate_mandelbrot.h"

void computeMandelbrot(struct ppm_pixel* arrPx, struct ppm_pixel* palette, int size, int rowMin, int colMin, int rowMax,
                       int colMax, float xmin, float xmax, float ymin, float ymax, int maxIterations){
    // computing fractals

    for (int i = rowMin; i < rowMax; i++) {
        for (int j = colMin; j < colMax; j++) {
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
}