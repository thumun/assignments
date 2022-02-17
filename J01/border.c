#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void makeBorder(char * userInp, char symbol){
    int lenStr = strlen(userInp);
    lenStr+= 4;

    for (int i = 0; i < lenStr; i++){
        printf("%c", symbol);
    }
    printf("\n");

    printf("%c %s %c\n", symbol, userInp, symbol);

    for (int i = 0; i < lenStr; i++){
        printf("%c", symbol);
    }
    printf("\n");
}


int main(){
    char userInp [50];
    char symbol;

    printf("Please enter a word: ");
    scanf("%s", userInp);

    printf("Please enter a symbol: ");
    scanf(" %c", &symbol);

    makeBorder(userInp, symbol);

    return 0;
}