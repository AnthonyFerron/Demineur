#include "puissance4.h"

void regles() {
    printf("Bienvenue dans le jeu du puissance 4 !\n");
    printf("Le but du jeu est d'aligner 4 pions de sa couleur horizontalement, verticalement ou diagonalement.\n");
    printf("Le premier joueur qui aligne 4 pions de sa couleur gagne la partie.\n");
    printf("Bonne chance !\n\n");
    return;
}

void clearOutput(void) {
    printf("\033[H\033[2J");
}

void theMain() {
    clearOutput();
    regles();
    int choix;
    do
    {
        printf("Que voulez vous faire ?\n");
        printf(" 1. Jouer\n 2. Charger une partie\n 3. Afficher les regles\n 4. Quitter\n\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            clearOutput();
            initGame();
            break;
        case 2:
            clearOutput();
            //loadAGame();
            break;
        case 3:
            clearOutput();
            regles();
            choix = 0;
            break;
        case 4:
            clearOutput();
            printf("Merci d'avoir joué !\n");
            printf("A bientôt !\n");
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

int main(void) {
    theMain();
    return 0;
}