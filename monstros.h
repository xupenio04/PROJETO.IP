#ifndef ENEMIES
#define ENEMIES
#include "raylib.h"

typedef struct{
  bool active;
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
} Enemy;

float enemyColisao(Rectangle enemy, Rectangle player);

#endif
