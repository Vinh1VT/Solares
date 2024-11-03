
#include <math.h>




typedef struct Planet_{
    float Mass;
    float Speed_x;
    float Speed_y;
    float Radius;
    float Direction;
    float Distance;
    float Pos_x;
    float Pos_y;
} Planet;


void GetNextPosition(Planet P, Planet S){
    float G = 6.74;
    float Acc = (G*S.Mass)/pow(P.Distance,2);
    P.Pos_x = (1.0/60)*Acc; //il manque les termes en cos et sin, faut trouver theta
    P.Pos_y = (1.0/60)*Acc; //tout pareil
}





