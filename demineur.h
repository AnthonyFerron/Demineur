#ifndef DEMINEUR
#define DEMINEUR



// void realGridWithMines(char **grid);
// int countMines(char **grid, int x, int y);
// char **realGridInit(char **grid);
// void printGrid(char **grid);
// void initGame(void);
// void regles(void);
// void clearOutput(void);

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


#define TAILLE 5
#define MINES 10

void clearOutput(void);
void regles(void);

#include "grid.c"
#include "game.c"



#endif