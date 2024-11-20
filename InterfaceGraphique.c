#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "ModelePhysique.h"
#include <stdio.h>

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
    .Pos_x = Soleil.Pos_x+304,
    .Pos_y = Soleil.Pos_y, 
    .Vitesse_x = 0,
    .Vitesse_y = -40
    };

    Planet Mercure= {
        .Pos_x = Soleil.Pos_x+78,
        .Pos_y = Soleil.Pos_y,
        .Vitesse_x = 0,
        .Vitesse_y = -95
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
    
    //Caméra
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.target = (Vector2){0,0};


    while (!WindowShouldClose())
    {
/*
        P.Pos_x = (float)ScreenWidth/2 + R * cosf(((2*PI)/PERIODE)*deltaTime);
        P.Pos_y = (float)ScreenHeight/2 + R * sinf(((2*PI)/PERIODE)*deltaTime); //On incrémente la position de oméga à chaque boucle (une boucle = 1 frame)
*/
        if(IsKeyDown(KEY_UP)) camera.target.y += 2;
        if(IsKeyDown(KEY_DOWN)) camera.target.y -= 2;
        if(IsKeyDown(KEY_RIGHT)) camera.target.x -= 2;
        if(IsKeyDown(KEY_LEFT)) camera.target.x += 2;


        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);


        DrawCircle(Soleil.Pos_x, Soleil.Pos_y, 20, YELLOW);
        DrawCircle(Terre.Pos_x, Terre.Pos_y, 10, BLUE);
        DrawCircle(Mars.Pos_x, Mars.Pos_y, 10, RED);
        DrawCircle(Mercure.Pos_x, Mercure.Pos_y, 5 , WHITE);

        EndMode2D();

        EndDrawing();

        actualTime = GetTime();
        deltaTime = (actualTime - previousTime)*MULTIPLICATEUR;
        previousTime = actualTime;
        //GetNextPosition(&Terre, Mars, deltaTime);
        //GetNextPosition(&Mars, Terre, deltaTime);
        GetNextPosition(&Terre, &Soleil, deltaTime);
        GetNextPosition(&Mars, &Soleil, deltaTime);
        GetNextPosition(&Mercure, &Soleil, deltaTime);
        //float V = sqrt((Terre.Vitesse_x*Terre.Vitesse_x)+(Terre.Vitesse_y*Terre.Vitesse_y)); 
        //printf("%f %f %f \n", Terre.Pos_x, Terre.Pos_y, V);
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
