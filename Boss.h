
#ifndef BOSS
#define BOSS
#include "raylib.h" 

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
  float Vida;
  int CurrentFrameAtaq;
} Boss;

#endif
