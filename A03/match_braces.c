//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name:
//
#include <stdio.h>
#include <stdlib.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  return NULL;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  return NULL;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {

}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {

//    char sym;
//    int linenum;
//    int colnum;
//    struct node* next;

//    struct node* current = top;
//
//    while(current != NULL){
//        printf("\n%d) %s \t\t cost: %0.02f \t quantity: %d", counter, current->name, current->cost, current->quantity);
//        counter++;
//        current = current->next;
//    }
}

int main(int argc, char* argv[]) {
    FILE *file = NULL;
    char * fileName;
    char character;

//    for (int i = 0; i < argc; i++){
//        printf("param %d: %s\n", i, argv[i]);
//    }

    fileName = argv[1];

    // opens file
    file = fopen(fileName, "r");

    // pointer test
    if (file == NULL) {
        printf("Cannot open file: %s", fileName); // print error
        return 1;
    }


    while ((character = fgetc(file)) != EOF){
        printf("%c", character);

        if (character == '\n'){
            printf("\n");
        }
    }

    return 0;
}
