#include "puissance4.h"

void printGrid(char **grid) {
    printf("  ");
    for (int i = 0; i < COLS; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    for (int j = 0; j < ROWS; j++) {
        printf("  ");
        for (int i = 0; i < COLS; i++) {
            if (grid[j][i] == 'O') {
                printf("\033[0;31m%c \033[0m", grid[j][i]); // Rouge pour 'O'
            } else if (grid[j][i] == '0') {
                printf("\033[0;32m%c \033[0m", grid[j][i]); // Vert pour '0'
            } else {
                printf("%c ", grid[j][i]);
            }
        }
        printf("\n");
    }
    printf("\n");
    return;
}

