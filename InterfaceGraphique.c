#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "ModelePhysique.h"
#include <stdio.h>

#define PERIODE 5
#define MULTIPLICATEUR 1



int main(void)
{
    const int ScreenWidth = 1000;
    const int ScreenHeight = 1000;

    Planet Soleil ={
    .Mass = 1E25,
    .Pos_x= (float)ScreenWidth/2,
    .Pos_y= (float)ScreenHeight/2,
    .Vitesse_x = 0,
    .Vitesse_y = 0};

    Planet Terre ={
    .Mass = 1,
    .Pos_x = Soleil.Pos_x + 200,
    .Pos_y = Soleil.Pos_y,
    .Vitesse_x = 0,
    .Vitesse_y = -58};

    Planet Mars ={
    .Mass = 0.1,
    .Pos_x = Soleil.Pos_x+400,
    .Pos_y = Soleil.Pos_y, 
    .Vitesse_x = 0,
    .Vitesse_y = -40
    };

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
    SetWindowState(FLAG_WINDOW_RESIZABLE);



    while (!WindowShouldClose())
    {
/*
        P.Pos_x = (float)ScreenWidth/2 + R * cosf(((2*PI)/PERIODE)*deltaTime);
        P.Pos_y = (float)ScreenHeight/2 + R * sinf(((2*PI)/PERIODE)*deltaTime); //On incrémente la position de oméga à chaque boucle (une boucle = 1 frame)
*/
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(Soleil.Pos_x, Soleil.Pos_y, 20, YELLOW);
        DrawCircle(Terre.Pos_x, Terre.Pos_y, 10, BLUE);
        DrawCircle(Mars.Pos_x, Mars.Pos_y, 10, RED);

        EndDrawing();

        actualTime = GetTime();
        deltaTime = (actualTime - previousTime) * MULTIPLICATEUR;
        previousTime = actualTime;
        //GetNextPosition(&Terre, Mars, deltaTime);
        //GetNextPosition(&Mars, Terre, deltaTime);
        GetNextPosition(&Terre, Soleil, deltaTime);
        GetNextPosition(&Mars, Soleil, deltaTime);
        
        //float V = sqrt((Terre.Vitesse_x*Terre.Vitesse_x)+(Terre.Vitesse_y*Terre.Vitesse_y)); 
        //printf("%f %f %f \n", Terre.Vitesse_x, Terre.Vitesse_y, V);
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
