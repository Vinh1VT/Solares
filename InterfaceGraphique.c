#include "raylib.h"
#include <stdlib.h>
#include <math.h>

int main(void)
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 450;
    
    double StartTime = GetTime();
    double actualTime = 0;
    double deltaTime = 0.0;
    float positionX = 0.0f;
    float positionY = 0.0f;
    float R = 70;

    SetTargetFPS(60);
    
    InitWindow(ScreenWidth, ScreenHeight, "Simulation");
    
    
    
    
    while (!WindowShouldClose())
    {
        positionX = ScreenWidth/2 + R * cos(((2*PI)/0.016)*deltaTime);
        positionY = ScreenHeight/2 + R * sin(((2*PI)/0.016)*deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(ScreenWidth/2, ScreenHeight/2, 50, YELLOW);
        
        DrawCircle(positionX, positionY, 10, BLUE);
        
        EndDrawing();

        actualTime = GetTime();
        deltaTime = actualTime - StartTime;
        StartTime = actualTime;
        
    }

    CloseWindow();

    return EXIT_SUCCESS;
}