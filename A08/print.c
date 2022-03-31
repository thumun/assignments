#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {

    void* heapTop = sbrk(0);

    printf("The initial top of the heap is %p", heapTop);

    void* current = sbrk(0);

    printf("The current top of the heap is %p", current);

    // check in bytes!!!
    printf("Increased by %d (0x%0.3x) bytes", current-heapTop, current-heapTop);

    return 0 ;
}
