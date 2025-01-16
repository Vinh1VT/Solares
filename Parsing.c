#include <stdlib.h>
#include <stdio.h>
#include "Planete.h"
#include <string.h>

Color Conversion_couleur(char* str){
    if (strcmp(str, "LIGHTGRAY") == 0) return LIGHTGRAY;
    if (strcmp(str, "GRAY") == 0) return GRAY;
    if (strcmp(str, "DARKGRAY") == 0) return DARKGRAY;
    if (strcmp(str, "YELLOW") == 0) return YELLOW;
    if (strcmp(str, "GOLD") == 0) return GOLD;
    if (strcmp(str, "ORANGE") == 0) return ORANGE;
    if (strcmp(str, "PINK") == 0) return PINK;
    if (strcmp(str, "RED") == 0) return RED;
    if (strcmp(str, "MAROON") == 0) return MAROON;
    if (strcmp(str, "GREEN") == 0) return GREEN;
    if (strcmp(str, "LIME") == 0) return LIME;
    if (strcmp(str, "DARKGREEN") == 0) return DARKGREEN;
    if (strcmp(str, "SKYBLUE") == 0) return SKYBLUE;
    if (strcmp(str, "BLUE") == 0) return BLUE;
    if (strcmp(str, "DARKBLUE") == 0) return DARKBLUE;
    if (strcmp(str, "PURPLE") == 0) return PURPLE;
    if (strcmp(str, "VIOLET") == 0) return VIOLET;
    if (strcmp(str, "DARKPURPLE") == 0) return DARKPURPLE;
    if (strcmp(str, "BEIGE") == 0) return BEIGE;
    if (strcmp(str, "BROWN") == 0) return BROWN;
    if (strcmp(str, "DARKBROWN") == 0) return DARKBROWN;
    if (strcmp(str, "WHITE") == 0) return WHITE;
    if (strcmp(str, "BLACK") == 0) return BLACK;
    if (strcmp(str, "BLANK") == 0) return BLANK;
    if (strcmp(str, "MAGENTA") == 0) return MAGENTA;
    if (strcmp(str, "RAYWHITE") == 0) return RAYWHITE;
    return BLACK;
}



Planet* parse(FILE *f, float PosInitX,float PosInitY){
    char ligne[100];
    int nb_planete = 8;
    Planet *tableau = malloc(nb_planete*sizeof(Planet));
    if(tableau==NULL){
        fprintf(stderr,"erreur d'allocation mémoire");
    };
    int compteur = 0;
    fgets(ligne,sizeof(ligne),f);
    while(fgets(ligne,sizeof(ligne),f)){
        
        if(compteur >= nb_planete){
            tableau = realloc(tableau,(compteur+1)*sizeof(Planet));
            if(tableau==NULL){
                fprintf(stderr,"erreur d'allocation mémoire");
            };
        }

        Planet P;
        char couleur[20];

        sscanf(ligne,"%15[^,],%f,%f,%f,%f,%19s",P.Nom,&P.Taille,&P.Pos_x,&P.Mass,&P.Vitesse_y,couleur);

        P.couleur = Conversion_couleur(couleur);
        P.Pos_x += PosInitX;
        P.Pos_y = PosInitY;
        P.Vitesse_y = -P.Vitesse_y;
        P.Vitesse_x = 0;


        tableau[compteur] = P;
        compteur++;
    }
    return tableau;
}