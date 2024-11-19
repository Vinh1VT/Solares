#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "ModelePhysique.h"
#include <stdio.h>

#define PERIODE 5

Planet Soleil ={
.Mass = 1E25,
.Pos_x= 400,
.Pos_y= 225,
.Vitesse_x = 0,
.Vitesse_y = 0};

Planet Terre ={
.Mass = 1,
.Pos_x = 600,
.Pos_y = 225,
.Vitesse_x = 0,
.Vitesse_y = -58};

int main(void)
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 450;
/*
    Planet P;
    P.Pos_x = 0.0f;
    P.Pos_y = 0.0f;//toute cette partie est temporaire, faudra qu'on voit comment implémenter ça planete par planete
    float R = 100;
*/
    double actualTime; //temps actuel
    double previousTime = GetTime(); //temps de début de la simulation
    double deltaTime = 0; //temps écoulé depuis le début de la simulation

    SetTargetFPS(60);

    InitWindow(ScreenWidth, ScreenHeight, "Simulation");




    while (!WindowShouldClose())
    {
/*
        P.Pos_x = (float)ScreenWidth/2 + R * cosf(((2*PI)/PERIODE)*deltaTime);
        P.Pos_y = (float)ScreenHeight/2 + R * sinf(((2*PI)/PERIODE)*deltaTime); //On incrémente la position de oméga à chaque boucle (une boucle = 1 frame)
*/
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(ScreenWidth/2, ScreenHeight/2, 25, YELLOW);
        DrawCircle(Terre.Pos_x, Terre.Pos_y, 10, BLUE);

        EndDrawing();

        actualTime = GetTime();
        deltaTime = (actualTime - previousTime);
        previousTime = actualTime;
        GetNextPosition(&Terre, Soleil, deltaTime);
        float V = sqrt((Terre.Vitesse_x*Terre.Vitesse_x)+(Terre.Vitesse_y*Terre.Vitesse_y)); 
        //printf("%f %f %f \n", Terre.Vitesse_x, Terre.Vitesse_y, V);
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
