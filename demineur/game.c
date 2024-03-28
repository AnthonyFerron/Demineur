#include "demineur.h"



int nbRevealed(char **playerGrid) {
    int count = 0;
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            if (playerGrid[j][i] != 'x' && playerGrid[j][i] != 'P') {
                count++;
            }
        }
    }
    return count;
}

void startGame(char **playerGrid, char **realGrid, long int cpu_time_store) {
    time_t start, end;
    long int cpu_time_used;
    int win = 0;
    start = time(NULL);
    win = logicGame(playerGrid, realGrid);
    end = time(NULL);
    cpu_time_used = difftime(end, start);
    cpu_time_used += cpu_time_store;
    if(win == 2) {
        saveGame(playerGrid, realGrid, cpu_time_used);
    }
    for (int i = 0; i < TAILLE; i++) {
        free(playerGrid[i]);
    }
    free(playerGrid);
    for (int i = 0; i < TAILLE; i++) {
        free(realGrid[i]);
    }
    free(realGrid);
    
    if(win == 1) {
        endGame(1, cpu_time_used);
    } else if(win == 0)
    {
        endGame(0, cpu_time_used);
    }
    else {
        printf("Problem, problem !!\n");
    }
    return;
}

void initGame(void) {


    //init grid
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

    startGame(playerGrid, realGrid, 0);
    for (int i = 0; i < TAILLE; i++) {
        free(grid[i]);
    }
    free(grid);
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

int logicGame(char **playerGrid, char **realGrid) {
    int game = 1;
    char action;
    char case1 = 0;
    char case2 = 0;
    int x = 0;
    int y = 0;
    int revealed = nbRevealed(playerGrid);
    while (game) {
        clearOutput();
        printf("Pour jouer, écrivez sur 'x' pour découvrir une case et 'd' pour poser un drapeau\n");
        printf("Ensuite, indiquez la position avec les lettres en minuscule\n");
        printf("Exemple : x a b pour decouvrir la case de la collone A, ligne B\n");
        printf("Vous pouvez quitter la partie en écrivant 'qaa'\n");
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
                return 0;
            } else {
                playerGrid[y][x] = realGrid[y][x];
                revealed++;
                if (revealed == TAILLE * TAILLE - nbMines(realGrid)) {
                    clearOutput();
                    printf("Vous avez gagné !\n");
                    printf("\n\n");
                    printGrid(playerGrid);
                    game = 0;
                    return 1;
                }
            }
            
        } else if (action == 'q') {
            printf("Voulez-vous sauvegarder la partie ? (s/n) : ");
            char choix;
            scanf(" %c", &choix);
            if (choix == 's') {
                game = 0;
                return 2;
            }
            game = 0;
            return 0;
        } else if (action == 's') {
            game = 0;
            return 2;
        }
        else(printf("Veuillez entrer une action valide !\n"));
    }
    return 0;
}

void endGame(int win, long int time) {
    int choix;

    if (win == 1) {
        printf("Votre temps : %d minutes et %d secondes\n", (int)time / 60, (int)time % 60);
        printf("Entrez votre nom pour le tableau des scores : ");
        char name[50];
        scanf("%s", name);
        addScore(name, time);
    }
    else {}
    do
    {
    printf("Merci d'avoir joué !\n");
    printf("Que souhaitez vous faire ? \n 1)Rejouer \n 2)Menu principal \n 3)Voir le tableau des scores\n 4)Quitter\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            clearOutput();
            initGame();
            break;
        case 2:
            clearOutput();
            theMain();
            break;
        case 3:
            clearOutput();
            printScores();
            choix = 0;
            break;
        case 4:
            clearOutput();
            printf("Merci d'avoir jouer !\nA bientot !\n");
            break;
        default:
            printf("\033[0;31m");
            printf("Veuillez choisir un chiffre valide !\n");
            printf("\033[0m");
            break;
        }
    } while (!(choix < 5 && choix > 0));
    return;
}