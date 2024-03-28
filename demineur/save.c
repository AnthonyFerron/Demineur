#include "demineur.h"
int logicGame(char **playerGrid, char **realGrid);
void loadAGame(void);
void deleteSave(char saveName[50]);

// Vérifier si un nom de sauvegarde existe déjà dans le fichier
int isSaveNameExists(const char *saveName) {
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char currentName[50];
    while (fgets(currentName, sizeof(currentName), file) != NULL) {
        currentName[strcspn(currentName, "\n")] = '\0';
        if (strcmp(currentName, saveName) == 0) {
            fclose(file);
            return 1;
        }
        for (int i = 0; i < 10; i++) {
            if (fgets(currentName, sizeof(currentName), file) == NULL) {
                break;
            }
        }
    }

    fclose(file);
    return 0;
}

// sauvegarder une partie en cours
void saveGame(char **playerGrid, char **realGrid) {
    char saveName[50];

    int choosenName = 0;
    do
    {
        printf("Enter a name for the save: ");
        scanf("%s", saveName);
        if (isSaveNameExists(saveName)) {
            printf("A save with the given name already exists. Please choose a different name.\n");
        } else {
            choosenName = 1;
        }
    } while (choosenName == 0);

    FILE *file = fopen("save.txt", "a");
    if (file == NULL) {
        printf("Erreur lors de la sauvegarde de la partie\n");
        return;
    }
    fprintf(file, "%s\n", saveName);
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
    printf("Game saved successfully.\n");
    theMain();
    return;
}

// charger une partie sauvegardée
void loadGame(void) {
    char saveName[50];
    printf("Enter the name of the save to load: ");
    scanf("%s", saveName);
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        printf("Aucune partie sauvegardée\n");
        return;
    }
    char line[50];
    char currentName[50];
    while (fgets(currentName, sizeof(currentName), file) != NULL) {
        currentName[strcspn(currentName, "\n")] = '\0';
        if (strcmp(currentName, saveName) == 0) {
            char **playerGrid = malloc(TAILLE * sizeof(char *));
            for (int i = 0; i < TAILLE; i++) {
                playerGrid[i] = malloc(TAILLE * sizeof(char));
            }
            char **realGrid = malloc(TAILLE * sizeof(char *));
            for (int i = 0; i < TAILLE; i++) {
                realGrid[i] = malloc(TAILLE * sizeof(char));
            }
            // Lire la grille du joueur
            for (int j = 0; j < TAILLE; j++) {
                fgets(line, sizeof(line), file);
                for (int i = 0; i < TAILLE; i++) {
                    playerGrid[j][i] = line[i];
                }
            }
            // Lire la grille réelle
            for (int j = 0; j < TAILLE; j++) {
                fgets(line, sizeof(line), file);
                for (int i = 0; i < TAILLE; i++) {
                    realGrid[j][i] = line[i];
                }
            }
            deleteSave(saveName);
            fclose(file);
            logicGame(playerGrid, realGrid);
            return;
        }
        for (int i = 0; i < TAILLE * 2; i++) {
            fgets(line, sizeof(line), file);
        }
    }
    printf("No save found with the given name.\n");
}

//liste des parties sauvegardées
void listSave(void) {
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        printf("Aucune partie sauvegardée\n");
        return;
    }
    char line[50];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        printf("%s\n", line);
        for (int i = 0; i < TAILLE * 2; i++) {
            fgets(line, sizeof(line), file);
        }
    }
    printf("\n");
    fclose(file);
}

// Supprimer une partie sauvegardée
void deleteSave(char saveName[50]) {
    
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        printf("Aucune partie sauvegardée\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Erreur lors de la suppression de la sauvegarde\n");
        return;
    }

    char currentName[50];
    char line[50];
    int found = 0;

    while (fgets(currentName, sizeof(currentName), file) != NULL) {
        currentName[strcspn(currentName, "\n")] = '\0';
        if (strcmp(currentName, saveName) == 0) {
            found = 1;
            for (int i = 0; i < 10; i++) {
                if (fgets(line, sizeof(line), file) == NULL) {
                    break;
                }
            }
        } else {
            fprintf(tempFile, "%s\n", currentName);
            for (int i = 0; i < 10; i++) {
                if (fgets(line, sizeof(line), file) == NULL) {
                    break;
                }
                fprintf(tempFile, "%s", line);
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("save.txt");
    rename("temp.txt", "save.txt");

    if (found) {
        printf("Save '%s' deleted successfully.\n", saveName);
    } else {
        printf("No save found with the given name.\n");
    }
}



void loadAGame(void) {
    int choix;
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
            listSave();
            loadGame();
            break;
        case 3:
            clearOutput();
            listSave();
            char saveName[50];
            printf("Enter the name of the save to delete: ");
            scanf("%s", saveName);
            deleteSave(saveName);
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