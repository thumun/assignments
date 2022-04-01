#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {

    void* heapTop = sbrk(0);

    char buff[2000];
    for (int i = 0; i < 2000; i++){
        buff[i] = '.';
    }
    buff[1999] = '\0';

    printf("%s\n", buff);
    //printf("The initial top of the heap is %p\n", heapTop);

    void* current = sbrk(0);

    printf("The current top of the heap is %p\n", current);

    // check in bytes!!!
    printf("Increased by %ld (0x%lx) bytes\n", current-heapTop, current-heapTop);

    return 0 ;
}
