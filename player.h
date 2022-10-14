#ifndef PLAYER
#define PLAYER

#include "raylib.h"
#include "player.h"

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

Player player;

int flag = 0;
int aux = 0;
int ataque = 0;
int acabou = 0;
int CurrentFrameAtaq = 0;

Color ColorPlayer;

void iniciarPlayer(){
  player.Img = (Texture2D) LoadTexture("assets/player.png");
    player.Width = (float) player.Img.width / 8;
    player.Height = (float) player.Img.height/4;
    player.MaxFrame = 4;
    player.CurrentFrame = 0;
    player.Position = (Vector2) {GetScreenWidth()/2-100, GetScreenHeight()/2-100};
    player.Temp = 0;
    player.FrameSpeed = 0.1;
    player.Vida = 100.0;
}

void checkTeclaPressionada(Image imageFundo){
  flag = 0;
    Color colorPixel;
    int preto = ColorToInt(BLACK);
    int corMapa;
    
    //if(corMapa != preto){
    if(IsKeyDown(KEY_DOWN)){
      colorPixel = GetImageColor(imageFundo, player.Position.x, player.Position.y+4);
      corMapa = ColorToInt(colorPixel);
      if(corMapa == preto){
        player.Position.y += 4;
        flag = 1;
      }
    } 
    if(IsKeyDown(KEY_UP)){
      colorPixel = GetImageColor(imageFundo, player.Position.x, player.Position.y - 4);
      corMapa = ColorToInt(colorPixel);
      if(corMapa == preto){
        player.Position.y -= 4;
        flag = 2;
      }
    }
    if(IsKeyDown(KEY_RIGHT)) {
      colorPixel = GetImageColor(imageFundo, player.Position.x + 4, player.Position.y);
      corMapa = ColorToInt(colorPixel);
      if(corMapa == preto){
        player.Position.x += 4;
        flag = 3;
      }
    }
    if(IsKeyDown(KEY_LEFT)){
      colorPixel = GetImageColor(imageFundo, player.Position.x - 4, player.Position.y);
      corMapa = ColorToInt(colorPixel);
      if(corMapa == preto){
        player.Position.x -= 4;
        flag = 4;
      }
    }
    if(IsKeyDown(KEY_F)){
        ataque = 1;
        acabou = 0;
    }
}
#endif