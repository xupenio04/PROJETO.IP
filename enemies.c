#include "raylib.h"
#include "enemies.h"

Boss boss;
Enemy enemie;
Enemy monstro;
Enemy voador;

int estadoBoss = 1; //se o boss n tiver atacando
int estadoEnemy = 3; //se o enemy tiver atacando
int estadoMonstro = 1;
int estadoVoador = 1;

bool monstroMorreu = false;
bool enemieMorreu = false;
bool bossMorreu = false;
bool voadorMorreu = false;

Color ColorMonstro = RAYWHITE;
Color Colorboss = RAYWHITE;
Color ColorEnemy = RAYWHITE;
Color ColorVoador = RAYWHITE;


void iniciarBoss() {
    boss.Vida = 600;
    boss.Img = (Texture2D) LoadTexture("assets/boss.png");
    boss.Width = (float) boss.Img.width/7;
    boss.Height = 163.0;
    boss.MaxFrame = 5;
    boss.CurrentFrame = 0;
    boss.CurrentFrameAtaq = 0;
    boss.Position = (Vector2){ 900.0, 800.0};//boss.Position = (Vector2) {screenWidth/2-100,screenHeight/2-100};
    boss.Temp = 0;
    boss.FrameSpeed = 0.3;
}

void iniciarEnemie() { 
    enemie.Vida = 300;
    enemie.Img = (Texture2D) LoadTexture("assets/enemy.png");
    enemie.Width = (float) enemie.Img.width/4;
    enemie.Height = (float) enemie.Img.height/6;
    enemie.MaxFrame = 5;
    enemie.CurrentFrame = 0;
    enemie.Position = (Vector2) {516.0, 316.0};
    enemie.Temp = 0;
    enemie.CurrentFrameAtaq = 0;
    enemie.FrameSpeed = 0.3;
}

void iniciarMonstro() {
    // essa funcao carrega a textura
    monstro.Vida = 350;
    monstro.Img = (Texture2D) LoadTexture("assets/monstroOculos.png");
    monstro.Width = (float) monstro.Img.width/4;
    monstro.Height = (float) monstro.Img.height/4;
    monstro.MaxFrame = 5;
    monstro.CurrentFrame = 0;
    monstro.CurrentFrameAtaq = 0;
    monstro.Position = (Vector2) {1484.0, 419.0};
    monstro.Temp = 0;
    monstro.FrameSpeed = 0.3;
}

void iniciarVoador(){
  voador.Vida = 250;
  voador.Img = (Texture2D) LoadTexture("assets/voador.png");
  voador.Width = 94.0;
  voador.Height = (float) voador.Img.height/4;
  voador.MaxFrame = 5;
  voador.CurrentFrame = 0;
  voador.CurrentFrameAtaq = 0;
  voador.Position = (Vector2) {300.0, 778.0};
  voador.Temp = 0;
  voador.FrameSpeed = 0.1;
}