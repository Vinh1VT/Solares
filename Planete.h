#include "raylib.h"

#define TAILLETRACE 1800

#ifndef PLANETE
#define PLANETE

typedef struct Planet_{
    float Mass;
    float Pos_x;
    float Pos_y;
    float Vitesse_x;
    float Vitesse_y;
    Color couleur;
    float Taille;
} Planet;

typedef struct Point_ {
    float x;
    float y;
} Point;


typedef struct _ListPlanet{

    struct _ListPlanet* start;
    Planet* P;
    struct _ListPlanet* suivant;
    Point trace[TAILLETRACE];

} ListPlanet;
#endif