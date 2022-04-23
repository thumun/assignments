#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include "read_ppm.h"

static unsigned long long maxCount = 0;
pthread_mutex_t mutex;
pthread_barrier_t barrier;

struct thread_data {
    struct ppm_pixel * arrPx;
    struct ppm_pixel * palette;
    int rowMin;
    int colMin;
    int rowMax;
    int colMax;
    float xmin;
    float xmax;
    float ymin;
    float ymax;
    int maxIterations;
    int size;
    bool * membership;
    int * count;
};

void * computeMandelbrot(void * inputData){

    struct thread_data *data = (struct thread_data *) inputData;

    // computing fractals

    for (int i = data->rowMin; i < data->rowMax; i++) {
        for (int j = data->colMin; j < data->colMax; j++) {
            float xfrac = j / (float) data->size;
            float yfrac = i / (float) data->size;
            float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
            float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

            float x = 0;
            float y = 0;
            int iter = 0;

            while (iter < data->maxIterations && (x * x + y * y < 2 * 2)) {
                float xtmp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtmp;

                iter++;
            }

            if (iter < data->maxIterations) {
                data->membership[i * data->size + j] = false;
            } else {
                data->membership[i * data->size + j] = true;
            }
        }
    }

    // computing visited counts [step 2]

    for (int i = data->rowMin; i < data->rowMax; i++) {
        for (int j = data->colMin; j < data->colMax; j++) {

            if (data->membership[i * data->size + j] == true) {

                float xfrac = j / (float) data->size;
                float yfrac = i / (float) data->size;
                float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
                float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

                float x = 0;
                float y = 0;

                int iter = 0;

                while (iter < data->maxIterations && (x * x + y * y < 2 * 2)) {
                    float xtmp = x * x - y * y + x0;
                    y = 2 * x * y + y0;
                    x = xtmp;

                    int yrow = round(data->size * (y - data->ymin) / (data->ymax - data->ymin));
                    int xcol = round(data->size * (x - data->xmin) / (data->xmax - data->xmin));

                    if (yrow < 0 || yrow >= data->size) continue; // out of range
                    if (xcol < 0 || xcol >= data->size) continue; // out of range

                    data->count[i * data->size + j] += 1;

                    pthread_mutex_lock(&mutex);
                    if (maxCount < data->count[yrow * data->size + xcol]) {
                        maxCount = data->count[yrow * data->size + xcol];
                    }
                    pthread_mutex_unlock(&mutex);
                }
            }
        }
    }

    pthread_barrier_wait(&barrier);

    // step 3.) compute colors

    double gamma = 0.681;
    double factor = 1.0/gamma;

    for (int i = data->rowMin; i < data->rowMax; i++) {
        for (int j = data->colMin; j < data->colMax; j++) {

            double value = 0;

            if (data->count[i * data->size + j] > 0){
                value = log(data->count[i * data->size + j])/log(maxCount);
                value = pow(value, factor);
            }

            data->arrPx[i * data->size + j].red = value * 255;
            data->arrPx[i * data->size + j].blue = value * 255;
            data->arrPx[i * data->size + j].green = value * 255;

        }
    }

    return NULL;
}


int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.5;
  float xmax = 1.0;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

    double timer;
    struct timeval tstart, tend;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating buddhabrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here
  // compute image

    srand(time(0));

    // generate pallet
    // creating the palette based on maxIterations
    struct ppm_pixel * palette = (struct ppm_pixel *) malloc(maxIterations * sizeof(struct ppm_pixel));

    // generating rgb vals
    for (int i = 0; i < maxIterations; i++) {
        palette[i].red = rand() % 255;
        palette[i].green = rand() % 255;
        palette[i].blue = rand() % 255;
    }

    // allocating space for array of pixels (for fractals)
    struct ppm_pixel * arrPx = (struct ppm_pixel *) malloc(size * size * sizeof(struct ppm_pixel));

    bool * membership = (bool *) malloc(size * size * sizeof(bool));
    int * count = (int *) malloc(size * size * sizeof(int));
    memset(count, 0, size * size * sizeof(int));

    gettimeofday(&tstart, NULL);

    // compute image

    pthread_barrier_init(&barrier,NULL,4);

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[4];
    struct thread_data data[4];

    for (int i = 0; i < 4; i++) {
        data[i].arrPx = arrPx;
        data[i].palette = palette;

        if (i == 0){
            data[i].rowMin = 0;
            data[i].colMin = 0;
            data[i].rowMax = size/2;
            data[i].colMax = size/2;
        } else if (i == 1){
            data[i].rowMin = 0;
            data[i].colMin = size/2;
            data[i].rowMax = size/2;
            data[i].colMax = size;
        } else if (i == 2){
            data[i].rowMin = size/2;
            data[i].colMin = 0;
            data[i].rowMax = size;
            data[i].colMax = size/2;
        } else {
            data[i].rowMin = size/2;
            data[i].colMin = size/2;
            data[i].rowMax = size;
            data[i].colMax = size;
        }

        data[i].xmin = xmin;
        data[i].xmax = xmax;
        data[i].ymin = ymin;
        data[i].ymax = ymax;
        data[i].maxIterations = maxIterations;
        data[i].size = size;
        data[i].membership = membership;
        data[i].count = count;

        pthread_create(&threads[i], NULL, computeMandelbrot, (void*) &data[i]);
        printf("Thread %d) sub-image block: cols (%d, %d) to rows (%d, %d)\n",
               (int) threads[i], data[i].colMin, data[i].colMax, data[i].rowMin, data[i].rowMax);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %d) finished\n", (int) threads[i]);
    }

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    gettimeofday(&tend, NULL);
    timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;

    printf("Computed buddhabrot set (%dx%d) in %g seconds\n", size, size, timer);


    // making filename
    char filename[100];
    //sprintf(filename, "buddhabrot-%d-%ld.ppm", size, time(0));

    //CHANGE BACK TO ACTUAL FILENAME
    sprintf(filename, "buddhabrot.ppm");

    // write to file
    write_ppm(filename, arrPx, size, size);
    printf("\nWriting file %s", filename);

    // free stuff
    free(arrPx);
    free(palette);

    free(count);
    free(membership);

    arrPx = NULL;
    palette = NULL;

    count = NULL;
    membership = NULL;

    // also check free in valgrind
}
