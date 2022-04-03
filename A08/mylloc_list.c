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
    for(int i = 0; i < len; i++){
        if (buffers[i] != NULL){
            inUseChunks++;
        }
    }
    
    int freeChunks = 0;
    struct chunk *next = flist;

    while (next != NULL){
        freeChunks++;
        next = next->next;
    }
    
    
    
    printf("Total blocks: %d Free: %d Used: %d \n", inUseChunks + freeChunks, freeChunks, inUseChunks);
//    printf("Internal unused: total: 95635 average: 1648.0 smallest: 6 largest: 3805 \n");
//    printf("External unused: total: 235487 average: 2770.0 smallest: 151 largest: 3999 \n");
    
    
}

