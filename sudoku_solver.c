#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define N 9
#define EMPTY 0

// Global counter for performance analysis
long long recursive_calls = 0;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    printf("\n");
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            printf("------+-------+------\n");
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0) {
                printf("| ");
            }
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if number exists in current row
bool usedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

// Check if number exists in current column
bool usedInColumn(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

// Check if number exists in current 3x3 box
bool usedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
        }
    }
    return false;
}

// Check if it's safe to place number at given position
bool isSafe(int grid[N][N], int row, int col, int num) {
    return !usedInRow(grid, row, num) &&
           !usedInColumn(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

// Find empty cell in the grid
bool findEmptyLocation(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == EMPTY)
                return true;
        }
    }
    return false;
}

// Standard Backtracking Sudoku Solver
bool solveSudoku(int grid[N][N]) {
    int row, col;
    recursive_calls++;

    if (!findEmptyLocation(grid, &row, &col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = EMPTY;
        }
    }
    return false;
}

// Count possible values for MRV
int countPossibleValues(int grid[N][N], int row, int col) {
    if (grid[row][col] != EMPTY)
        return 10;

    int count = 0;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num))
            count++;
    }
    return count;
}

// Find empty cell with MRV heuristic
bool findEmptyLocationMRV(int grid[N][N], int *row, int *col) {
    int minCount = 10;
    bool found = false;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (grid[r][c] == EMPTY) {
                int count = countPossibleValues(grid, r, c);

                if (count < minCount) {
                    minCount = count;
                    *row = r;
                    *col = c;
                    found = true;
                }
            }
        }
    }
    return found;
}

// Optimized Sudoku Solver using MRV
bool solveSudokuOptimized(int grid[N][N]) {
    int row, col;
    recursive_calls++;

    if (!findEmptyLocationMRV(grid, &row, &col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudokuOptimized(grid))
                return true;

            grid[row][col] = EMPTY;
        }
    }
    return false;
}

// Validate the initial puzzle
bool isValidConfiguration(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] != EMPTY) {
                int num = grid[row][col];
                grid[row][col] = EMPTY;

                if (!isSafe(grid, row, col, num)) {
                    grid[row][col] = num;
                    return false;
                }
                grid[row][col] = num;
            }
        }
    }
    return true;
}

int main() {

    int grid1[N][N] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    int grid2[N][N] = {
        {0,0,0,0,0,0,6,8,0},
        {0,0,0,0,7,3,0,0,9},
        {3,0,9,0,0,0,0,4,5},
        {4,9,0,0,0,0,0,0,0},
        {8,0,3,0,5,0,9,0,2},
        {0,0,0,0,0,0,0,3,6},
        {9,6,0,0,0,0,3,0,8},
        {7,0,0,6,8,0,0,0,0},
        {0,2,8,0,0,0,0,0,0}
    };

    printf("\n===============================================\n");
    printf("SUDOKU SOLVER USING BACKTRACKING ALGORITHM\n");
    printf("===============================================\n");

    printf("\n--- EXAMPLE 1: EASY PUZZLE ---\n");
    printGrid(grid1);

    if (!isValidConfiguration(grid1)) {
        printf("Invalid initial configuration!\n");
        return 1;
    }

    clock_t start = clock();
    recursive_calls = 0;

    if (solveSudoku(grid1)) {
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Solution Found!");
        printGrid(grid1);
        printf("Execution Time: %.6f seconds\n", time_taken);
        printf("Recursive Calls: %lld\n", recursive_calls);
    }

    printf("\n--- EXAMPLE 2: HARD PUZZLE (Standard Backtracking) ---\n");
    printGrid(grid2);

    int grid2_copy[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid2_copy[i][j] = grid2[i][j];

    start = clock();
    recursive_calls = 0;

    if (solveSudoku(grid2)) {
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Solution Found!");
        printGrid(grid2);
        printf("Execution Time: %.6f seconds\n", time_taken);
        printf("Recursive Calls: %lld\n", recursive_calls);
    }

    printf("\n--- EXAMPLE 2: HARD PUZZLE (Optimized with MRV) ---\n");

    start = clock();
    recursive_calls = 0;

    if (solveSudokuOptimized(grid2_copy)) {
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Solution Found!");
        printGrid(grid2_copy);
        printf("Execution Time: %.6f seconds\n", time_taken);
        printf("Recursive Calls: %lld\n", recursive_calls);
    }

    printf("\n===============================================\n");
    printf("Performance Comparison Summary:\n");
    printf("Optimized algorithm significantly reduces recursive calls.\n");
    printf("===============================================\n");

    return 0;
}

