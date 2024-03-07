#include "demineur.h"
double logicGame(char **playerGrid, char **realGrid);

// sauvegarder une partie en cours
void saveGame(char **playerGrid, char **realGrid) {
    FILE *file = fopen("save.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de la sauvegarde de la partie\n");
        return;
    }
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            fprintf(file, "%c", playerGrid[j][i]);
        }
        fprintf(file, "\n");
    }
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            fprintf(file, "%c", realGrid[j][i]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Partie sauvegardée avec succès !\n");
    theMain();
    return;
}

// charger une partie sauvegardée
void loadGame(void) {
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        printf("Aucune partie sauvegardée\n");
        return;
    }
    char **playerGrid = malloc(TAILLE * sizeof(char *));
    for (int i = 0; i < TAILLE; i++) {
        playerGrid[i] = malloc(TAILLE * sizeof(char));
    }
    char **realGrid = malloc(TAILLE * sizeof(char *));
    for (int i = 0; i < TAILLE; i++) {
        realGrid[i] = malloc(TAILLE * sizeof(char));
    }
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            fscanf(file, " %c", &playerGrid[j][i]);
        }
    }
    for (int j = 0; j < TAILLE; j++) {
        for (int i = 0; i < TAILLE; i++) {
            fscanf(file, " %c", &realGrid[j][i]);
        }
    }
    fclose(file);
    logicGame(playerGrid, realGrid);
    return;
}

//liste des parties sauvegardées
void listSave(void) {
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        printf("Aucune partie sauvegardée\n");
        return;
    }
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL && count < 5) {
        printf("%s", line);
        count++;
    }
    printf("\n");
    fclose(file);
}

//supprimer une partie sauvegardée
void deleteSave(void) {
    if (remove("save.txt") == 0) {
        printf("Partie sauvegardée supprimée avec succès !\n");
    } else {
        printf("Erreur lors de la suppression de la partie sauvegardée\n");
    }
    return;
}

void loadAGame(void) {
    int choix;
    clearOutput();
    do
    {
        printf("Que souhaitez vous faire ? \n 1)Liste des parties sauvegardées\n 2)Charger une partie\n 3)Supprimer une partie sauvegardée\n 4)Retour\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            clearOutput();
            listSave();
            choix = 0;
            break;
        case 2:
            clearOutput();
            loadGame();
            break;
        case 3:
            clearOutput();
            deleteSave();
            choix = 0;
            break;
        case 4:
            clearOutput();
            theMain();
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