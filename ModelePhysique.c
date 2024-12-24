#include <math.h>
#include <stdlib.h>
#include "Planete.h"
#include "raylib.h"

/* Quelques constantes*/
float G = 6.67E-20;


/* Retourne le rayon entre P et T, peu importe l'ordre*/
float get_R(Planet* P,Planet* T){
    return sqrt((P->Pos_x - T->Pos_x)*(P->Pos_x - T->Pos_x) + (P->Pos_y - T->Pos_y)*(P->Pos_y - T->Pos_y));
}

/*Retourne l'angle entre P et T, en prenant P comme l'origine*/
float get_theta(Planet* P, Planet* T){
    float theta;
    if ((P->Pos_x==T->Pos_x) && (T->Pos_y > P->Pos_y)){
        theta=PI/2;
    }
    else if (P->Pos_x==T->Pos_x){
        theta=-PI/2;
    }
    else{
        theta = atanf((T->Pos_y-P->Pos_y)/(T->Pos_x-P->Pos_x));
        if (T->Pos_x < P->Pos_x){
            theta += PI;
        }
    }
    return theta;
}

/* Calcule la prochaine vitesse de P, en prenant en compte la gravité de S. à appliquer pour chaque planète qui exerce de la gravité*/
void GetNextVitesse(Planet* P, Planet* S,float deltatime){
    float R = get_R(P,S);
    float theta = get_theta(P,S);

    P->Vitesse_x += (G * S->Mass * cosf(theta) * deltatime) / (R*R);
    P->Vitesse_y += (G * S->Mass * sinf(theta) * deltatime) / (R*R);

    return;
}

/* Calcule la prochaine position de P, en prenant en compte la gravité de S*/
void GetNextPosition(Planet* P, Planet* S,float deltatime){
    P->Pos_x += P->Vitesse_x * deltatime;
    P->Pos_y += P->Vitesse_y * deltatime;
    return;
}

//Ajoute une planete a la liste des planetes
void append(ListPlanet *L, Planet P, Color C, float T){
    ListPlanet* i = L;
    while(i->suivant!=NULL){
        i = i-> suivant;
    }
    i->suivant = malloc(sizeof(ListPlanet));
    i = i->suivant;
    i->Taille = T;
    i->start = L;
    i->suivant = NULL;
}

//Calcule la longueur de la liste des planetes
int len(ListPlanet *L){
    ListPlanet* i = L;
    int length = 0; 

    while(i!=NULL){
        length+=1;
        i = i->suivant;
    }
    return length;
}

void GetNextPosition_lune(Planet* P, Planet* S,Planet* Sol, float deltatime){
    float R = get_R(P,S);
    float theta = get_theta(P,S);
    
    P->Vitesse_x += (G * S->Mass * cosf(theta) * deltatime) / (10+R*R);
    P->Vitesse_y += (G * S->Mass * sinf(theta) * deltatime) / (10+R*R);
    
    R = get_R(S,Sol);
    theta = get_theta(S,Sol);

    P->Vitesse_x += (G * Sol->Mass * cosf(theta) * deltatime) / (R*R);
    P->Vitesse_y += (G * Sol->Mass * sinf(theta) * deltatime) / (R*R);

    P->Pos_x += P->Vitesse_x * deltatime;
    P->Pos_y += P->Vitesse_y * deltatime;
}