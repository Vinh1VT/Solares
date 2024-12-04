#include "raylib.h"


typedef struct Planet_{
    float Mass;
    float Pos_x;
    float Pos_y;
    float Vitesse_x;
    float Vitesse_y;
} Planet;

typedef struct Point_ {
    float x;
    float y;
} Point;


typedef struct _ListPlanet{

    struct _ListPlanet* start;
    Planet P;
    struct _ListPlanet* suivant;
    Color couleur;
    float Taille;

} ListPlanet;