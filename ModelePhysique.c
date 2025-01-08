#include <math.h>
#include <stdlib.h>
#include "Planete.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

/* Quelques constantes*/
const float G = 6.67E-20;


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

/* Calcule la prochaine position de P*/
void GetNextPosition(Planet* P,float deltatime){
    P->Pos_x += P->Vitesse_x * deltatime;
    P->Pos_y += P->Vitesse_y * deltatime;
    return;
}

//Ajoute une planete a la liste des planetes
void append(ListPlanet *L, Planet* Plan,bool planete){
    ListPlanet* i = L;
    while(i->suivant!=NULL){
        i = i-> suivant;
    }
    i->suivant = malloc(sizeof(ListPlanet));
    i = i->suivant;
    i->P = Plan;
    i->start = L;
    i->suivant = NULL;
    i->planete = planete;
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
/* Parcourt la liste chainée pour update la vitesse de toutes les planètes, par rapport à la gravité de S*/
void GetNextVitesseAll(ListPlanet* liste,Planet* S, float deltatime){
    ListPlanet* lis = liste;
    while(lis->suivant != NULL){
        GetNextVitesse((lis->P),S,deltatime);
        lis = lis->suivant;
    }
    GetNextVitesse((lis->P),S,deltatime);
    return;
}

/* Parcourt la liste chainée pour update la position de toutes les planètes*/
void GetNextPositionAll(ListPlanet* liste, float deltatime){
    ListPlanet* lis = liste;
    while(lis->suivant != NULL){
        GetNextPosition((lis->P),deltatime);
        lis = lis->suivant;
    }
    GetNextPosition((lis->P),deltatime);
    return;
}
/* Parcourt la liste chainée pour dessiner toutes les planètes*/
void DrawAll(ListPlanet* liste){
    ListPlanet* lis = liste;
    while(lis->suivant != NULL){
        DrawCircle(lis->P->Pos_x,lis->P->Pos_y,lis->P->Taille,lis->P->couleur);
        lis = lis->suivant;
    }
    DrawCircle(lis->P->Pos_x,lis->P->Pos_y,lis->P->Taille,lis->P->couleur);
    return;
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

//Affiche toute les traces
void DrawTrace(ListPlanet* liste){
    while(liste!=NULL){
        for(int j = 0;j<TAILLETRACE;j++){
            if(liste->planete)
            DrawPixel(liste->trace[j].x,liste->trace[j].y,liste->P->couleur);
        }
        liste = liste->suivant;
    }
}

//Ajoute les points dans les traces
void UpdateTrace(ListPlanet* liste,int i){
    while(liste!=NULL){
        if(liste->planete){
        liste->trace[i].x = liste->P->Pos_x;
        liste->trace[i].y = liste->P->Pos_y;
        }
        liste = liste->suivant;
    }
}

//initialise une nouvelle liste
ListPlanet* newListe(Planet *P, bool planete){
    ListPlanet* list = malloc(sizeof(ListPlanet));
    list->suivant = NULL;
    list-> P = P;
    list->start = list;
    list -> planete = planete;
    return list;
}

//free une liste (pour faire propre)
void freeList(ListPlanet* l){
    ListPlanet* p;
    l = l->suivant;
    while(l!=NULL){
        p = l;
        l = l->suivant;
        free(p);
    }
}
//Crée une nouvelle planete
Planet* newPlanet(float M,float x, float y, float vx, float vy, Color couleur, float t, char* Nom){
    Planet* P = malloc(sizeof(Planet));
    strcpy(P->Nom,Nom);
    P->Mass = M;
    P->Pos_x = x;
    P->Pos_y = y;
    P->Vitesse_x = vx;
    P-> Vitesse_y = vy;
    P->couleur = couleur;
    P->Taille = t;
    return P;
}

ListPlanet* RemovePlanet(char* Name,ListPlanet* List){
    ListPlanet* ptr = List;
    if(List->suivant == NULL || List == NULL){
        return List;
    }
    if(ptr->P->Nom == Name){
        return List->suivant;
    }
    while(ptr->suivant != NULL){
        if(ptr->suivant->P->Nom == Name){
            ptr->suivant = ptr->suivant->suivant;
            return List;
        }
        ptr = ptr->suivant;
    }
    return List;
}

void DrawName(ListPlanet* liste,Camera2D* camera){
    while (liste != NULL){
        Planet* P = liste->P;
        if(liste->planete)
            DrawText(P->Nom, P->Pos_x, P->Pos_y+P->Taille+5,((float)(10*GetScreenWidth())/1000)*(1/camera->zoom), P->couleur);
        liste = liste->suivant;
    }
}

/* ajoute nbr asteroides dans la liste, centrés autour de centr, entre les rayons rmin et rmax*/
void add_asteroide(int nbr,int rmin, int rmax, Planet* centr ,ListPlanet* list){
    float theta = 0;
    for (int i=0;i<nbr;i++){
        int r = GetRandomValue(rmin,rmax);
        int taille = GetRandomValue(1,4);
        Planet* plan = newPlanet(0.1,centr->Pos_x+r*cos(theta),centr->Pos_y+r*sin(theta),sin(theta)*sqrt(G*centr->Mass/r),-cos(theta)*sqrt(G*centr->Mass/r),GRAY,taille,"Asteroide");
        append(list,plan,false);
        theta += 2*PI/nbr;
    }
    return;
}