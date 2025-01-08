#include "Planete.h"
#ifndef MODELE
#define MODELE
float get_R(Planet* P,Planet* T);
float get_theta(Planet* P, Planet* T);
void GetNextPosition(Planet* P, Planet* S,float deltatime);
void GetNextVitesse(Planet* P, Planet* S,float deltatime);
void append(ListPlanet* L, Planet* P, bool trace);
int len(ListPlanet *L);
void GetNextPosition_lune(Planet* P, Planet* S,Planet* Sol, float deltatime);
void GetNextVitesseAll(ListPlanet* liste,Planet* S, float deltatime);
void GetNextPositionAll(ListPlanet* liste, float deltatime);
void DrawAll(ListPlanet* liste);
void DrawTrace(ListPlanet* liste);
void UpdateTrace(ListPlanet* liste,int i);
ListPlanet* newListe(Planet *P);
void freeList(ListPlanet* l);
Planet* newPlanet(float M,float x, float y, float vx, float vy, Color couleur, float t, char* Nom);
ListPlanet* RemovePlanet(char* Name,ListPlanet* List);
void DrawName(ListPlanet* liste, Camera2D* camera);
void add_asteroide(int nbr,int rmin, int rmax, Planet* centr ,ListPlanet* list);
#endif