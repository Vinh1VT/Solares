#include "Planete.h"

float get_R(Planet* P,Planet* T);
float get_theta(Planet* P, Planet* T);
void GetNextPosition(Planet* P, Planet* S,float deltatime);
void append(ListPlanet* L, Planet P, Color C, float Taille);
int len(ListPlanet *L);
void GetNextPosition_lune(Planet* P, Planet* S,Planet* Sol, float deltatime);