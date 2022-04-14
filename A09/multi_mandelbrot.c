#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"

void computeMandelbrot(struct ppm_pixel* arrPx, struct ppm_pixel* palette, int rowleft, int rowright, int colup, int coldown, float xmin, float xmax, float ymin, float ymax, int maxIterations){
    // computing fractals
    for (int i = rowleft; i < rowright; i++) {
        for (int j = colup; j < coldown; j++) {
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

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

    double timer = 0.0;

  int numProcesses = 4;

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
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here

    // creating the palette based on maxIterations
    struct ppm_pixel * palette = (struct ppm_pixel *) malloc(maxIterations * sizeof(struct ppm_pixel));

    // generating rgb vals
    for (int i = 0; i < maxIterations; i++) {
        palette[i].red = rand() % 255;
        palette[i].green = rand() % 255;
        palette[i].blue = rand() % 255;
    }

    int shmid;
    shmid = shmget(IPC_PRIVATE, size * size * sizeof(struct ppm_pixel), 0644 | IPC_CREAT);
    if (shmid == -1) {
        perror("Error: cannot initialize shared memory\n");
        exit(1);
    }

    // allocating space for array of pixels (for fractals)
    struct ppm_pixel * arrPx = (struct ppm_pixel *) shmat(shmid, NULL, 0);

    gettimeofday(&tstart, NULL);

    for (int i = 0; i < numProcesses; i++){
        pid_t child = fork();

        if (child == 0){
            printf("Launched child process: %d", child);
            printf("%d) Sub-image block: cols (%d, %d) to rows (&d, %d)", child, 0, (int)size/2, 0, (int)size/2);

            computeMandelbrot(arrPx, palette, 0, size/2, 0, size/2, xmin, xmax, ymin, ymax, maxIterations);

            exit(0);
        } else if (child < 1) {
            // parent process here

            pid_t childtwo = fork();

            if (childtwo == 0){
                printf("Launched child process: %d", childtwo);
                printf("%d) Sub-image block: cols (%d, %d) to rows (&d, %d)", child, (int)size/2, size, 0, (int)size/2);

                computeMandelbrot(arrPx, palette, (int)size/2, size, 0, (int)size/2, xmin, xmax, ymin, ymax, maxIterations);

                exit(0);

            } else if (childtwo < 1){

                pid_t childthree = fork();

                if (childthree == 0){
                    printf("Launched child process: %d", childthree);
                    printf("Launched child process: %d", childtwo);
                    printf("%d) Sub-image block: cols (%d, %d) to rows (&d, %d)", child, 0, (int)size/2, (int)size/2, size);

                    computeMandelbrot(arrPx, palette, 0, (int)size/2, (int)size/2, size, xmin, xmax, ymin, ymax, maxIterations);

                    exit(0);

                } else if (childthree < 1){

                    pid_t childfour = fork();

                    if (childfour == 0){
                        printf("Launched child process: %d", childfour);
                        printf("Launched child process: %d", childtwo);
                        printf("%d) Sub-image block: cols (%d, %d) to rows (&d, %d)", child, (int)size/2, size, (int)size/2, size);

                        computeMandelbrot(arrPx, palette, (int)size/2, size, (int)size/2, size, xmin, xmax, ymin, ymax, maxIterations);

                        exit(0);

                    } else if (childfour < 1){

                    }

                }

            }

        }
    }

    gettimeofday(&tend, NULL);
    timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;



    // generate pallet
  // compute image
}
