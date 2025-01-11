#include "raylib.h"


#ifndef PLANETE
#define PLANETE

#define TAILLETRACE 1800

typedef struct Planet_{
    char Nom[20];
    float Mass;
    float Pos_x;
    float Pos_y;
    float Vitesse_x;
    float Vitesse_y;
    Color couleur;
    float Taille;
} Planet;

typedef struct _ListPlanet{

    Planet* P;
    struct _ListPlanet* suivant;
    Vector2* trace;
    bool planete;

} ListPlanet;
#endif