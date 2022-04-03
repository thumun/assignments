#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int memUse;
  struct chunk *next;
};

struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }

  struct chunk *next = flist;
  struct chunk *prev = NULL;

  // finding a free block
  // searching flist & if found -> reuse & unlink from flist
  // else, get more space (new block) from kernel
  while (next != NULL){
      if (next -> size >= size){
          if (prev != NULL){
              prev->next = next->next;
          } else {
              flist = next->next;
          }
          // amount of memory used in chunk from flist that was allocated
          next->memUse = size;
          // returns pointer to the memory
          return (void*)(next + 1);
      } else {
          prev = next;
          next = next->next;
      }
  }
    
// if nothing in flist that fits memory allocated
// (getting more memory from system)

  // sbrk is allocating new memory
  void *memory = sbrk(size + sizeof(struct chunk));

  if (memory == (void *) -1) {
    return NULL;
  } else {
      // creates a chunk that's exact size as what is allocated
    struct chunk* cnk = (struct chunk*) memory;
    cnk->size = size;
    cnk->memUse = size;
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
    if (memory != NULL){
        struct chunk *cnk = (struct chunk*)((struct chunk*) memory - 1);
        // adding chunk to the beginning of the free list
        cnk -> next = flist;
        flist = cnk;
    }

    return;
}


void fragstats(void* buffers[], int len) {
    
    // (mostly for) calculating the internal
    int inUseChunks = 0;
    int internalUnused = 0;
    float internalUnusedAvg = 0;
    int internalUnusedSmall = -1;
    int internalUnusedLarge = -1;
    
    for(int i = 0; i < len; i++){
        if (buffers[i] != NULL){
            // the total bytes of memory used/allocated in buffers
            inUseChunks++;
            
            struct chunk *cnk = (struct chunk*)((struct chunk*) buffers[i] - 1);
            
            // getting unused by looking at how much memory in use in each chunk
            internalUnused += (cnk->size - cnk->memUse);
            
            // logic for getting smallest unused memory chunk
            if(internalUnusedSmall == -1){
                internalUnusedSmall = (cnk->size - cnk->memUse);
            } else {
                if (internalUnusedSmall > (cnk->size - cnk->memUse)){
                    internalUnusedSmall = (cnk->size - cnk->memUse);
                }
            }
            
            // logic for getting largest unused memory chunk
            if(internalUnusedLarge == -1){
                internalUnusedLarge = (cnk->size - cnk->memUse);
            } else {
                if (internalUnusedLarge < (cnk->size - cnk->memUse)){
                    internalUnusedLarge = (cnk->size - cnk->memUse);
                }
            }
        }
    }
    
    internalUnusedAvg = internalUnused/inUseChunks;
    
    // (mostly for) calculating the external
    int freeChunks = 0;

    int extUnused = 0;
    float extUnusedAvg = 0;
    int extUnusedSmall = -1;
    int extUnusedLarge = -1;

    struct chunk *next = flist;

    while (next != NULL){
        // number of free'd chunks in flist
        freeChunks++;
       
        // logic for amount of free space in each free'd chunk
        extUnused += (next->size - next->memUse);

        // smallest amount of free space
        if(extUnusedSmall == -1){
            extUnusedSmall = (next->size - next->memUse);
        } else {
            if (extUnusedSmall > (next->size - next->memUse)){
                extUnusedSmall = (next->size - next->memUse);
            }
        }

        // largest amount of free space
        if(extUnusedLarge == -1){
            extUnusedLarge = (next->size - next->memUse);
        } else {
            if (extUnusedLarge < (next->size - next->memUse)){
                extUnusedLarge = (next->size - next->memUse);
            }
        }

        next = next->next;

    }

    extUnusedAvg = extUnused/freeChunks;

    
    
    printf("Total blocks: %d Free: %d Used: %d \n", inUseChunks + freeChunks, freeChunks, inUseChunks);
    
    
    printf("Internal unused: total: %d average: %0.1f smallest: %d largest: %d \n", internalUnused, internalUnusedAvg, internalUnusedSmall, internalUnusedLarge);


    printf("Internal unused: total: %d average: %0.1f smallest: %d largest: %d \n", extUnused, extUnusedAvg, extUnusedSmall, extUnusedLarge);
    
    
}

