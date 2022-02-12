//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name: Neha Thumu
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

    struct node * newItem = (struct node *) malloc(sizeof (struct node));
    newItem->sym = sym;
    newItem->linenum = line;
    newItem->colnum = col;
    newItem->next = top;

    top = newItem;

    return top;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {

    if(top == NULL){
        return top;
    } else if (top->next == NULL){
        free(top);
        top = NULL;
    } else {
        struct node* next = top->next;
        free(top);
        top = next;
    }

    return top;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {

    while(top != NULL){
        struct node* next = top->next;
        free(top);
        top = next;
    }

    top = NULL;
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {

    struct node* current = top;
    int counter = 0;

    while(current != NULL){
        printf("%d.) sym: %c, linenum: %d, colnum: %d \n",
               counter, current->sym, current->linenum, current->colnum);
        current = current->next;
        counter++;
    }
}

int main(int argc, char* argv[]) {
    FILE *file = NULL;
    char * fileName = NULL;
    char character;
    struct node* top = NULL;

    // input checker
    if (argc != 2){
        printf("usage:");
        for (int i = 0; i < argc; i++){
            printf(" %s", argv[i]);
        }
        return 1;
    }

    fileName = argv[1];

    // opens file
    file = fopen(fileName, "r");

    // file pointer test
    if (file == NULL) {
        printf("Cannot open file: %s", fileName); // print error
        return 1;
    }

    int lineCounter = 1;
    int colCount = 0;

    while ((character = fgetc(file)) != EOF){

        if (character == '\n'){
            colCount = 0;
            lineCounter+=1;
        }

        if (character == '{'){
            top = push(character, lineCounter, colCount, top);
        }

        if (character == '}'){
            if (top == NULL){
                printf("Unmatched brace on Line %d and Column %d\n", lineCounter, colCount);
            } else {
                printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
                       top->linenum, top->colnum, lineCounter, colCount);
            }
            top = pop(top);
        }

        //print(top);

        colCount++;
    }

    // printing unmatched braces: { (open facing)
    while (top != NULL){
        printf("Unmatched brace on Line %d and Column %d\n", top->linenum, top->colnum);
        struct node * next = top->next;

        free(top);

        top = next;
    }

    // I think linked list is already cleared but calling just in case
    clear(top);
    top = NULL;

    return 0;
}
