#include "demineur.h"

void printScores() {
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    printf("Tableau des records :\n\n");
    char line[100];
    int lineCount = 0;
    while (fgets(line, sizeof(line), file) && lineCount < 5) {
        printf("%s", line);
        lineCount++;
    }
    printf("\n\n");

    fclose(file);
}

typedef struct Score {
    char name[50];
    double time;
    struct Score *next;
} Score;

void addScore(char *playerName, double time) {
    int minutes = (int)time / 60;
    int seconds = (int)time % 60;
    int newScoreRank = 0;

    // Open the scores.txt file in read mode
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read the existing scores from the file
    Score *head = NULL;
    Score *tail = NULL;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        Score *temp = (Score *)malloc(sizeof(Score));
        int rank;
        sscanf(line, "%d) %s en %d minutes %d secondes", &rank, temp->name, &minutes, &seconds);
        temp->time = minutes * 60 + seconds;
        temp->next = NULL;
        if (head == NULL) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    // Close the file
    fclose(file);

    // Insert our score at the appropriate position
    Score *newScore = (Score *)malloc(sizeof(Score));
    strncpy(newScore->name, playerName, 50);
    newScore->time = time;
    newScore->next = NULL;
    if (head == NULL || head->time > time) {
        newScore->next = head;
        head = newScore;
        newScoreRank = 1;
    } else {
        Score *current = head;
        int rank = 1;
        while (current->next != NULL && current->next->time < time) {
            current = current->next;
            rank++;
        }
        newScore->next = current->next;
        current->next = newScore;
        newScoreRank = rank + 1;
    }

    // Open the scores.txt file in write mode
    file = fopen("scores.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write the updated scores to the file
    Score *current = head;
    int rank = 1;
    while (current != NULL) {
        minutes = (int)current->time / 60;
        seconds = (int)current->time % 60;
        fprintf(file, "%d) %s en %d minutes %d secondes\n", rank, current->name, minutes, seconds);
        current = current->next;
        rank++;
    }

    // Close the file
    fclose(file);
    
    if (newScoreRank == 1) {
        printf("Félicitations, vous avez obtenu le meilleur score !\n");
    } else {
        printf("Félicitations, vous avez obtenu le %dème meilleur score !\n", newScoreRank);
    }
}