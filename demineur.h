#ifndef DEMINEUR
#define DEMINEUR

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define TAILLE 5
#define MINES 1

void clearOutput(void);
void regles(void);
int theMain(void);

#include "save.c"
#include "scores.c"
#include "grid.c"
#include "game.c"

#endif

//created by @AnthonyFerron
//Thanks for playing !