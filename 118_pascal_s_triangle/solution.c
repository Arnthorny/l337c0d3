/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>


void gen_pascal_rows(int row_pos, int* row_arr, int *prev_row) {
    int last_val = 1, i = 1;
    // printf("Here\n");

    row_arr[0] = 1;
    if (row_pos > 1) {row_arr[row_pos - 1] = 1; row_pos--;}

    for (i = 1; i < row_pos; i++) {
        printf("%d\n", i);
        row_arr[i] = prev_row[i - 1] + prev_row[i];}
    return;
    
}

int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    
    int **pyramid_arr = malloc(sizeof(*pyramid_arr) * numRows);
    int *cols = malloc(sizeof(*cols) * numRows);

    int *tmp_row = NULL;

    for (int i = 0; i < numRows; i++)
    {
        pyramid_arr[i] = malloc(sizeof(int *) * (i + 1));
        cols[i] = i + 1;

        if(i == 0) gen_pascal_rows(i + 1, pyramid_arr[i], NULL);
        else gen_pascal_rows(i + 1, pyramid_arr[i], pyramid_arr[i - 1]);
    }

    // *returnSize = numRows;
    // *returnColumnSizes = cols;
    return pyramid_arr;
}

int main(void) {
    generate(5, NULL, NULL);
}