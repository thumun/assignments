#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(){

    char phrase[100];

    printf("Please enter a phrase: ");
    fgets (phrase, 100, stdin);
    //scanf("%s", phrase);

    unsigned char thirdmask = 1;
    thirdmask = thirdmask << 2;

    unsigned char secmask = 1;
    secmask = secmask << 1;

    unsigned char thirdbit;
    unsigned char secbit;

    for (int i = 0; i < strlen(phrase); i++){
        //printf("char: 0x%x (%d) \n", phrase[i], phrase[i]);

        secbit = (phrase[i] & secmask);
        //printf("before secbit: %x \n", secbit);

        phrase[i] = phrase[i] & ~secmask;

        secbit = secbit << 1;
        //printf("after secbit: %x \n", secbit);

        thirdbit = (phrase[i] & thirdmask) >> 1;

        phrase[i] = phrase[i] & ~thirdmask;

        phrase[i] = phrase[i] | secbit;
        phrase[i] = phrase[i] | thirdbit;
    }

//    int origNum = atoi(argv[1]);
//
//    printf("Your original number: 0x%x (%d) \n", origNum, origNum);
//
//    unsigned int mask = ~(1 << atoi(argv[2]));
//
//    unsigned int newNum = origNum & mask;
//    newNum =  newNum | (atoi(argv[3]) << atoi(argv[2]));
//

    printf("scramble: %s", phrase);

    return 0;
}
