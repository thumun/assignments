#include <stdio.h>
#include <stdlib.h>

// readvector opens and reads the given file
// The size of the vector should be stored in the parameter size
// The values should be returned in a flat float array
float* readvector(const char* filename, int *size) {
    FILE * file = NULL;

    file = fopen(filename, "r");

    float * vector;

    // file pointer test
    if (file == NULL) {
        printf("Cannot open file: %s", filename); // print error
        exit(1);
    }
    char buff[100];
    fgets(buff,100,file);
    sscanf(buff,"%d",size);
    vector = malloc(sizeof(size));
    for(int i = 0; i < *size;i++){
        fscanf(file,"%f",&vector[i]);
    }

    fclose(file);
    return vector;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: readvector <filename>\n");
    exit(0);
  }

  int size = 0;
  float* vector = readvector(argv[1], &size);

  for(int i = 0; i < size;i++){
      printf("%f\n",vector[i]);
  }

  free(vector);
  return 0;
}

