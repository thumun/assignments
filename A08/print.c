#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {

    void* heapTop = sbrk(0);

    printf("The initial top of the heap is %p\n", heapTop);

    void* current = sbrk(0);

    printf("The current top of the heap is %p\n", current);

    printf("Increased by %ld (0x%lx) bytes\n", current-heapTop, current-heapTop);

    return 0 ;
}
