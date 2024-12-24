#include "Planete.h"
#ifndef MODELE
#define MODELE
float get_R(Planet* P,Planet* T);
float get_theta(Planet* P, Planet* T);
void GetNextPosition(Planet* P, Planet* S,float deltatime);
void GetNextVitesse(Planet* P, Planet* S,float deltatime);
void append(ListPlanet* L, Planet P, Color C, float Taille);
int len(ListPlanet *L);
void GetNextPosition_lune(Planet* P, Planet* S,Planet* Sol, float deltatime);
void GetNextVitesseAll(ListPlanet* liste,Planet* S, float deltatime);
void GetNextPositionAll(ListPlanet* liste, float deltatime);
void DrawAll(ListPlanet* liste);
#endif