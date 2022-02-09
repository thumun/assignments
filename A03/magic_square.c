//---------------------------------------------------------------------
// magic_square.c
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name: Neha Thumu
//

#include <stdio.h>
#include <stdlib.h>

int calculateArr(int num, int ** magicSqu){
    int * calcArr;
    int comparison;

    calcArr = (int *) malloc(sizeof(int)*num);

    // should I fill rowsArr with 0's?

    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            calcArr[i] += magicSqu[i][j];
        }
    }

    comparison = calcArr[0];

    for (int i = 1; i < num; i++){
        if (calcArr[i] != comparison){
            comparison = 0;
        }
    }

    return comparison;
}

int calculateDiag(int num, int ** magicSqu){
    int * calcArr;
    int comparison;
    int counter = 0;

    calcArr = (int *) malloc(sizeof(int)*num);

    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            if (i == j){
                calcArr[counter] += magicSqu[i][j];
            }
        }
    }

    counter+=1;

    int rowIndx = 0;
    for (int j = num-1; j >= 0; j--){
        calcArr[counter] += magicSqu[rowIndx][j];
        rowIndx++;
    }

    if (calcArr[0] == calcArr[1]){
        comparison = calcArr[0];
    }

    return comparison;
}

void isMagic(int num, int ** magicSqu){

    //calculate row, column, and diagonals

    int row = calculateArr(num, magicSqu);
    int col = calculateArr(num, magicSqu);
    int diag = calculateDiag(num, magicSqu);

    // check all outputs same
    if (row == col && row == diag) {
        printf("\nM is a magic square (magic constant = %d)", row);
    } else {
        printf("\nM is NOT a magic square!");
    }
}

int main() {
    int rows;
    int cols;
    int num;
    int ** magicSqu;

    scanf("%d %d", &rows, &cols);
    printf("rows: %d, cols: %d", rows, cols);

    // malloc array
    magicSqu = (int**) malloc(sizeof(int*)*rows);
    for(int row = 0; row < rows; row++) {
        magicSqu[row] = (int*) malloc(sizeof(int)* cols);
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            scanf("%d", &num);
            magicSqu[i][j] = num;
        }
    }

    // printing out matrix
    for (int i = 0; i < rows; i++){
        printf("\n");
        for (int j = 0; j < cols; j++){
            printf("%d ", magicSqu[i][j]);
            // initialize using ex
        }
    }

    isMagic(rows, magicSqu);

    return 0;
}

