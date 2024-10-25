#include "raylib.h"
#include "rlgl.h"
#include <stdlib.h>

int main(void)
{
    InitWindow(800, 450, "Simulation");
    Camera2D Camera = {0};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode2D(Camera);
        SetTargetFPS(10);
        ClearBackground(BLACK);
        DrawCircle(400,225,50,YELLOW);
        while(1){
            rlPushMatrix();
            rlScalef(10, 10, 10);
            rlPopMatrix();
            };


        EndMode2D();
        EndDrawing();

    }

    CloseWindow();

    return EXIT_SUCCESS;
}