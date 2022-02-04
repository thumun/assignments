#include <stdio.h>
#include <stdlib.h>

// prints the inputStr inputNum times
void printUsrStr(char* inputStr, int inputNum){ 
  for (int i = 0; i < inputNum; i++){
    printf("%s", inputStr); 
  }    
}

int main() {
  char* inputStr = NULL; 
  int inputNum;

  // allocating space for user input
  inputStr = (char *) malloc(32);

  // check if malloc is successful
  if (inputStr == NULL){
    printf("\nCannot allocate new string. Exiting...");
    exit(1);
  }

  printf("Enter a word: "); 
  scanf("%s", inputStr);

  printf("Enter a count: "); 
  scanf("%d", &inputNum);  

  printUsrStr(inputStr, inputNum); 

  // deallocating & freeing pointer
  free(inputStr);
  inputStr = NULL;

  return 0;
}
