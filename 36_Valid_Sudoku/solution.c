#include <stdio.h>
#include <stdbool.h>

#define MAX_ROW 9
#define MAX_COL 9

/**
 * Checks whether a frequency array contains any repeated values.
 *
 * The frequency array is expected to use indices 1 through 9 to represent
 * the Sudoku digits '1' through '9'. Index 0 is ignored.
 *
 * @param freq_arr An array containing the frequency of each Sudoku digit.
 *
 * @return true  if no digit occurs more than once.
 * @return false if any digit occurs more than once.
 */
bool has_no_repetitions(int freq_arr[MAX_ROW + 1]){
    int i = 1;

    while (i < MAX_ROW + 1)
        if(freq_arr[i++] > 1)
            return false;

    return true;
}

/**
 * Checks whether a 3x3 Sudoku subgrid contains duplicate digits.
 *
 * Starting from the top-left cell of the specified 3x3 subgrid, the function
 * traverses all nine cells and counts the occurrences of each digit.
 * Empty cells ('.') are ignored.
 *
 * The traversal follows this pattern:
 *
 * (0,0) -> (0,1) -> (0,2)
 *                      |
 * (1,0) <- (1,1) <- (1,2)
 *   |
 * (2,0) -> (2,1) -> (2,2)
 *
 * @param board      The Sudoku board represented as char pointers.
 * @param start_row  The row index of the top-left cell of the 3x3 subgrid.
 * @param start_col  The column index of the top-left cell of the 3x3 subgrid.
 *
 * @return true  if the 3x3 subgrid contains no repeated digits.
 * @return false if a digit occurs more than once in the subgrid.
 */
bool check_3_x_3(char **board, int start_row, int start_col){
    int i, board_val = 0;
    int cur_row = start_row, cur_col = start_col;

    int traverse_mat[MAX_ROW - 1][2] = {
        {0,1},
        {0,1},
        {1,0},
        {0,-1},
        {0,-1},
        {1,0},
        {0,1},
        {0,1}
    };

    int square_val_freq[MAX_ROW + 1] = {0};

    board_val = board[cur_row][cur_col] != '.'
                   ? board[cur_row][cur_col] - '0'
                   : -1;

    if(board_val != -1)
        square_val_freq[board_val] += 1;

    for (i = 0; i < MAX_ROW - 1; i++)
    {
        /* Move to the next cell in the 3x3 subgrid. */
        cur_row += traverse_mat[i][0];
        cur_col += traverse_mat[i][1];

        /* Ignore empty cells and count valid digits. */
        board_val = board[cur_row][cur_col] != '.'
                       ? board[cur_row][cur_col] - '0'
                       : -1;

        if(board_val != -1)
            square_val_freq[board_val] += 1;
    }

    return has_no_repetitions(square_val_freq);
}

/**
 * Checks whether a Sudoku column contains duplicate digits.
 *
 * Starting at the specified row and column, the function traverses downward
 * through all nine rows while keeping the column fixed.
 * Empty cells ('.') are ignored.
 *
 * @param board      The Sudoku board represented as char pointers.
 * @param start_row  The row from which to begin checking.
 * @param start_col  The column to check.
 *
 * @return true  if the column contains no repeated digits.
 * @return false if a digit occurs more than once in the column.
 */
bool check_cols(char **board, int start_row, int start_col){
    int i, board_val = 0;
    int cur_row = start_row, cur_col = start_col;

    int square_val_freq[MAX_COL + 1] = {0};

    for (i = 0; i < MAX_COL; i++)
    {
        /* Ignore empty cells and count valid digits. */
        board_val = board[cur_row][cur_col] != '.'
                       ? board[cur_row][cur_col] - '0'
                       : -1;

        if(board_val != -1)
            square_val_freq[board_val] += 1;

        cur_row += 1;
    }

    return has_no_repetitions(square_val_freq);
}

/**
 * Checks whether a Sudoku row contains duplicate digits.
 *
 * Starting at the specified row and column, the function traverses across
 * all nine columns while keeping the row fixed.
 * Empty cells ('.') are ignored.
 *
 * @param board      The Sudoku board represented as char pointers.
 * @param start_row  The row to check.
 * @param start_col  The column from which to begin checking.
 *
 * @return true  if the row contains no repeated digits.
 * @return false if a digit occurs more than once in the row.
 */
bool check_rows(char **board, int start_row, int start_col){
    int i, board_val = 0;
    int cur_row = start_row, cur_col = start_col;

    int square_val_freq[MAX_ROW + 1] = {0};

    for (i = 0; i < MAX_ROW; i++)
    {
        /* Ignore empty cells and count valid digits. */
        board_val = board[cur_row][cur_col] != '.'
                       ? board[cur_row][cur_col] - '0'
                       : -1;

        if(board_val != -1)
            square_val_freq[board_val] += 1;

        cur_col += 1;
    }

    return has_no_repetitions(square_val_freq);
}

/**
 * Determines whether a 9x9 Sudoku board is valid.
 *
 * A valid Sudoku board must satisfy three conditions:
 *
 * 1. Every row contains no repeated digits.
 * 2. Every column contains no repeated digits.
 * 3. Every 3x3 subgrid contains no repeated digits.
 *
 * Empty cells, represented by '.', are ignored.
 *
 * Each iteration checks one row, one column, and one 3x3 subgrid.
 * The starting coordinates of the 3x3 subgrid are calculated using:
 *
 *     curr_3x3_row = (i / 3) * 3;
 *     curr_3x3_col = (i % 3) * 3;
 *
 * This produces the following starting positions:
 *
 *     (0,0) -> (0,3) -> (0,6)
 *     (3,0) -> (3,3) -> (3,6)
 *     (6,0) -> (6,3) -> (6,6)
 *
 * @param board        The Sudoku board represented as char pointers.
 * @param boardSize    The number of rows in the board. Expected to be 9.
 * @param boardColSize Pointer to the number of columns in each row.
 *                     Expected to be 9.
 *
 * @return true  if the Sudoku board is valid.
 * @return false if any row, column, or 3x3 subgrid contains a duplicate.
 */
bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    int i, curr_3x3_row = 0, curr_3x3_col = 0;

    for (i = 0; i < MAX_ROW; i++)
    {
        /* Determine the starting cell of the current 3x3 subgrid. */
        curr_3x3_row = (i / 3) * 3;
        curr_3x3_col = (i % 3) * 3;

        /* Check the current 3x3 subgrid. */
        if (!check_3_x_3(board, curr_3x3_row, curr_3x3_col))
            return false;

        /* Check the current row. */
        if (!check_rows(board, i, 0))
            return false;

        /* Check the current column. */
        if (!check_cols(board, 0, i))
            return false;
    }

    return true;
}
