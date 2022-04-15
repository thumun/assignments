//
// Created by Neha Thumu on 4/15/22.
//

#ifndef CALCULATE_MANDELBROT_H
#define CALCULATE_MANDELBROT_H

#include "read_ppm.h"

extern void computeMandelbrot(struct ppm_pixel* arrPx, struct ppm_pixel* palette, int size, int rowMin, int colMin, int rowMax,
        int colMax, float xmin, float xmax, float ymin, float ymax, int maxIterations);

#endif
