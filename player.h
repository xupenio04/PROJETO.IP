##ifndef PLAYER
#define PLAYER

#include "raylib.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>


typedef struct{
    Rectangle FrameRec;
    Rectangle Collision;
    Texture2D Img;
    Vector2 Position;
    int MaxFrame;
    int CurrentFrame;
    float Width;
    float Height;
    float Temp;
    float FrameSpeed;
    int Life;
} Player;





#endif;


