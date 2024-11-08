#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "Planete.h"
#include <stdio.h>

#define PERIODE 5

int main(void)
{
    Planet P;
    P.Pos_x = 0.0f;
    P.Pos_y = 0.0f;//toute cette partie est temporaire, faudra qu'on voit comment implémenter ça planete par planete
    float R = 100;

    double actualTime; //temps actuel
    double previousTime = GetTime(); //temps de début de la simulation
    double deltaTime = 0; //temps écoulé depuis le début de la simulation

    //Gestion de la fenetre
    int ScreenWidth = 800;
    int ScreenHeight = 450; 
    SetTargetFPS(60);
    InitWindow(ScreenWidth, ScreenHeight, "Simulation");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    //Caméra
    Camera2D camera = {0};
    camera.zoom = 1.0f;


    while (!WindowShouldClose())
    {
        ScreenHeight = GetScreenHeight();
        ScreenWidth = GetScreenWidth();
        P.Pos_x = (float)ScreenWidth/2 + R * cosf(((2*PI)/PERIODE)*deltaTime);
        P.Pos_y = (float)ScreenHeight/2 + R * sinf(((2*PI)/PERIODE)*deltaTime); //On incrémente la position de oméga à chaque boucle (une boucle = 1 frame)
        camera.zoom += GetMouseWheelMove() * 0.10f;

        if (IsMouseButtonDown(0))
            {
                camera.target = (Vector2){GetMouseX()-ScreenWidth/2,GetMouseY()-ScreenHeight/2};
                printf("%d %d \n",GetMouseX(),GetMouseY());
            }
        BeginDrawing();
        ClearBackground(BLACK);
        
        BeginMode2D(camera);


        DrawCircle(ScreenWidth/2, ScreenHeight/2, 25, YELLOW);

        DrawCircle(P.Pos_x, P.Pos_y, 10, BLUE);

        EndMode2D();
        EndDrawing();

        actualTime = GetTime();
        deltaTime += actualTime - previousTime;
        previousTime = actualTime;
        //printf("%d\n", GetFPS());
    }

    CloseWindow();

    return EXIT_SUCCESS;
}