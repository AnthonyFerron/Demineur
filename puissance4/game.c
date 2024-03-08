#include "puissance4.h"
int logicGame(char **grid, char *redName, char *greenName, int turn);

char *upperName(char *name) {
    char *p = name;
    if (p[0] <= 'z' && p[0] >= 'a') {
        p[0] -= 32;
    }
    return p;
}

void initGame(void) {
    char *redName;
    char *greenName;
    char redtemp[50];
    char greentemp[50];
    //init grid
    char **grid = malloc(ROWS * sizeof(char *));
    for (int i = 0; i < ROWS; i++) {
        grid[i] = malloc(COLS * sizeof(char));
    }
    // fill grid with 'x'
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 'x';
        }
    }
    printGrid(grid);
    printf("Joueur 1, entrez votre nom : ");
    scanf("%s", redtemp);
    printf("Joueur 2, entrez votre nom : ");
    scanf("%s", greentemp);
    greenName = upperName(greentemp);
    redName = upperName(redtemp);
    printf("Bienvenue %s et %s !\n", redName, greenName);
    printf("%s joue avec des pions \033[0;31mO\033[0m (rouges)\n", redName);
    printf("%s joue avec des pions \033[0;32m0\033[0m (verts)\n", greenName);
    printf("Bonne chance !\n\n");
    printf("Appuyez sur entrer pour continuer...\n");
    getchar();
    getchar();
    int turn = 0;
    clearOutput();
    logicGame(grid, redName, greenName, turn);
    return;
}

int logicGame(char **grid, char *redName, char *greenName, int turn) {
    int win = 0;
    char choice;
    int nbCoupRed = 0;
    int nbCoupGreen = 0;
    int i = 0;
    int col = 0;
    int rightChoice = 0;
    clearOutput();
    printf("%d", turn);
    printGrid(grid);
    if (turn % 2 == 0) {
        printf("%s, c'est à vous de jouer !\n", redName);
        printf("Entrez la lettre de la colonne où vous voulez placer votre pion : ");
        scanf("%c", &choice);
        if (choice >= 'A' && choice <= 'G') {
        }
        else if (choice >= 'a' && choice <= 'g') {
        } else {
            printf("\033[0;31m");
            printf("Veuillez choisir une colonne valide !\n");
            printf("\033[0m");
        }
        if (choice >= 'A' && choice <= 'G') {
            col = choice - 'A';
        }
        else if (choice >= 'a' && choice <= 'g') {
            col = choice - 'a';
        }
        while (i < ROWS) {
            if(grid[i][col] == 'x') {
                grid[i][col] = 'O';
                nbCoupRed++;
                break;
            }
            i++;
        }
        if (i == ROWS) {
            printf("\033[0;31m");
            printf("La colonne est pleine !\n");
            printf("\033[0m");
            i = 0;
        }
        i = 0;
    }
    else if (turn % 2 == 1) {
        printf("%s, c'est à vous de jouer !\n", greenName);
        printf("Entrez la lettre de la colonne où vous voulez placer votre pion : ");
        scanf("%c", &choice);
        if ((choice < 'A' || choice > 'G') || (choice < 'a' || choice > 'g')) {
            printf("\033[0;31m");
            printf("Veuillez choisir une colonne valide !\n");
            printf("\033[0m");
        }
        else {
            if (choice >= 'A' && choice <= 'G') {
                col = choice - 'A';
            }
            else if (choice >= 'a' && choice <= 'g') {
                col = choice - 'a';
            }
            while (i < ROWS) {
                if(grid[i][col] == 'x') {
                    grid[i][col] = '0';
                    nbCoupGreen++;
                    break;
                }
                i++;
            }
            if (i == ROWS) {
                printf("\033[0;31m");
                printf("La colonne est pleine !\n");
                printf("\033[0m");
                i = 0;
            }
            i = 0;
        }
    }
    else {
        printf("\033[0;31m");
        printf("Ya une couille la\n");
        printf("\033[0m");
    }
    turn = turn + 1;
    clearOutput();
    printGrid(grid);
    //win = checkWin(grid, redName, greenName, nbCoupRed, nbCoupGreen);
    if (win == 0) {
        logicGame(grid, redName, greenName, turn);
        return 0;
    }
    return win;
}