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
            float xfrac = j / (float) (rowright - rowleft);
            float yfrac = i / (float) (coldown - colup);
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
                arrPx[i * (rowright - rowleft) + j].red = palette[iter].red;
                arrPx[i * (rowright - rowleft) + j].blue = palette[iter].blue;
                arrPx[i * (rowright - rowleft) + j].green = palette[iter].green;
            } else {
                arrPx[i * (rowright - rowleft) + j].red = 0;
                arrPx[i * (rowright - rowleft) + j].blue = 0;
                arrPx[i * (rowright - rowleft) + j].green = 0;
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
    struct timeval tstart, tend;

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

    srand(time(0));

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
            // depending on which child process: computes a different part
            if (i == 0){
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", child, 0, size/2, 0, size/2);
                computeMandelbrot(arrPx, palette, 0, size/2, 0, size/2, xmin, xmax/2, ymin, ymax/2, maxIterations);
            } else if (i == 1){
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", child, size/2, size, 0, size/2);
                computeMandelbrot(arrPx, palette, size/2, size, 0, size/2, xmin/2, xmax, ymin, ymax/2, maxIterations);
            } else if (i == 2){
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", child, 0, size/2, size/2, size);
                computeMandelbrot(arrPx, palette, 0, size/2, size/2, size, xmin, xmax/2, ymin/2, ymax, maxIterations);
            } else {
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", child, size/2, size, size/2, size);
                computeMandelbrot(arrPx, palette, size/2, size, size/2, size, xmin/2, xmax, ymin/2, ymax, maxIterations);
            }

            exit(0);
        } else {
            // parent process here
            printf("Launched child process: %d\n", child);
        }
    }

    // borrowed from the class example
    // waiting for each child to complete
    for (int i = 0; i < 4; i++) {
        int status;
        int pid = wait(&status);
        printf("Child process complete: %d\n", pid);
    }

    gettimeofday(&tend, NULL);
    timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;

    printf("Computed mandelbrot set (%dx%d) in %g seconds\n", size, size, timer);

    // making filename
    char filename[100];
    sprintf(filename, "mandelbrot-%d-%ld.ppm", size, time(0));

    // write to file
    write_ppm(filename, arrPx, size, size);
    printf("\nWriting file %s", filename);

    free(palette);
    palette = NULL;

    // freeing shared memory
    if (shmdt(arrPx) == -1) {
        perror("Error: cannot detatch from shared memory\n");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("Error: cannot remove shared memory\n");
        exit(1);
    }

}
