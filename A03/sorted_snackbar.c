//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name: Neha Thumu
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};

// set up for print statements in snack bar (showing options)
void printSnacks(struct snack* snacks){

    int counter = 0;
    struct snack* current = snacks;

    while(current != NULL){
        printf("\n%d) %s \t\t cost: $%0.02f \t quantity: %d", counter, current->name, current->cost, current->quantity);
        counter++;
        current = current->next;
    }
}


// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, 
  const char* name, int quantity, float cost) {

    struct snack* temp = (struct snack*) malloc(sizeof(struct snack));
    strcpy(temp->name, name);
    temp->quantity = quantity;
    temp->cost = cost;
    temp->next = NULL;

    struct snack* current = NULL;
    struct snack* next = NULL;

    if (snacks == NULL) { // nothing in lst so new item is head
        snacks = temp;

    } else if (strcmp(temp->name, snacks->name) <= 0){ // new item = head
        temp->next = snacks;
        snacks = temp;

    } else {
        current = snacks;
        next = current->next;

        while(next != NULL){
            // checking temp before current name-wise
            if (strcmp(temp->name, next->name) <= 0){
                current->next = temp;
                temp->next = next;
                break;
            } else {
                current = current->next;
                next = next->next;
            }
        }

        if (current->next == NULL){
            current->next = temp;
        }
    }

    // return full linked list (to save it somewhere)
  return snacks;
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {

    while(snacks != NULL){
        struct snack* next = snacks->next;
        free(snacks);
        snacks = next;
    }

    snacks = NULL;
}

int main() {
    int numSnacks;
    struct snack* list = NULL;

    char name [32];
    int quantity;
    float cost;

    printf("Enter a number of snacks: ");
    scanf("%d", &numSnacks);

    for (int i = 0; i < numSnacks; i++){

        printf("\nEnter a name: ");
        scanf("%s", name);
        printf("\nEnter a cost: ");
        scanf("%f", &cost);
        printf("\nEnter a quantity: ");
        scanf("%d", &quantity);

        list = insert_sorted(list, name, quantity, cost);
    }

    printf("\nWelcome to Neha's Amazing Snack Bar!\n");
    printSnacks(list);

    clear(list);
    list = NULL;

    return 0;
}

