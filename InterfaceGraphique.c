#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "ModelePhysique.h"
#include "Parsing.h"



#define MULTIPLICATEUR 1

int main(void)
{
    int ScreenWidth = GetScreenWidth();
    int ScreenHeight = GetScreenHeight();



    /*Planet Soleil ={
    .Mass = 1E25,
    .Pos_x= (float)ScreenWidth/2,
    .Pos_y= (float)ScreenHeight/2,
    .Vitesse_x = 0,
    .Vitesse_y = 0
    };*/

    FILE *f;
    if(!(f = fopen("./files/Calculs_Projet.csv","r"))){
        fprintf(stderr,"erreur d'ouverture du fichier");
    };
    Planet* TableauPlanete = parse(f,(float)ScreenWidth/2,(float)ScreenHeight/2);
    fclose(f);

    ListPlanet* liste = newListe(TableauPlanete+1, true);
    for(int t = 2; t<9; t++){
        append(liste,&TableauPlanete[t],true);
    }
    add_asteroide(2500,500,800,&TableauPlanete[0],liste);

    InitWindow(ScreenWidth, ScreenHeight, "Solares");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    //Caméra
    Camera2D camera;
    camera.zoom = 1.0f;
    camera.target = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};


    //Traceur
    int i = 0;
    bool afficheTrace = false;
    bool afficheNom = true;
    /* variables temporelles à mettre juste avant la boucle principale*/
    SetTargetFPS(60);
    double actualTime; //temps actuel
    double previousTime = GetTime(); //temps de début de la simulation
    double deltaTime = 0; //temps écoulé depuis le début de la simulation
    //Tableau des bits qui marquent l'état des planetes (affiches ou non)
    int PlaneteAffichee[8] = {1,1,1,1,1,1,1,1};

    while (!WindowShouldClose()){
        if(i==TAILLETRACE) i=0;

        ScreenHeight = GetScreenHeight();
        ScreenWidth = GetScreenWidth();

        camera.offset = (Vector2){(float)ScreenWidth/2,(float)ScreenHeight/2};

        //controle de la caméra
        {
            if(IsKeyDown(KEY_UP)) camera.target.y -= 2 * (1/camera.zoom);
            if(IsKeyDown(KEY_DOWN)) camera.target.y += 2 * (1/camera.zoom);
            if(IsKeyDown(KEY_RIGHT)) camera.target.x += 2 * (1/camera.zoom);
            if(IsKeyDown(KEY_LEFT)) camera.target.x -= 2 * (1/camera.zoom);
            if(IsKeyDown(KEY_ENTER)) camera.target = (Vector2){TableauPlanete[0].Pos_x,TableauPlanete[0].Pos_y};
            if(IsKeyDown(KEY_RIGHT_SHIFT)) camera.zoom = 1;
            if(IsKeyPressed(KEY_KP_ADD)) camera.zoom += 0.1f;
            if(IsKeyPressed(KEY_KP_SUBTRACT)) camera.zoom -= 0.1f;
            if(camera.zoom<0.1f) camera.zoom=0.1f;
            if(IsKeyPressed(KEY_T)) afficheTrace = !afficheTrace;
            if(IsKeyPressed(KEY_N)) afficheNom = !afficheNom;

            for(int c = 0; c<8;c++){
                if(IsKeyDown(49+c)){
                    camera.target = (Vector2){TableauPlanete[c+1].Pos_x, TableauPlanete[c+1].Pos_y};
                }
            }
            for(int c = 0; c<8;c++){
                if(IsKeyPressed(321+c)){
                    if(PlaneteAffichee[c+1]){
                        liste = RemovePlanet(TableauPlanete[c+1].Nom, liste);
                        PlaneteAffichee[c+1] = 0;
                    } else{
                        append(liste,&TableauPlanete[c+1],true);
                        PlaneteAffichee[c] = 1;
                    }
                }
            }
        }


        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        DrawCircleGradient(TableauPlanete[0].Pos_x,TableauPlanete[0].Pos_y,TableauPlanete[0].Taille,YELLOW,ORANGE);
        DrawAll(liste);



        //Trace
        if(afficheTrace) DrawTrace(liste);

        if(afficheNom) DrawName(liste, &camera);


        EndMode2D();

        EndDrawing();

        actualTime = GetTime();
        deltaTime = (actualTime - previousTime)*MULTIPLICATEUR;
        previousTime = actualTime;



        UpdateTrace(liste, i);
        i++;
        GetNextVitesseAll(liste,&TableauPlanete[0],deltaTime);

        GetNextPositionAll(liste, deltaTime);
        //DrawFPS(TableauPlanete[0].Pos_x,TableauPlanete[0].Pos_y);
    }

    CloseWindow();
    freeList(liste);
    free(TableauPlanete);
    return EXIT_SUCCESS;
}
