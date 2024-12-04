#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "ModelePhysique.h"
#include <stdio.h>

#define MULTIPLICATEUR 1
#define TAILLETRACE 1800


int main(void)
{
    int ScreenWidth = 1000;
    int ScreenHeight = 1000;

    Point TraceTerre[TAILLETRACE];
    Point TraceMars[TAILLETRACE];
    Point TraceMercure[TAILLETRACE];


    Planet Soleil ={
    .Mass = 1E25,
    .Pos_x= (float)ScreenWidth/2,
    .Pos_y= (float)ScreenHeight/2,
    .Vitesse_x = 0,
    .Vitesse_y = 0
    };

    Planet Terre ={
    .Mass = 1,
    .Pos_x = Soleil.Pos_x + 200,
    .Pos_y = Soleil.Pos_y,
    .Vitesse_x = 0,
    .Vitesse_y = -58
    };

    Planet Mars ={
    .Mass = 0.1,
    .Pos_x = Soleil.Pos_x+304,
    .Pos_y = Soleil.Pos_y, 
    .Vitesse_x = 0,
    .Vitesse_y = -47
    };

    Planet Mercure= {
        .Pos_x = Soleil.Pos_x+78,
        .Pos_y = Soleil.Pos_y,
        .Vitesse_x = 0,
        .Vitesse_y = -95
    };



    InitWindow(ScreenWidth, ScreenHeight, "Simulation");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    
    //Caméra
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.target = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};


    //Traceur
    int i = 0;
    /* variables temporelles à mettre juste avant la boucle principale*/
    SetTargetFPS(60);
    double actualTime; //temps actuel
    double previousTime = GetTime(); //temps de début de la simulation
    double deltaTime = 0; //temps écoulé depu²is le début de la simulation
    float deltaTime2 = 0;
    
    while (!WindowShouldClose())
    {
/*      
        P.Pos_x = (float)ScreenWidth/2 + R * cosf(((2*PI)/PERIODE)*deltaTime);
        P.Pos_y = (float)ScreenHeight/2 + R * sinf(((2*PI)/PERIODE)*deltaTime); //On incrémente la position de oméga à chaque boucle (une boucle = 1 frame)
*/

        if(i==TAILLETRACE) i=0;

        ScreenHeight = GetScreenHeight();
        ScreenWidth = GetScreenWidth();

        camera.offset = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};

        //controle de la caméra 
        if(true){
        if(IsKeyDown(KEY_UP)) camera.target.y -= 2;
        if(IsKeyDown(KEY_DOWN)) camera.target.y += 2;
        if(IsKeyDown(KEY_RIGHT)) camera.target.x += 2;
        if(IsKeyDown(KEY_LEFT)) camera.target.x -= 2;
        if(IsKeyDown(KEY_ENTER)) camera.target = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};
        if(IsKeyDown(KEY_RIGHT_SHIFT)) camera.zoom = 1;
        if(IsKeyPressed(KEY_KP_ADD)) camera.zoom += 0.1f;
        if(IsKeyPressed(KEY_KP_SUBTRACT)) camera.zoom -= 0.1f;
        if(camera.zoom<0.1f) camera.zoom=0.1f;
        
        if(IsKeyDown(KEY_ONE)){
            camera.target = (Vector2){Mercure.Pos_x ,Mercure.Pos_y };
        }
        if(IsKeyDown(KEY_THREE)){
            camera.target = (Vector2){Terre.Pos_x ,Terre.Pos_y };
        }
        if(IsKeyDown(KEY_FOUR)){
            camera.target = (Vector2){Mars.Pos_x ,Mars.Pos_y };
        }
        }


        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);


        DrawCircleGradient(Soleil.Pos_x, Soleil.Pos_y, 20, YELLOW, ORANGE);
        DrawCircle(Terre.Pos_x, Terre.Pos_y, 10, BLUE);
        DrawCircle(Mars.Pos_x, Mars.Pos_y, 10, RED);
        DrawCircle(Mercure.Pos_x, Mercure.Pos_y, 5 , WHITE);

        
        //Trace
        for(int j = 0; j<TAILLETRACE;j++){
            DrawPixel(TraceTerre[j].x, TraceTerre[j].y, BLUE);
            DrawPixel(TraceMars[j].x, TraceMars[j].y, RED);
            DrawPixel(TraceMercure[j].x, TraceMercure[j].y, WHITE);

        };
        //Trajectoire idéale
        //DrawCircleLines(Soleil.Pos_x,Soleil.Pos_y,200, SKYBLUE);
        //DrawCircleLines(Soleil.Pos_x,Soleil.Pos_y,304, ORANGE);
        //DrawCircleLines(Soleil.Pos_x,Soleil.Pos_y,78, YELLOW);



        EndMode2D();

        EndDrawing();

        actualTime = GetTime();
        deltaTime = (actualTime - previousTime)*MULTIPLICATEUR;
        deltaTime2 += actualTime - previousTime;
        previousTime = actualTime;
        //GetNextPosition(&Terre, Mars, deltaTime);
        //GetNextPosition(&Mars, Terre, deltaTime);
        
        
        TraceTerre[i].x = Terre.Pos_x;
        TraceTerre[i].y = Terre.Pos_y;
        TraceMars[i].x = Mars.Pos_x;
        TraceMars[i].y = Mars.Pos_y;
        TraceMercure[i].x = Mercure.Pos_x;
        TraceMercure[i].y = Mercure.Pos_y;
        i++;


        GetNextPosition(&Terre, &Soleil, deltaTime);
        GetNextPosition(&Mars, &Soleil, deltaTime);
        GetNextPosition(&Mercure, &Soleil, deltaTime);

        //Soleil.Pos_x += 0.1;
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
