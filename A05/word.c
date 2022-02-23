#include <stdio.h>
#include <string.h>

void convertToInt(char * usrInput, unsigned int * outputVal){
    unsigned int temp;

    for (int i = strlen(usrInput)-1; i >= 0; i--){

        temp = (unsigned int)(usrInput[i] << (strlen(usrInput)-1 - i)*8);

        printf("Debug: %c = 0x%08X \n", usrInput[i], temp);

        *outputVal = *outputVal | temp;
    }
}

int main() {
    unsigned int outputVal = 0;

    char usrInput[5]; // gotta add null termination?

    printf("Enter 4 characters: ");
    scanf("%s", usrInput);

    convertToInt(usrInput, &outputVal);

    printf("Your number is: %d (0x%08X)", outputVal, outputVal);

    return 0;
}
