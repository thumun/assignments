#include <stdio.h>
#include <string.h>


int main() {
    char bitInput[32];

    printf("Enter 8 bits: ");
    scanf("%s", bitInput);

    char output = 0;

    for (int i = 0; i < strlen(bitInput); i++){
        // shifting by one so next iteration not overwriting
        output = output << 1;
        output = output | (bitInput[i]-0x30); // converting to numeric value (0 or 1) then OR'ing it

    }

    printf("Your character is: %c\n", output);
    return 0;
}
