#include <stdio.h>
#include <string.h>

struct cake {
  float cost;
  char flavor[16];
  struct cake* next;
};

void printNodes(struct cake* list){
    float costcheap = list->cost;
    char cake [16];

    struct cake* current = list;

    while(current != NULL){

        printf("\n cake: %s ($%0.02f)", current->flavor, current->cost);
        current = current->next;

    }

    struct cake* a = list;

    while(a != NULL){
        if (costcheap < a->cost){
            costcheap = a->cost;
            strcpy(cake, a->flavor);
            printf("test cost: %f, %s\n", costcheap, cake);
        }

        a = a->next;

    }
}

struct cake makeCake(const char* flavor, float cost) {
  struct cake newCake;
  strncpy(newCake.flavor, flavor, 16);
  newCake.cost = cost;
  newCake.next = NULL;
  return newCake;
}

// todo: implement cheapestCake

int main() {
  struct cake cake1 = makeCake("red velvet", 2.00);
  struct cake cake2 = makeCake("chocolate", 1.75);
  struct cake cake3 = makeCake("mocha", 3.50);
  // todo: define 4th cake
  struct cake cake4 = makeCake("rainbow sprinkle", 5.25);

  cake1.next = &cake2;
  cake2.next = &cake3;

  cake3.next = &cake4;
  // draw stack and heap here

    printNodes(&cake1);

  // todo: call cheapestCake
}
