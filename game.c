#include "demineur.h"

void logicGame(char **playerGrid, char **realGrid);
void endGame(void);
int nbMines(char **grid);


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

    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            playerGrid[j][i] = grid[j][i];
            realGrid[j][i] = grid[j][i];
        }
    }
    realGridInit(realGrid);
    realGridWithMines(realGrid);
    // printGrid(grid);
    // printGrid(playerGrid);
    // printGrid(realGrid);

    //Reveler 3 cases pour aider le joueur 
    int x = 0;
    int y = 0;
    
    x = rand() % TAILLE;
    y = rand() % TAILLE;
    do {
        x = rand() % TAILLE;
        y = rand() % TAILLE;
    } while (realGrid[y][x] == '*');
    playerGrid[y][x] = realGrid[y][x];
    int count = 0;
    int revealed = 0;
    while (revealed < 3 && count < TAILLE * TAILLE) {
        int x = count % TAILLE;
        int y = count / TAILLE;
        if (playerGrid[y][x] == 'x' && realGrid[y][x] != '*') {
            playerGrid[y][x] = realGrid[y][x];
            revealed++;
        }
        count++;
    }

    logicGame(playerGrid, realGrid);

    for (int i = 0; i < TAILLE; i++) {
        free(grid[i]);
    }
    free(grid);
    for (int i = 0; i < TAILLE; i++) {
        free(playerGrid[i]);
    }
    free(playerGrid);
    for (int i = 0; i < TAILLE; i++) {
        free(realGrid[i]);
    }
    free(realGrid);
    return;
}


void logicGame(char **playerGrid, char **realGrid) {
    int game = 1;
    char action;
    char case1 = 0;
    char case2 = 0;
    int x = 0;
    int y = 0;
    int revealed = 4;
    while (game) {
        clearOutput();
        printf("Pour jouer, écrivez sur 'x' pour découvrir une case et 'd' pour poser un drapeau\n");
        printf("Ensuite, indiquez la position avec les lettres en minuscule\n");
        printf("Exemple : x a b pour decouvrir la case de la collone A, ligne B\n");
        printf("Bonne chance !\n\n");
        printGrid(playerGrid);
        printf("\nEntrez votre coup : ");
        scanf(" %c %c %c", &action, &case1, &case2);
        if (case1 < 'a' || case1 > 'e' || case2 < 'a' || case2 > 'e') {
            printf("Veuillez entrer une case valide !\n");
            continue;
        }
        x = case1 - 'a';
        y = case2 - 'a';
        if (action == 'd') {
            if (playerGrid[y][x] == 'x') {
                playerGrid[y][x] = 'P';
            } else if (playerGrid[y][x] == 'P') {
                playerGrid[y][x] = 'x';
            }
        } else if (action == 'x') {
            if (realGrid[y][x] == '*') {
                clearOutput();
                playerGrid[y][x] = realGrid[y][x];
                printf("Vous avez perdu !\n");
                printf("\n\n");
                printGrid(playerGrid);
                printf("\n\n");
                printf("La solution était : \n");
                printGrid(realGrid);
                game = 0;
                endGame();
            } else {
                playerGrid[y][x] = realGrid[y][x];
                revealed++;
                if (revealed == TAILLE * TAILLE - nbMines(realGrid)) {
                    clearOutput();
                    printf("Vous avez gagné !\n");
                    printf("\n\n");
                    printGrid(playerGrid);
                    game = 0;
                    endGame();
                    
                }
            }
        }
        else(printf("Veuillez entrer une action valide !\n"));
    }
}

void endGame(void) {
    printf("Merci d'avoir joué !\n");
    printf("Que souhaitez vous faire ? \n 1)Rejouer \n 2)Menu principal \n 3)Quitter\n");
    return;
}

int nbMines(char **grid) {
    int count = 0;
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            if (grid[j][i] == '*') {
                count++;
            }
        }
    }
    return count;
}