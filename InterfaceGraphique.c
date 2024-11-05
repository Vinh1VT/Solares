#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define PERIODE 5

int main(void)
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 450;
    

    float positionX = 0.0f;
    float positionY = 0.0f;
    float R = 100;
    float rad = 0.0;
    double actualTime;
    double previousTime = GetTime();
    double deltaTime = 0;

    SetTargetFPS(60);
    
    InitWindow(ScreenWidth, ScreenHeight, "Simulation");
    
    
    
    
    while (!WindowShouldClose())
    {

        positionX = (float)ScreenWidth/2 + R * cosf(((2*PI)/PERIODE)*deltaTime);
        positionY = (float)ScreenHeight/2 + R * sinf(((2*PI)/PERIODE)*deltaTime); //On incrémente la position de oméga à chaque boucle (une boucle = 1 frame)


        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawCircle(ScreenWidth/2, ScreenHeight/2, 25, YELLOW);
        
        DrawCircle(positionX, positionY, 10, BLUE);
        
        EndDrawing();

        rad += 2*PI/120;
        
        actualTime = GetTime();
        deltaTime += actualTime - previousTime;
        previousTime = actualTime;

    }

    CloseWindow();

    return EXIT_SUCCESS;
}