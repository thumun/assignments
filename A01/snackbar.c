#include <stdio.h>
#include <string.h> 

int main() {
  int money;
  int option;

  struct snack {
	char name[100]; 
	float cost; 
	int quantity; 
  }; 

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
  //options = [gummy, choco, gum]; 

  printf("Welcome to Neha's Fantastic Snacks.\n\n");
  printf("How much money do you have?\n\n"); 

  scanf("%d", &money);

  printf("0) %s \t\t cost: $%0.2f \t quantity: %d\n", gummy.name, gummy.cost, gummy.quantity);
  printf("1) %s \t\t cost: $%f \t quantity: %d\n", choco.name, choco.cost, choco.quantity); 
  printf("2) %s \t\t cost: $%f \t quantity: %d\n", gum.name, gum.cost, gum.quantity); 

  printf("\nWhat snack would you like to buy? [0, 1, 2]");
  scanf("%d", &option);

  // if good: say bought item 
  
  // check if have enough money 
  // check if have quantity  

  return 0;
}
