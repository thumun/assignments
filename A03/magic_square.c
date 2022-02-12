//---------------------------------------------------------------------
// magic_square.c
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name: Neha Thumu
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// calculating sum columns-wise
bool calcColArr(int num, int ** magicSqu, int * colSum){
    int * calcArr;
    bool comparison = true;

    calcArr = (int *) malloc(sizeof(int)*num);

    //fill with 0's
    memset(calcArr, 0, sizeof(int)*num);

    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            calcArr[i] += magicSqu[j][i];
        }
    }

    for (int i = 1; i < num; i++){
        if (calcArr[i] != calcArr[0]){
            comparison = false;
            break;
        }
    }

    // gets the sum for columns
    *colSum = calcArr[0];

    free(calcArr);
    calcArr = NULL;

    return comparison;
}

// calculating sum rows-wise
bool calcRowArr(int num, int ** magicSqu, int * rowSum){
    int * calcArr;
    bool comparison = true;

    calcArr = (int *) malloc(sizeof(int)*num);

    //fill with 0's
    memset(calcArr, 0, sizeof(int)*num);

    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            calcArr[i] += magicSqu[i][j];
        }
    }

    comparison = calcArr[0];

    for (int i = 1; i < num; i++){
        if (calcArr[i] != calcArr[0]){
            comparison = false;
            break;
        }
    }

    // gets sum row-wise
    *rowSum = calcArr[0];

    free(calcArr);
    calcArr = NULL;

    return comparison;
}

// calcs sum for diagonals
bool calculateDiag(int num, int ** magicSqu, int * diagSum){
    int * calcArr;
    bool comparison = false;
    int counter = 0; // counter for getting nums to compare diag sums

    calcArr = (int *) malloc(sizeof(int)*num);

    //fill with 0's
    memset(calcArr, 0, sizeof(int)*num);

    // left to right diag
    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            if (i == j){
                calcArr[counter] += magicSqu[i][j];
            }
        }
    }

    counter+=1;

    // right to left diag
    int rowIndx = 0;
    for (int j = num-1; j >= 0; j--){
        calcArr[counter] += magicSqu[rowIndx][j];
        rowIndx++;
    }

    if (calcArr[0] == calcArr[1]){
        comparison = true;
    }

    *diagSum = calcArr[0];

    free(calcArr);
    calcArr = NULL;

    return comparison;
}

void isMagic(int num, int ** magicSqu){
    int rowSum = 0;
    int colSum = 0;
    int diagSum = 0;

    //calculate row, column, and diagonals

    bool row = calcRowArr(num, magicSqu, &rowSum);
    bool col = calcColArr(num, magicSqu, &colSum);
    bool diag = calculateDiag(num, magicSqu, &diagSum);

    // seeing if sums same among individual rows/cols/diags & sums same when compared
    if ((row == true && col == true && diag == true) &&
            (rowSum == colSum && rowSum == diagSum)){

        printf("\nM is a magic square (magic constant = %d)", rowSum);

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

    isMagic(rows, magicSqu);

    free(magicSqu);
    magicSqu = NULL;

    return 0;
}

