#include "demineur.h"



void printGrid(char **grid) {
    int k = 'A';
    printf("  ");
    for (int l = 0; l < TAILLE; l++) {
        printf("%c", k);
        k++;
    }
    k = 'A';
    printf("\n");
    printf("%c ", k);
    k++;
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            printf("%c", grid[j][i]);
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

    // Parcourir toutes les directions
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Vérifier si la case adjacente est à l'intérieur de la grille
        if (nx >= 0 && nx < TAILLE && ny >= 0 && ny < TAILLE) {
            // Si la case adjacente contient une mine, incrémenter le compteur
            if (grid[ny][nx] == '*') {
                count++;
            }
        }
    }

    return count;
}

// Fonction pour mettre à jour la grille avec le nombre de mines autour de chaque case
void realGridWithMines(char **grid) {
    // Parcourir chaque case de la grille
    for (int y = 0; y < TAILLE; y++) {
        for (int x = 0; x < TAILLE; x++) {
            // Si la case ne contient pas de mine, compter les mines autour
            if (grid[y][x] != '*') {
                // Compter les mines autour de la case actuelle
                int minesCount = countMines(grid, x, y);
                // Mettre à jour la case avec le nombre de mines trouvées
                grid[y][x] = minesCount + '0'; // Convertir le nombre en caractère
            }
        }
    }
}

// char **initGrid(void) {
//     char **grid = malloc(TAILLE * sizeof(char *));
//     for (int i = 0; i < TAILLE; i++) {
//         grid[i] = malloc(TAILLE * sizeof(char));
//     }
//     char **realGrid = malloc(TAILLE * sizeof(char *));
//     for (int i = 0; i < TAILLE; i++) {
//         realGrid[i] = malloc(TAILLE * sizeof(char));
//     }
//     char **playerGrid = malloc(TAILLE * sizeof(char *));
//     for (int i = 0; i < TAILLE; i++) {
//         playerGrid[i] = malloc(TAILLE * sizeof(char));
//     }

//     for (int j = 0; j < TAILLE; j++) {
//         for (int i = 0; i < TAILLE; i++) {
//             grid[j][i] = 'x';
//         }
//     }

//     // printGrid(grid);
//     // memcpy(playerGrid, grid, TAILLE * sizeof(char *));
//     // printf("\n\n");
//     // memcpy(realGrid, grid, TAILLE * sizeof(char *));
//     // realGridInit(realGrid);
//     // printGrid(realGrid);
//     // printf("\n\n");
//     // realGridWithMines(realGrid);
//     // printGrid(realGrid);

//     return(grid);

//     for (int i = 0; i < TAILLE; i++) {
//         free(grid[i]);
//     }
//     free(grid);
// }
