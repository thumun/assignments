#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// returns 1 if user or AI wins, 0 if it's a draw or a loss
// also sets message depending on rps choice and outcome
int pickWinner(const char * first, const char * second, char * msg){
    if (strcmp(first, second) == 0){
        strcpy(msg, "It's a draw!\n");
        return 0;
    } else {
        if (((strcmp(second, "rock") == 0) && (strcmp(first, "scissors") == 0))){
            strcpy(msg, "rock bashes scissors\n");
            return 1;
        } else if (((strcmp(second, "paper") == 0) && (strcmp(first, "rock") == 0))){
            strcpy(msg, "paper covers rock\n");
            return 1;
        } else if (((strcmp(second, "scissors") == 0) && (strcmp(first, "paper") == 0))){
            strcpy(msg, "scissors cuts paper\n");
            return 1;
        }

        return 0;
    }

}

// AI choice for rps game
int AIPick(){
    return rand() % 3;
}

void game(int rounds){
    char userChoice[100];
    const char * AIChoice;
    int userScore = 0;
    int AIScore = 0;
    char msg[100];

    // array of strings for game options
    const char * gameOptions[3] = {"rock", "paper", "scissors"};

    while (rounds != 0) {

        printf("\nWhich do you choose? rock, paper, or scissors? ");
        scanf("%s", userChoice);

        // quit condition
        if (strcmp(userChoice, "quit") == 0){
            printf("Quitting the game...");
            return;
        }

        AIChoice = gameOptions[AIPick()];

        printf("AI chose %s\n", AIChoice);

        // invalid choice condition
        if (strcmp(userChoice, "rock") != 0
                   && strcmp(userChoice, "paper") != 0
                   && strcmp(userChoice, "scissors") != 0) {

            printf("You entered an invalid choice: %s\n", userChoice);
            //printf("%lu", strlen(userChoice));
        } else {
            // adding to the AI or user score depending on who wins rps
            AIScore += pickWinner(userChoice, AIChoice, msg);
            userScore += pickWinner(AIChoice, userChoice, msg);

            printf("%s", msg);
        }

        printf("AI score: %d, Player score: %d\n", AIScore, userScore);

        rounds -= 1;

    }

    // declares who wins at end of rounds
    if (userScore > AIScore){
        printf("Player wins!");
    } else if (userScore == AIScore){
        printf("It's a draw!");
    } else{
        printf("AI wins :(");
    }
}

int main() {
  srand(time(0));
  int rounds;

  printf("Welcome to Rock, Paper, Scissors!\n");
  printf("How many rounds do you want to play? ");
  scanf("%d", &rounds);

  // printf("you have chosen %d rounds", rounds);

  game(rounds);

  return 0;
}

