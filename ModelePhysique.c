#include "Planete.h"
#include <math.h>
#include <raylib.h>


#define G 1


float GetTheta(Planet P, Planet Soleil, float t, float R){
    float theta;
    if(P.Pos_x == Soleil.Pos_x && Soleil.Pos_y > P.Pos_x){
        theta = PI/2;
    } else if(P.Pos_x == Soleil.Pos_x){
        theta = -PI/2;
    } else {
        theta = atanf((Soleil.Pos_y - P.Pos_y / Soleil.Pos_x - P.Pos_x));
        if(Soleil.Pos_x < P.Pos_x){
            theta += PI;
        }
    }
    return theta;
    }
    
    
    /*P.Vitesse_x -= G * Soleil.Mass * cos(theta) * t / R;
    P.Vitesse_y -= G * Soleil.Mass * sin(theta) * t / R;

    P.Pos_x += P.Vitesse_x*t;
    P.Pos_y += P.Vitesse_y *t;*/


  /* P.Pos_x = Soleil.Pos_x + R * cosf(((2*PI)/10)*t);
    P.Pos_y = Soleil.Pos_y + R * sinf(((2*PI)/10)*t);
    printf("A %f %f \n", P.Pos_x, P.Pos_y);*/