#include <stdio.h>
#include <stdlib.h>


void printUsrStr(char* inputStr, int inputNum){ 
  for (int i = 0; i < inputNum; i++){
    printf("%s", inputStr); 
  }    
}

int main() {

  char* inputStr = NULL; 
  int inputNum;

  inputStr = (char *) malloc(32);

  // check if malloc is successful

  printf("Enter a word: "); 
  scanf("%s", inputStr);

  printf("Enter a count: "); 
  scanf("%d", &inputNum);  

  printUsrStr(inputStr, inputNum); 
  
  free(inputStr);
  inputStr = NULL;

  return 0;
}
