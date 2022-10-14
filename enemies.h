#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
//#include "player.h"

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

Boss boss;
Enemy enemie;
Enemy monstro;

int estadoBoss = 1; //se o boss n tiver atacando
int estadoEnemy = 3; //se o enemy tiver atacando
int estadoMonstro = 1;

Color ColorMonstro = RAYWHITE;
Color Colorboss = RAYWHITE;
Color ColorEnemy = RAYWHITE;

void iniciarBoss(){
  boss.Vida = 50.0;
    boss.Img = (Texture2D) LoadTexture("assets/boss.png");
    boss.Width = (float) boss.Img.width/7;
    boss.Height = 163.0;
    boss.MaxFrame = 5;
    boss.CurrentFrame = 0;
    boss.CurrentFrameAtaq = 0;
    boss.Position = (Vector2){ 500.0, 200.0};//boss.Position = (Vector2) {screenWidth/2-100,screenHeight/2-100};
    boss.Temp = 0;
    boss.FrameSpeed = 0.1;
}
void iniciarEnemie(){
  enemie.Vida = 50;
    enemie.Img = (Texture2D) LoadTexture("assets/enemy.png");
    enemie.Width = (float) enemie.Img.width/4;
    enemie.Height = (float) enemie.Img.height/6;
    enemie.MaxFrame = 5;
    enemie.CurrentFrame = 0;
    enemie.Position = (Vector2) {500.0, 300.0};
    enemie.Temp = 0;
    enemie.CurrentFrameAtaq = 0;
    enemie.FrameSpeed = 0.1;
}
void iniciarMonstro(){
  // essa funcao carrega a textura
    monstro.Img = (Texture2D) LoadTexture("assets/monstroOculos.png");
    monstro.Width = (float) monstro.Img.width/4;
    monstro.Height = (float) monstro.Img.height/4;
    monstro.MaxFrame = 5;
    monstro.CurrentFrame = 0;
    monstro.CurrentFrameAtaq = 0;
    monstro.Position = (Vector2) {400.0, 400.0};
    monstro.Temp = 0;
    monstro.FrameSpeed = 0.1;
    monstro.Vida = 50;
}

#endif