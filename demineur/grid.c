#include "demineur.h"

void printGrid(char **grid) {
    int k = 'A';
    printf("  ");
    for (int l = 0; l < TAILLE; l++) {
        printf("%c ", k);
        k++;
    }
    k = 'A';
    printf("\n");
    printf("%c ", k);
    k++;
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            if (grid[j][i] == '*' || grid[j][i] == 'P') { // If the cell is a mine
                printf("\033[31m%c\033[0m ", grid[j][i]); // Print in red
            } else if (grid[j][i] >= '0' && grid[j][i] <= '9') { // If the cell is hidden
                printf("\033[32m%c\033[0m ", grid[j][i]); // Print in green
            } else {
                printf("\033[34m%c\033[0m ", grid[j][i]); // Print in blue
                
            }
        }
        printf("\n");
        if(j < TAILLE - 1) {
            printf("%c ", k);
            k++;
        }
    }
}

char **realGridInit(char **grid) {
    srand(time(NULL));
    for (int m = 0; m < MINES; m++) {
        int x = rand() % TAILLE;
        int y = rand() % TAILLE;
        grid[y][x] = '*';
    }
    return grid;
}

int countMines(char **grid, int x, int y) {
    int count = 0;

    // Tableau des déplacements possibles pour trouver les cases adjacentes
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < TAILLE && ny >= 0 && ny < TAILLE) {
            if (grid[ny][nx] == '*') {
                count++;
            }
        }
    }

    return count;
}

void realGridWithMines(char **grid) {
    for (int y = 0; y < TAILLE; y++) {
        for (int x = 0; x < TAILLE; x++) {
            if (grid[y][x] != '*') {
                int minesCount = countMines(grid, x, y);
                grid[y][x] = minesCount + '0';
            }
        }
    }
}