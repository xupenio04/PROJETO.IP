#ifndef COLISAO
#define COLISAO

#include "raylib.h"
#include "colisao.h"
#include "player.h"
#include "enemies.h"

typedef struct{
    Texture2D Img;
    Vector2 Position;
    Rectangle Collision;
    int cura;
} Coxinhas;

bool flagcollisionPlayerMonstro = false;
bool flagcollisionPlayerboss = false;
bool flagcollisionPlayerEnemy = false;
bool ataqueConfirmado = false; //player ataca boss
bool ataqueEnemy = false;//player ataca enemy
bool ataqueBoss = false; //boss ataca player
bool contrario =  false; //se o boss tiver ao contrario
bool enemyAtaca = false; //quando o enemy ataca
bool ataqueMonstro = false; //player ataca monstro do oculos
bool monstroAtaca = false; //monstro do oculos ataca
bool coxinha = false;

Rectangle collisionPlayerboss;
Rectangle collisionPlayerEnemy;
Rectangle collisionPlayerMonstro;

int nCoxinhas = 3;
void checaColisao(){
     player.Temp += GetFrameTime();
    player.CurrentFrame = player.CurrentFrame % 4;
    player.Collision = (Rectangle) {player.Position.x, player.Position.y, 90.0, 102.0}; //CONSEGUI ESSES VALORES NO PISKEL, OLHANDO A IMAGEM
    boss.Collision = (Rectangle) {boss.Position.x, boss.Position.y, 160.0, 139.0};
    enemie.Collision = (Rectangle) {enemie.Position.x, enemie.Position.y, 90.0, 102.0};
    monstro.Collision = (Rectangle) {monstro.Position.x, monstro.Position.y, 70.0, 80.0};
    flagcollisionPlayerMonstro = CheckCollisionRecs(monstro.Collision, player.Collision);
    flagcollisionPlayerboss  = CheckCollisionRecs(boss.Collision, player.Collision);
    flagcollisionPlayerEnemy = CheckCollisionRecs(enemie.Collision, player.Collision);

    if(flagcollisionPlayerboss){
        //Colorboss = RED;
        //ColorPlayer = RED;
        ataqueConfirmado = true;
        collisionPlayerboss = GetCollisionRec(boss.Collision, player.Collision);
    }
    if(flagcollisionPlayerEnemy){
        ataqueEnemy = true;
        collisionPlayerEnemy = GetCollisionRec(enemie.Collision, player.Collision);
    }
    if(!flagcollisionPlayerboss){
        Colorboss = RAYWHITE; 
        ataqueConfirmado = false;
    }
    if(!flagcollisionPlayerEnemy){
        ColorEnemy = RAYWHITE;
        ataqueEnemy = false;
    }
    if(flagcollisionPlayerMonstro){
        ataqueMonstro = true;
        collisionPlayerMonstro = GetCollisionRec(monstro.Collision, player.Collision);
    }
    else if(!flagcollisionPlayerMonstro){
        ColorMonstro = RAYWHITE;
        ataqueMonstro = false;
    }

}

#endif