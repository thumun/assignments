#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {

    for (int i = 0; i < 11; i++){
        int * test = (int*) malloc(sizeof(int) * 25); // equals to 100
        free(test);
    }

    // how do I check how many bytes were allocated
    // get stack frames?

  return 0 ;
}
