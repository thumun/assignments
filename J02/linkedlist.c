#include <stdio.h>
#include <string.h>

struct cake {
  float cost;
  char flavor[16];
  struct cake* next;
};

void printNodes(struct cake* list){
    struct cake* current = list;

    while(current != NULL){

        printf("\ncake: %s ($%0.02f)", current->flavor, current->cost);
        current = current->next;

    }
}

struct cake * findCheapest(struct cake* list){
    struct cake* current = list;
    struct cake* next = current->next;
    struct cake* cheapest;

    float cost = list->cost;

    //char * cakeName = NULL;

    //float * prices = (float *)malloc(sizeOf(float)*15);

    while(next!=NULL){
        if (cost > current->cost){
            cheapest = current;
            cost = current->cost;
            //strcpy(cakeName, current->flavor);
        }

        current = next;
        next = next->next;
    }

    return cheapest;
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

    printf("\n");

    //char cakeName[32];
    //strcpy(cakeName, findCheapest(&cake1));

    struct cake cheapest = *findCheapest(&cake1);

    printf("cheapest cake is: %s", cheapest.flavor);
}
