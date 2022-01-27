#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int AI_pick(){
    int random_variable = rand();
    return random_variable % 3;
}

void game(int rounds){
    char user_choice[100];
    char AI_choice[100];
    int user_score;
    int AI_score;

    // * = pointer to a string
    // is array size 3; each type is char * (string)
    const char * game_options[3] = {"rock", "paper", "scissors"};

//    char * a = "hi";
//    strcpy(a, "aa");
//    printf("%s", a);

    printf("Which do you choose? rock, paper, or scissors?\n");
    scanf("%s", user_choice);

    // using random num to get AI's choice
    AI_score = AI_pick();

    printf("AI chose %s\n", game_options[AI_score]);

    // can optimize the defeat??

    // make sure to incorporate while loop for rounds!!

    // testing
    printf("user choice test: %d\n", (strcmp(user_choice, "rock ") == 0));
    printf("ai choice test: %d\n", strcmp(AI_choice, "scissors") == 0);

    if (!((strcmp(user_choice, "rock") == 0) && (strcmp(AI_choice, "scissors") == 0))
        || !((strcmp(user_choice, "paper") == 0) && (strcmp(AI_choice, "rock") == 0))
            || !((strcmp(user_choice, "scissors") == 0) && (strcmp(AI_choice, "paper") == 0))) {

        printf("%s defeats %s\n", user_choice, AI_choice);
        user_score += 1;
    } else if (strcmp(user_choice, AI_choice) == 0){
        printf("It's a draw!\n");
    } else if (strcmp(user_choice, "rock") != 0
        || strcmp(user_choice, "paper") != 0
            || strcmp(user_choice, "scissors") != 0 ) {

        printf("You entered an invalid choice: %s\n", user_choice);
    } else {
        printf("%s defeats %s\n", AI_choice, user_choice);
        AI_score += 1;
    }

    // why isn't & used?
    printf("AI score: %d, Player score: %d\n", AI_score, user_score);
}

int main() {
  srand(time(0)); //??
  int rounds;

  printf("Welcome to Rock, Paper, Scissors!\n");
  printf("How many rounds do you want to play?\n");
  scanf("%d", &rounds);

  game(rounds);

  return 0;
}

