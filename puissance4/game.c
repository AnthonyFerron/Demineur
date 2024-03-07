#include "puissance4.h"

void initGame(void) {
    //init grid
    char **grid = malloc(ROWS * sizeof(char *));
    for (int i = 0; i < ROWS; i++) {
        grid[i] = malloc(COLS * sizeof(char));
    }
    // fill grid with 'x'
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = '0';
        }
    }
    printGrid(grid);
    return;
}