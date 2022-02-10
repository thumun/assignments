#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void makeBorder(char * userInp, char * symbol){
    int lenStr = strlen(userInp);
    lenStr+= 4;

    for (int i = 0; i < lenStr; i++){
        printf("%s", symbol);
    }
    printf("\n");

    printf("%s %s %s\n", symbol, userInp, symbol);

    for (int i = 0; i < lenStr; i++){
        printf("%s", symbol);
    }
    printf("\n");
}

int main(){
    char userInp [50];
    char symbol [32];

    printf("Please enter a word: ");
    scanf("%s", userInp);

    printf("Please enter a symbol: ");
    scanf("%s", symbol);

    makeBorder(userInp, symbol);

    return 0;
}