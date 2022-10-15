#ifndef PLAYER
#define PLAYER

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
} Player;

extern Player player;

extern int flag;
extern int aux;
extern int ataque;
extern int acabou;
extern int CurrentFrameAtaq;
extern int corMapa;

extern Color ColorPlayer;

void iniciarPlayer();
void checkTeclaPressionada();
#endif
