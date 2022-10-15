#ifndef ENEMIES_H
#define ENEMIES_H

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
} Enemy;

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

extern Boss boss;
extern Enemy enemie;
extern Enemy monstro;
extern Enemy voador;

extern int estadoBoss; //se o boss n tiver atacando
extern int estadoEnemy; //se o enemy tiver atacando
extern int estadoMonstro;
extern int estadoVoador;

extern bool monstroMorreu;
extern bool enemieMorreu;
extern bool bossMorreu;
extern bool voadorMorreu;


extern Color ColorMonstro;
extern Color Colorboss;
extern Color ColorEnemy;
extern Color ColorVoador;
 

void iniciarBoss();
void iniciarEnemie();
void iniciarMonstro();
void iniciarVoador();

#endif
