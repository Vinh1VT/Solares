#include "Planete.h"
#include "raylib.h"
#include <stdio.h>

#ifndef PARSING
#define PARSING

Color Conversion_couleur(char* str);
Planet* parse(FILE *f, float PosInitX,float PosInitY);

#endif