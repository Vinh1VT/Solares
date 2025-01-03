#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "ModelePhysique.h"
#include "Parsing.h"



#define MULTIPLICATEUR 1

int main(void)
{
    int ScreenWidth = 1000;
    int ScreenHeight = 1000;



    Planet Soleil ={
    .Mass = 1E25,
    .Pos_x= (float)ScreenWidth/2,
    .Pos_y= (float)ScreenHeight/2,
    .Vitesse_x = 0,
    .Vitesse_y = 0
    };

    /*Planet Terre ={
    .Mass = 1,
    .Pos_x = Soleil.Pos_x + 200,
    .Pos_y = Soleil.Pos_y,
    .Vitesse_x = 0,
    .Vitesse_y = -58,
    .couleur = BLUE,
    .Taille = 10
    };

    Planet Mars ={
    .Mass = 0.1,
    .Pos_x = Soleil.Pos_x+304,
    .Pos_y = Soleil.Pos_y,
    .Vitesse_x = 0,
    .Vitesse_y = -47,
    .couleur = RED,
    .Taille = 10
    };

    Planet Mercure= {
        .Pos_x = Soleil.Pos_x+78,
        .Pos_y = Soleil.Pos_y,
        .Vitesse_x = 0,
        .Vitesse_y = -95,
        .couleur = WHITE,
        .Taille =5
    };

    Planet Venus={
        .Pos_x = Soleil.Pos_x + 143,
        .Pos_y = Soleil.Pos_y,
        .Vitesse_x = 0,
        .Vitesse_y = -70,
        .couleur = ORANGE,
        .Taille = 5
    };*/

    FILE *f = fopen("./files/Calculs_Projet.csv","r");
    Planet* TableauPlanete = parse(f,Soleil.Pos_x,Soleil.Pos_y);
    fclose(f);

    /*ListPlanet liste ={
        .start = &liste,
        .P = Terre,
        .suivant = NULL,
        .couleur = BLUE,
        .Taille = 10
    };*/

    ListPlanet* liste = newListe(TableauPlanete);
    for(int t = 1; t<8; t++){
        append(liste,&TableauPlanete[t]);
    }


    InitWindow(ScreenWidth, ScreenHeight, "Simulation");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    //Caméra
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.target = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};


    //Traceur
    int i = 0;
    bool afficheTrace = true;
    /* variables temporelles à mettre juste avant la boucle principale*/
    SetTargetFPS(60);
    double actualTime; //temps actuel
    double previousTime = GetTime(); //temps de début de la simulation
    double deltaTime = 0; //temps écoulé depuis le début de la simulation
    float deltaTime2 = 0;

    while (!WindowShouldClose())
    {
        if(i==TAILLETRACE) i=0;

        ScreenHeight = GetScreenHeight();
        ScreenWidth = GetScreenWidth();

        camera.offset = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};

        //controle de la caméra
        if(true){
        if(IsKeyDown(KEY_UP)) camera.target.y -= 2 + (1-camera.zoom);
        if(IsKeyDown(KEY_DOWN)) camera.target.y += 2+ (1-camera.zoom);
        if(IsKeyDown(KEY_RIGHT)) camera.target.x += 2+ (1-camera.zoom);
        if(IsKeyDown(KEY_LEFT)) camera.target.x -= 2+ (1-camera.zoom);
        if(IsKeyDown(KEY_ENTER)) camera.target = (Vector2){Soleil.Pos_x,Soleil.Pos_y};
        if(IsKeyDown(KEY_RIGHT_SHIFT)) camera.zoom = 1;
        if(IsKeyPressed(KEY_KP_ADD)) camera.zoom += 0.1f;
        if(IsKeyPressed(KEY_KP_SUBTRACT)) camera.zoom -= 0.1f;
        if(camera.zoom<0.1f) camera.zoom=0.1f;
        if(IsKeyPressed(KEY_T)) afficheTrace = !afficheTrace;

        for(int c = 0; c<=8;c++){
            if(IsKeyDown(49+c)){
                camera.target = (Vector2){TableauPlanete[c].Pos_x, TableauPlanete[c].Pos_y};
            }
        }
        }

        //ListPlanet* ptr = liste;
        /*while(ptr !=NULL){
            printf("%s\n",ptr->P->Nom);
            ptr = ptr->suivant;
            }  */


        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);


        DrawCircleGradient(Soleil.Pos_x, Soleil.Pos_y, 20, YELLOW, ORANGE);
        DrawAll(liste);



        //Trace
        if(afficheTrace) DrawTrace(liste);
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



        UpdateTrace(liste, i);
        i++;
        GetNextVitesseAll(liste,&Soleil,deltaTime);

        GetNextPositionAll(liste, deltaTime);
        //Soleil.Pos_x += 0.1;
    }

    CloseWindow();
    freeList(liste);
    free(TableauPlanete);
    return EXIT_SUCCESS;
}
