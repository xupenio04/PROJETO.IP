#include "raylib.h"
#include "player.h"
#include "menu.h"

Player player;

int flag = 0;
int aux = 0;
int ataque = 0;
int acabou = 0;
int CurrentFrameAtaq = 0;
int corMapa = 0;

Color ColorPlayer = RAYWHITE;

void iniciarPlayer() {
    player.Img = (Texture2D) LoadTexture("assets/player.png");
    player.Width = (float) player.Img.width / 8;
    player.Height = (float) player.Img.height/4;
    player.MaxFrame = 4;
    player.CurrentFrame = 0;
    player.Position = (Vector2) {GetScreenWidth()/2-100, GetScreenHeight()/2-100};
    player.Temp = 0;
    player.FrameSpeed = 0.3;
    player.Vida = 120.0;
}


void checkTeclaPressionada() {
    flag = 0;
    Color colorPixel;
    int preto = 255;
    int i = 1;

    if(IsKeyDown(KEY_DOWN)){
      for (i = 1; i <= 4; i++) {
        colorPixel = GetImageColor(fundoMapa, player.Position.x+50, player.Position.y+90+i);
        corMapa = ColorToInt(colorPixel);
        if (corMapa != preto) {
          i--;
          break;
        }
      }
      player.Position.y += i;
      flag = 1;
    } 
    if(IsKeyDown(KEY_UP)){
      for (i = 1; i <= 4; i++) {
        colorPixel = GetImageColor(fundoMapa, player.Position.x+50, player.Position.y+90 - i);
        corMapa = ColorToInt(colorPixel);
        if (corMapa != preto) {
          i--;
          break;
        }
      }
      player.Position.y -= i;
      flag = 2;
    }
    if(IsKeyDown(KEY_RIGHT)) {
      for (i = 1; i <= 4; i++) {
        colorPixel = GetImageColor(fundoMapa, player.Position.x+50 + i, player.Position.y+90);
        corMapa = ColorToInt(colorPixel);
        if (corMapa != preto) {
          i--;
          break;
        }
      }
      player.Position.x += i;
      flag = 3;
    }
    if(IsKeyDown(KEY_LEFT)){
      for (i = 1; i <= 4; i++) {
        colorPixel = GetImageColor(fundoMapa, player.Position.x+50 - i, player.Position.y+90);
        corMapa = ColorToInt(colorPixel);
        if (corMapa != preto) {
          i--;
          break;
        }
      }
      player.Position.x -= i;
      flag = 4;
    }
    if(IsKeyDown(KEY_F)){
        ataque = 1;
        acabou = 0;
    }
}


