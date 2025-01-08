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


    FILE *f = fopen("./files/Calculs_Projet.csv","r");
    Planet* TableauPlanete = parse(f,Soleil.Pos_x,Soleil.Pos_y);
    fclose(f);

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
    bool afficheNom = true;
    /* variables temporelles à mettre juste avant la boucle principale*/
    SetTargetFPS(60);
    double actualTime; //temps actuel
    double previousTime = GetTime(); //temps de début de la simulation
    double deltaTime = 0; //temps écoulé depuis le début de la simulation
    float deltaTime2 = 0;
    //Tableau des bits qui marquent l'état des planetes (affiches ou non)
    int PlaneteAffichee[8] = {1,1,1,1,1,1,1,1};

    while (!WindowShouldClose())
    {
        if(i==TAILLETRACE) i=0;

        ScreenHeight = GetScreenHeight();
        ScreenWidth = GetScreenWidth();

        camera.offset = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};

        //controle de la caméra
        if(true){
        if(IsKeyDown(KEY_UP)) camera.target.y -= 2 * (1/camera.zoom);
        if(IsKeyDown(KEY_DOWN)) camera.target.y += 2 * (1/camera.zoom);
        if(IsKeyDown(KEY_RIGHT)) camera.target.x += 2 * (1/camera.zoom);
        if(IsKeyDown(KEY_LEFT)) camera.target.x -= 2 * (1/camera.zoom);
        if(IsKeyDown(KEY_ENTER)) camera.target = (Vector2){Soleil.Pos_x,Soleil.Pos_y};
        if(IsKeyDown(KEY_RIGHT_SHIFT)) camera.zoom = 1;
        if(IsKeyPressed(KEY_KP_ADD)) camera.zoom += 0.1f;
        if(IsKeyPressed(KEY_KP_SUBTRACT)) camera.zoom -= 0.1f;
        if(camera.zoom<0.1f) camera.zoom=0.1f;
        if(IsKeyPressed(KEY_T)) afficheTrace = !afficheTrace;
        if(IsKeyPressed(KEY_N)) afficheNom = !afficheNom;

        for(int c = 0; c<8;c++){
            if(IsKeyDown(49+c)){
                camera.target = (Vector2){TableauPlanete[c].Pos_x, TableauPlanete[c].Pos_y};
            }
        }
        for(int c = 0; c<8;c++){
            if(IsKeyPressed(321+c)){
                if(PlaneteAffichee[c]){
                    liste = RemovePlanet(TableauPlanete[c].Nom, liste);
                    PlaneteAffichee[c] = 0;
                } else{
                    append(liste,&TableauPlanete[c]);
                    PlaneteAffichee[c] = 1;
                }
            }
        }
        }


        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);


        DrawCircleGradient(Soleil.Pos_x, Soleil.Pos_y, 20, YELLOW, ORANGE);
        DrawAll(liste);



        //Trace
        if(afficheTrace) DrawTrace(liste);

        if(afficheNom) DrawName(liste, &camera);


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
    }

    CloseWindow();
    freeList(liste);
    free(TableauPlanete);
    return EXIT_SUCCESS;
}
