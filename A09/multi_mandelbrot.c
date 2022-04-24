#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "calculate_mandelbrot.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

    double timer;
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

    int shmid = shmget(IPC_PRIVATE, size * size * sizeof(struct ppm_pixel), 0644 | IPC_CREAT);
    if (shmid == -1) {
        perror("Error: cannot initialize shared memory\n");
        exit(1);
    }

    int paletteid = shmget(IPC_PRIVATE, maxIterations * sizeof(struct ppm_pixel), 0644 | IPC_CREAT);
    if (paletteid == -1){
        perror("Error: cannot initialize shared memory\n");
        exit(1);
    }


    // creating the palette based on maxIterations
//    struct ppm_pixel * palette = (struct ppm_pixel *) malloc(maxIterations * sizeof(struct ppm_pixel));
    struct ppm_pixel * palette = (struct ppm_pixel *) shmat(paletteid, NULL, 0);


    // generating rgb vals
    for (int i = 0; i < maxIterations; i++) {
        palette[i].red = rand() % 255;
        palette[i].green = rand() % 255;
        palette[i].blue = rand() % 255;
    }


    // allocating space for array of pixels (for fractals)
    struct ppm_pixel * arrPx = (struct ppm_pixel *) shmat(shmid, NULL, 0);

    gettimeofday(&tstart, NULL);

    for (int i = 0; i < numProcesses; i++){
        pid_t child = fork();

        if (child == 0){
            // depending on which child process: computes a different part
            int pid = getpid();
            if (i == 0){
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", pid, 0, size/2, 0, size/2);
                computeMandelbrot(arrPx, palette, size, 0, 0, size/2, size/2, xmin, xmax, ymin, ymax, maxIterations);
            } else if (i == 1){
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", pid, size/2, size, 0, size/2);
                computeMandelbrot(arrPx, palette, size, 0, size/2, size/2, size, xmin, xmax, ymin, ymax, maxIterations);
            } else if (i == 2){
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", pid, 0, size/2, size/2, size);
                computeMandelbrot(arrPx, palette, size, size/2, 0, size, size/2, xmin, xmax, ymin, ymax, maxIterations);
            } else {
                printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n", pid, size/2, size, size/2, size);
                computeMandelbrot(arrPx, palette, size, size/2, size/2, size, size, xmin, xmax, ymin, ymax, maxIterations);
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

//    free(palette);
//    palette = NULL;

    // freeing shared memory
    if (shmdt(arrPx) == -1) {
        perror("Error: cannot detatch from shared memory\n");
        exit(1);
    }

    if (shmdt(palette) == -1) {
        perror("Error: cannot detatch from shared memory\n");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("Error: cannot remove shared memory\n");
        exit(1);
    }

    if (shmctl(paletteid, IPC_RMID, 0) == -1) {
        perror("Error: cannot remove shared memory\n");
        exit(1);
    }
}
