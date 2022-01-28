#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//void pick_winner(char * user_choice, int AIPick, const char * game_options[]){
//    int user;
//    int winner;
//
//    if (strcmp(user_choice, game_options[0]) == 0){
//        user = 0;
//    } else if (strcmp(user_choice, game_options[1]) == 0) {
//        user = 1;
//    } else if (strcmp(user_choice, game_options[2]) == 0) {
//        user = 2;
//    }
//
//    if (AIPick > user){
//
//
//    } else if (AIPick == user){
//
//
//    } else {
//
//    }
//
//    printf("%s bashes %s\n", user_choice, AI_choice);
//
//}

int AI_pick(){
    int random_variable = rand();
    return random_variable % 3;
}

void game(int rounds){
    char user_choice[100];
    const char * AI_choice;
    int AIPick;
    int user_score = 0;
    int AI_score = 0;
    int winner;

    // * = pointer to a string
    // is array size 3; each type is char * (string)
    const char * game_options[3] = {"rock", "paper", "scissors"};

    while (rounds != 0) {

        printf("Which do you choose? rock, paper, or scissors? ");
        scanf("%s", user_choice);

        // using random num to get AI's choice
        AIPick = AI_pick();
        AI_choice = game_options[AIPick];

        printf("AI chose %s\n", AI_choice);

        //winner = pick_winner(user_choice, AI_score, game_options);

        if (((strcmp(user_choice, "rock") == 0) && (strcmp(AI_choice, "scissors") == 0))){
            printf("%s bashes %s\n", user_choice, AI_choice);
            user_score += 1;
        } else if (((strcmp(user_choice, "paper") == 0) && (strcmp(AI_choice, "rock") == 0))){
            printf("%s covers %s\n", user_choice, AI_choice);
            user_score += 1;
        }
        else if (((strcmp(user_choice, "scissors") == 0) && (strcmp(AI_choice, "paper") == 0))){
            printf("%s cuts %s\n", user_choice, AI_choice);
            user_score += 1;
        } else if (strcmp(user_choice, AI_choice) == 0) {
            printf("It's a draw!\n");
        } else if (strcmp(user_choice, "rock") != 0
                   && strcmp(user_choice, "paper") != 0
                   && strcmp(user_choice, "scissors") != 0) {

            printf("You entered an invalid choice: %s\n", user_choice);
            printf("%lu", strlen(user_choice));
        } else {
            if (((strcmp(user_choice, "rock") == 0) && (strcmp(AI_choice, "scissors") == 0))){
                printf("%s bashes %s\n", AI_choice, user_choice);
            } else if (((strcmp(user_choice, "paper") == 0) && (strcmp(AI_choice, "rock") == 0))){
                printf("%s covers %s\n", AI_choice, user_choice);
            }
            else if (((strcmp(user_choice, "scissors") == 0) && (strcmp(AI_choice, "paper") == 0))){
                printf("%s cuts %s\n", AI_choice, user_choice);
            }

            AI_score += 1;
        }

        printf("AI score: %d, Player score: %d\n", AI_score, user_score);

        rounds -= 1;
    }
}

int main() {
  srand(time(0));
  int rounds;

  printf("Welcome to Rock, Paper, Scissors!\n");
  printf("How many rounds do you want to play?\n");
  scanf("%d", &rounds);

  game(rounds);

  return 0;
}

