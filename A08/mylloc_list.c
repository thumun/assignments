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
          next->memUse = size;
          return (void*)(next + 1);
      } else {
          prev = next;
          next = next->next;
      }
  }

  // sbrk is allocating new memory
  void *memory = sbrk(size + sizeof(struct chunk));

  if (memory == (void *) -1) {
    return NULL;
  } else {
    struct chunk* cnk = (struct chunk*) memory;
    cnk->size = size;
    cnk->memUse = size;
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
    if (memory != NULL){
        // going back one chunk
        struct chunk *cnk = (struct chunk*)((struct chunk*) memory - 1);
        cnk -> next = flist;
        flist = cnk;
    }

    return;
}


void fragstats(void* buffers[], int len) {
    
    int inUseChunks = 0;
    int internalUnused = 0;
    float internalUnusedAvg = 0;
    int internalUnusedSmall = -1;
    int internalUnusedLarge = -1;
    
    for(int i = 0; i < len; i++){
        if (buffers[i] != NULL){
            inUseChunks++;
            
            struct chunk *cnk = (struct chunk*)((struct chunk*) buffers[i] - 1);
            
            internalUnused += (cnk->size - cnk->memUse);
            
            if(internalUnusedSmall == -1){
                internalUnusedSmall = (cnk->size - cnk->memUse);
            } else {
                if (internalUnusedSmall > (cnk->size - cnk->memUse)){
                    internalUnusedSmall = (cnk->size - cnk->memUse);
                }
            }
            
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
    
    int freeChunks = 0;
    
    int extUnused = 0;
    float extUnusedAvg = 0;
    int extUnusedSmall = -1;
    int extUnusedLarge = -1;
    
    struct chunk *next = flist;

    while (next != NULL){
        freeChunks++;
        next = next->next;
        
        extUnused += (next->size - next->memUse);
        
        if(extUnusedSmall == -1){
            extUnusedSmall = (next->size - next->memUse);
        } else {
            if (extUnusedSmall > (next->size - next->memUse)){
                extUnusedSmall = (next->size - next->memUse);
            }
        }
        
        if(extUnusedLarge == -1){
            extUnusedLarge = (next->size - next->memUse);
        } else {
            if (extUnusedLarge < (next->size - next->memUse)){
                extUnusedLarge = (next->size - next->memUse);
            }
        }
        
        extUnusedAvg = extUnused/freeChunks;
        
    }
    
    
    
    printf("Total blocks: %d Free: %d Used: %d \n", inUseChunks + freeChunks, size, inUseChunks);
    
    
    printf("Internal unused: total: %d average: %0.1f smallest: %d largest: %d \n", internalUnused, internalUnusedAvg, internalUnusedSmall, internalUnusedLarge);
    
    
    printf("Internal unused: total: %d average: %0.1f smallest: %d largest: %d \n", extUnused, extUnusedAvg, extUnusedSmall, extUnusedLarge);
    
    
}

