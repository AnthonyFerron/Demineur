#include "puissance4.h"
int logicGame(char **grid, char *redName, char *greenName, int turn);
int checkWin(char **grid, char *redName, char *greenName, int nbCoupRed, int nbCoupGreen);

void winMessage(char *redName, char *greenName, int win) {
    if (win == 1) {
        printf("\033[0;32m");
        printf("Félicitations %s, vous avez gagné !\n", redName);
        printf("\033[0m");
        printf("Appuyez sur entrer pour continuer...\n");
        getchar();
        getchar();
    }
    else if (win == 2) {
        printf("\033[0;32m");
        printf("Félicitations %s, vous avez gagné !\n", greenName);
        printf("\033[0m");
        printf("Appuyez sur entrer pour continuer...\n");
        getchar();
        getchar();
    }
    else if (win == 3) {
        printf("\033[0;32m");
        printf("Match nul !\n");
        printf("\033[0m");
        printf("Appuyez sur entrer pour continuer...\n");
        getchar();
        getchar();
    }
    else {
        printf("%d", win);
        printf("\033[0;31m");
        printf("Petite erreur si tu vois ca, envoie moi un message que je puisse la rgler\n");
        printf("\033[0m");
        printf("Appuyez sur entrer pour continuer...\n");
        getchar();
        getchar();
    }
    return;
}


char *upperName(char *name) {
    char *p = name;
    if (p[0] >= 'a' && p[0] <= 'z') {
        p[0] -= 32;
    }
    return p;
}

void initGame(void) {
    char redName[50];
    char greenName[50];
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
    strcpy(redName, upperName(redtemp));
    strcpy(greenName, upperName(greentemp));
    printf("Bienvenue %s et %s !\n", redName, greenName);
    printf("%s joue avec des pions \033[0;31mO\033[0m (rouges)\n", redName);
    printf("%s joue avec des pions \033[0;32m0\033[0m (verts)\n", greenName);
    printf("Bonne chance !\n\n");
    printf("Appuyez sur entrer pour continuer...\n");
    getchar();
    getchar();
    int turn = 0;
    int win = 0;
    clearOutput();
    while (win == 0){
        win = logicGame(grid, redName, greenName, turn);
        if (win != 0)
            break;
    } 
    winMessage(redName, greenName, win);
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
    win = checkWin(grid, redName, greenName, nbCoupRed, nbCoupGreen);
    if (win != 0) {
        clearOutput();
        printGrid(grid);
        return win;
    }
    clearOutput();
    printGrid(grid);
    if (turn % 2 == 0) {
        printf("%s, c'est à vous de jouer !\n", redName);
        printf("Entrez la lettre de la colonne où vous voulez placer votre pion : ");
        scanf(" %c", &choice);
        if ((choice >= 'A' && choice <= 'G') || (choice >= 'a' && choice <= 'g')) {
            if (choice >= 'A' && choice <= 'G') {
                col = choice - 'A';
            }
            else if (choice >= 'a' && choice <= 'g') {
                col = choice - 'a';
            }
            while (i < ROWS) {
                if(grid[ROWS - 1 - i][col] == 'x') {
                    grid[ROWS - 1 - i][col] = 'O';
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
                printf("Appuyez sur entrer pour continuer...\n");
                getchar();
                getchar();
                logicGame(grid, redName, greenName, turn);
                return 0;
            }
        }
        else {
            printf("\033[0;31m");
            printf("Veuillez choisir une colonne valide !\n");
            printf("\033[0m");
            printf("Appuyez sur entrer pour continuer...\n");
            getchar();
            getchar();
            logicGame(grid, redName, greenName, turn);
            return 0;
        }
    }
    else if (turn % 2 == 1) {
        printf("%s, c'est à vous de jouer !\n", greenName);
        printf("Entrez la lettre de la colonne où vous voulez placer votre pion : ");
        scanf(" %c", &choice);
        if ((choice >= 'A' && choice <= 'G') || (choice >= 'a' && choice <= 'g')) {
            if (choice >= 'A' && choice <= 'G') {
                col = choice - 'A';
            }
            else if (choice >= 'a' && choice <= 'g') {
                col = choice - 'a';
            }
            while (i < ROWS) {
                if(grid[ROWS - 1 - i][col] == 'x') {
                    grid[ROWS - 1 - i][col] = '0';
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
                printf("Appuyez sur entrer pour continuer...\n");
                getchar();
                getchar();
                logicGame(grid, redName, greenName, turn);
                return 0;
            }
        }
        else {
            printf("\033[0;31m");
            printf("Veuillez choisir une colonne valide !\n");
            printf("\033[0m");
            printf("Appuyez sur entrer pour continuer...\n");
            getchar();
            getchar();
            logicGame(grid, redName, greenName, turn);
            return 0;
        }
    }
    else {
        printf("\033[0;31m");
        printf("Petite erreur si tu vois ca, envoie moi un message que je puisse la regler\n");
        printf("\033[0m");
        printf("Appuyez sur entrer pour continuer...\n");
        getchar();
        getchar();
        return 0;
    }
    turn++;
    logicGame(grid, redName, greenName, turn);
    return 0;
}

int checkWin(char **grid, char *redName, char *greenName, int nbCoupRed, int nbCoupGreen) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int win = 0;
    int nbCoup = nbCoupRed + nbCoupGreen;
    // check horizontal win
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS - 3; j++) {
            if (grid[i][j] == 'O' && grid[i][j + 1] == 'O' && grid[i][j + 2] == 'O' && grid[i][j + 3] == 'O') {
                win = 1;
                return win;
            }
            else if (grid[i][j] == '0' && grid[i][j + 1] == '0' && grid[i][j + 2] == '0' && grid[i][j + 3] == '0') {
                win = 2;
                return win;
            }
        }
    }
    // check vertical win
    for (i = 0; i < ROWS - 3; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j] == 'O' && grid[i + 1][j] == 'O' && grid[i + 2][j] == 'O' && grid[i + 3][j] == 'O') {
                win = 1;
                return win;
            }
            else if (grid[i][j] == '0' && grid[i + 1][j] == '0' && grid[i + 2][j] == '0' && grid[i + 3][j] == '0') {
                win = 2;
                return win;
            }
        }
    }
    // check diagonal win
    for (i = 0; i < ROWS - 3; i++) {
        for (j = 0; j < COLS - 3; j++) {
            if (grid[i][j] == 'O' && grid[i + 1][j + 1] == 'O' && grid[i + 2][j + 2] == 'O' && grid[i + 3][j + 3] == 'O') {
                win = 1;
                return win;
            }
            else if (grid[i][j] == '0' && grid[i + 1][j + 1] == '0' && grid[i + 2][j + 2] == '0' && grid[i + 3][j + 3] == '0') {
                win = 2;
                return win;
            }
        }
    }
    for (i = 0; i < ROWS - 3; i++) {
        for (j = 3; j < COLS; j++) {
            if (grid[i][j] == 'O' && grid[i + 1][j - 1] == 'O' && grid[i + 2][j - 2] == 'O' && grid[i + 3][j - 3] == 'O') {
                win = 1;
                return win;
            }
            else if (grid[i][j] == '0' && grid[i + 1][j - 1] == '0' && grid[i + 2][j - 2] == '0' && grid[i + 3][j - 3] == '0') {
                win = 2;
                return win;
            }
        }
    }
    if (nbCoup == 42) {
        win = 3;
        return win;
    }
    return win;
}
