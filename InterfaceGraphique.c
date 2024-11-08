#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "Modele_physique.h"
#include <stdio.h>

#define PERIODE 5

int main(void)
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 450;

    Planet P;
    P.Pos_x = 100;
    P.Pos_y = 0;//toute cette partie est temporaire, faudra qu'on voit comment implémenter ça planete par planete

    Planet Soleil;
    Soleil.Pos_x = (float)ScreenWidth /2;
    Soleil.Pos_y = (float)ScreenHeight /2; 
    Soleil.Vitesse_x = 0;
    Soleil.Vitesse_y = 0;

    double actualTime; //temps actuel
    double previousTime = GetTime(); //temps de début de la simulation
    double deltaTime = 0; //temps écoulé depuis le début de la simulation

    
    SetTargetFPS(60);
    InitWindow(ScreenWidth, ScreenHeight, "Simulation");

    

    while (!WindowShouldClose())
    {
        //float R = sqrt(pow(Soleil.Pos_x - P.Pos_x,2)+pow(Soleil.Pos_y - P.Pos_y,2));
        float R = 100;


        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(ScreenWidth/2, ScreenHeight/2, 25, YELLOW);

        DrawCircle(P.Pos_x, P.Pos_y, 10, BLUE);

        EndDrawing();

        actualTime = GetTime();
        deltaTime += actualTime - previousTime;
        previousTime = actualTime;
        printf("%d %f %f \n", GetFPS(), P.Pos_x, P.Pos_y);
        GetNextPos(P,Soleil,deltaTime,R);
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
