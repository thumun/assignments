#include <stdio.h> 
#include <string.h> 

char* createPassword(char word[], int capacity);

int main() {
  char word[100]; 
	
  printf("Please submit a word for your new password: "); 
  scanf("%s", word);

  createPassword(word, 100); 
  printf("Your bad password is %s", word); 
  return 0;

}

char * createPassword(char word[], int capacity){
  for (int i = 0; i < capacity; i++){ 
	  if(word[i] == 'e'){ 
		  word[i] = '3'; 
	  } else if (word[i] == 'l'){
		  word[i] = '1'; 
	  } else if (word[i] == 'a'){
		  word[i] = '@'; 
	  } 
  } 
  return word; 
}
