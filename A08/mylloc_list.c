#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
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
    return (void*) (cnk + 1);
  }
}

// I don't get this : (
// ptr is pointing to same as flist (?)
// flist updated to be pointer??
void free(void *memory) {
    if (memory != NULL){
        // going back one chunk
        struct chunk *cnk = (struct chunk*)((struct chunk*) memory - 1);
        cnk -> next = flist;
        flist = cnk;
    }

    return;
}

// figure out what goes here
void fragstats(void* buffers[], int len) {
}

