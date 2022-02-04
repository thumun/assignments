#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// if guess is right then updates the blanks to show letter in correct spot in word
void checkGuess(char * blanks, char * str, char usrGuess){
    for (int i = 0; i < strlen(blanks); i++){
        if (usrGuess == str[i]){
            blanks[i] = str[i];
        }
    }
}

// initializing blanks array based on length of str
// filling with same number of blanks as str
void blankSpaceGen(char * blanks, int size){
    for (int i = 0; i < size-1; i++){
        blanks[i] = '_';
    }
    blanks[size-1] = '\0';
}

void guess(char * str){
    //printf("%s", str); // testing by cheating :)

    // allocating space for blanks array
    // strlen doesn't account for null termination so +1
    char * blanks = (char *) malloc(strlen(str) + 1);

    if (blanks == NULL){
        printf("\nmalloc failed. exiting...");
        exit(1);
    }

    int turnCount = 1;
    char usrGuess[10];

    // generating blank spaces in arr based on str length
    blankSpaceGen(blanks, strlen(str)+1);

    // continues until guess (blanks) same as random word (str)
    while(strcmp(blanks, str) != 0){
        printf("\nTurn: %d\n\n", turnCount);

        printf("%s", blanks);

        printf("\nGuess a character: ");
        scanf("%s", usrGuess);

        printf("\n");

        // logic for guessing
        checkGuess(blanks, str, usrGuess[0]);

        turnCount++;
    }

    // word & win statement
    printf("%s\n", blanks);
    printf("You won in %d turns!\n", turnCount);

    // deallocating & freeing pointer
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
