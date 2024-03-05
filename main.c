#include "demineur.h"



void regles(void) {
    printf("Bienvenue sur le Démineur!\n\n");
    printf("Règles du jeu :\n");
    printf("1. Le jeu se déroule sur un plateau composé de cases.\n");
    printf("2. Certaines cases contiennent des mines et d'autres non.\n");
    printf("3. Le but du jeu est de découvrir toutes les cases sans mines.\n");
    printf("4. Lorsque vous découvrez une case sans mine, un nombre indique le nombre de cases voisines contenant des mines.\n");
    printf("5. Si vous découvrez une case avec une mine, le jeu est terminé.\n");
    printf("6. Utilisez les nombres révélés pour déduire l'emplacement des mines.\n");
    printf("7. Vous pouvez placer un drapeau sur une case suspectée de contenir une mine pour éviter de la découvrir par erreur.\n");
    printf("8. Le jeu est gagné lorsque toutes les cases sans mines sont découvertes.\n\n");
    return;
}

void clearOutput(void) {
    printf("\033[H\033[2J");
}




int main(void) {
    int choix;
    clearOutput();
    regles();
    do
    {
        printf("Que souhaitez vous faire ? \n 1)Regles \n 2)Jouer \n 3)Charger une partie\n 4)Tableau des records !\n 5)Quitter\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            clearOutput();
            regles();
            choix = 0;
            break;
        case 2:
            clearOutput();
            initGame();
            break;
        case 3:
            printf("Charger une partie\n");
            break;
        case 4:
            printf("Tableau des records !\n");
            break;
        case 5:
            printf("Quitter\n");
            break;
        default:
            printf("\033[0;31m");
            printf("Veuillez choisir un chiffre valide !\n");
            printf("\033[0m");
            break;
        }
    } while (!(choix < 6 && choix > 0));
    

    
    
    
    return 0;
}