#include <stdio.h>
#include <string.h>

// struct contains necessary info about snacks
struct snack {
    char name[100];
    float cost;
    int quantity;
};

// diff. outcomes when buying a snack
void buy_snack(struct snack item, float money){
    if (item.quantity == 0){
        printf("Sorry, %s is out of stock!", item.name);
    } else if (item.cost > money){
        printf("Sorry, you do not have enough money to purchase %s", item.name);
    } else {
        printf("Thank you for purchasing %s!\n", item.name);
        printf("Your current balance is: $%0.3f", money - item.cost);
    }
}

int main() {
    int option;
    int money;

    struct snack gummy, choco, gum;

    strcpy(gummy.name, "Gummy Worms");
    gummy.cost = 3.25;
    gummy.quantity = 10;

    strcpy(choco.name, "Chocolate");
    choco.cost = 5.75;
    choco.quantity = 0;

    strcpy(gum.name, "Bubble gum");
    gum.cost = 0.75;
    gum.quantity = 3;

    struct snack options[3];

    options[0] = gummy;
    options[1] = choco;
    options[2] = gum;

    printf("Welcome to Neha's Fantastic Snacks.\n\n");
    printf("How much money do you have? ");

    scanf("%d", &money);

    printf("\n");

    printf("0) %s \t\t cost: $%0.2f \t quantity: %d\n", gummy.name, gummy.cost, gummy.quantity);
    printf("1) %s \t\t cost: $%0.2f \t quantity: %d\n", choco.name, choco.cost, choco.quantity);
    printf("2) %s \t\t cost: $%0.2f \t quantity: %d\n", gum.name, gum.cost, gum.quantity);

    printf("\nWhat snack would you like to buy? [0, 1, 2] ");
    scanf("%d", &option);

    if (option == 0){
        buy_snack(options[0], money);
    } else if (option == 1){
        buy_snack(options[1], money);
    } else if (option == 2){
        buy_snack(options[2], money);
    } else {
        printf("Snack not available");
    }

    return 0;
}
