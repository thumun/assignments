#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {

    void* heapTop = sbrk(0);

    printf("The initial top of the heap is %p\n", heapTop);

    for (int i = 0; i < 10; i++){
        void * test = (void*) malloc(100);
        free(test);
    }

    void* current = sbrk(0);

    printf("Bytes allocated %ld (0x%lx) \n", current-heapTop, current-heapTop);
 
  return 0 ;
}
