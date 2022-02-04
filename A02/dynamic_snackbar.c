#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int quantity;
};

// set up for print statements in snack bar (showing options)
void printSnacks(struct snack* opts, int numSnacks){
    for (int i = 0; i < numSnacks; i++){
        printf("\n%d) %s \t\t cost: %0.02f \t quantity: %d", i, opts[i].name, opts[i].cost, opts[i].quantity);
    }
}

// adding to each snack struct's info
void createSnacks(struct snack* name){
    printf("\nEnter a name: ");
    scanf("%s", name->name);
    printf("\nEnter a cost: ");
    scanf("%f", &name->cost);
    printf("\nEnter a quantity: ");
    scanf("%d", &name->quantity);
}


int main() {
    int numSnacks;

    printf("Enter a number of snacks: ");
    scanf("%d", &numSnacks);

    // allocating space for each struct via an array of struct snack
    struct snack* opts = (struct snack*) malloc(sizeof(struct snack) * numSnacks);

    // seeing if malloc working
    if (opts == NULL){
        printf("\nmalloc failed. exiting...");
        exit(1);
    }

    // temp struct snack points to a struct in array
    // then via createSnacks, adds info to the struct it's pointing to
    // iteration changes which struct it's pointing to
    for (int i = 0; i < numSnacks; i++){
        struct snack* temp = &opts[i];

        createSnacks(temp);
    }

    printf("Welcome to Neha's Amazing Snack Bar!\n");
    printSnacks(opts, numSnacks);

    // deallocating & freeing
    free(opts);
    opts = NULL;

    return 0;
}
