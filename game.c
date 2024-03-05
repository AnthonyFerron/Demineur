#include "demineur.h"


void initGame(void) {

    char **grid = malloc(TAILLE * sizeof(char *));
    for (int i = 0; i < TAILLE; i++) {
        grid[i] = malloc(TAILLE * sizeof(char));
    }
    char **realGrid = malloc(TAILLE * sizeof(char *));
    for (int i = 0; i < TAILLE; i++) {
        realGrid[i] = malloc(TAILLE * sizeof(char));
    }
    char **playerGrid = malloc(TAILLE * sizeof(char *));
    for (int i = 0; i < TAILLE; i++) {
        playerGrid[i] = malloc(TAILLE * sizeof(char));
    }

    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            grid[j][i] = 'x';
        }
    }

    memcpy(playerGrid, grid, TAILLE * sizeof(char *));
    memcpy(realGrid, grid, TAILLE * sizeof(char *));
    realGridInit(realGrid);
    realGridWithMines(realGrid);
    printGrid(grid);
    printGrid(playerGrid);

    for (int i = 0; i < TAILLE; i++) {
        free(grid[i]);
    }
    free(grid);
}

