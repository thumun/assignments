#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fills output with inputNum number of inputStr
void fillOutput(char * inputStr, unsigned long inputNum, char * output) {

    for (unsigned long i = 0; i < inputNum; i++){
        for (int j = 0; j < strlen(inputStr); j++){
            output[j+(i*strlen(inputStr))] = inputStr[j];
        }
    }

    // adding null termination
    output[strlen(inputStr)*inputNum] = '\0';
}

int main() {
  char inputStr [32];
  unsigned long inputNum;

  char * output;

  printf("Enter a word: "); 
  scanf("%s", inputStr);

  printf("Enter a count: "); 
  scanf("%lu", &inputNum);

  // +1 for accounting for null termination
  output = (char *) malloc(strlen(inputStr)*inputNum + 1);

  // check if malloc is successful
  if (output == NULL){
    printf("\nCannot allocate new string. Exiting...");
    return 1;
  }

  fillOutput(inputStr, inputNum, output);

  printf("%s", output);

  // deallocating & freeing pointer
  free(output);
  output = NULL;

  return 0;
}
