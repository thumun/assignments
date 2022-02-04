#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void checkGuess(char * blanks, char * str, char usrGuess){
    for (int i = 0; i < strlen(blanks); i++){
        if (usrGuess == str[i]){
            blanks[i] = str[i];
        }
    }
}

void blankSpaceGen(char * blanks, int size){
    for (int i = 0; i < size-1; i++){
        blanks[i] = '_';
    }
    blanks[size-1] = '\0';
}

void guess(char * str){
    printf("%s", str);
    // strlen doesn't account for null termination
    char * blanks = (char *) malloc(strlen(str) + 1);

    int counter = 0;

    int turnCount = 1;
    char usrGuess[10];

    blankSpaceGen(blanks, strlen(str)+1);

    while(strcmp(blanks, str) != 0){
        printf("\nTurn: %d\n\n", turnCount);

        printf("%s", blanks);

        printf("\nGuess a character: ");
        scanf("%s", usrGuess);

        printf("\n");

        checkGuess(blanks, str, usrGuess[0]);

        turnCount++;

        counter++;
    }

    printf("%s\n", blanks);
    printf("You won in %d turns!\n", turnCount);

    free(blanks);
    blanks = NULL;
}

void trimStr(char * str){
    for (int i = 0; i < strlen(str); i++){
        // \r = carriage return = causes extra char in strlen
        if (str[i] == '\n' || str[i] == '\r'){
            str[i] = '\0';
            return;
        }
    }
}

int main() {
    FILE *wordList = NULL;
    int totalWords;
    char str[32]; // max length of word

    srand(time(0));

    wordList = fopen("words.txt", "r");

    fscanf(wordList, "%d", &totalWords);

    int randNum = rand() % (totalWords-2);
    randNum++; // avoiding the number as first element

    int counter = 0;

    if (wordList == NULL) {
        perror("Error opening file"); // print error
        exit(1);
    }

    while (fgets(str, sizeof(str), wordList)) {
        counter++;
        if (counter == randNum){
            trimStr(str);
            break;
        }
    }

    fclose(wordList);
    wordList = NULL;

    printf("\nWelcome to Word Guess!\n");
    guess(str);


  return 0;
}
