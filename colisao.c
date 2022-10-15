#include "raylib.h"
#include "player.h"
#include "enemies.h"
#include "colisao.h"

bool flagcollisionPlayerMonstro = false;
bool flagcollisionPlayerboss = false;
bool flagcollisionPlayerEnemy = false;
bool flagcollisionPlayerVoador = false;
bool ataqueConfirmado = false; //player ataca boss
bool ataqueEnemy = false;//player ataca enemy
bool ataqueBoss = false; //boss ataca player
bool contrario =  false; //se o boss tiver ao contrario
bool enemyAtaca = false; //quando o enemy ataca
bool ataqueMonstro = false; //player ataca monstro do oculos
bool monstroAtaca = false; //monstro do oculos ataca
bool ataqueVoador = false; //player ataca voador 
bool voadorAtaca = false; // voador ataca
bool coxinha = false;

Rectangle collisionPlayerboss;
Rectangle collisionPlayerEnemy;
Rectangle collisionPlayerMonstro;

int nCoxinhas = 6;

void checaColisao() {
    player.Temp += GetFrameTime();
    player.CurrentFrame = player.CurrentFrame % 4;
    
    player.Collision = (Rectangle) {player.Position.x, player.Position.y, 90.0, 102.0}; //CONSEGUI ESSES VALORES NO PISKEL, OLHANDO A IMAGEM
    boss.Collision = (Rectangle) {boss.Position.x, boss.Position.y, 160.0, 139.0};
    enemie.Collision = (Rectangle) {enemie.Position.x, enemie.Position.y, 90.0, 102.0};
    monstro.Collision = (Rectangle) {monstro.Position.x, monstro.Position.y, 70.0, 80.0};
    voador.Collision = (Rectangle) {voador.Position.x, voador.Position.y, 70.0, 90.0};
    
    flagcollisionPlayerVoador = CheckCollisionRecs(voador.Collision, player.Collision);
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
    if(flagcollisionPlayerVoador){
        ataqueVoador = true;
    }
    else if(!flagcollisionPlayerVoador){
        ColorVoador = RAYWHITE;
        ataqueVoador = false;
    }
}

/*
void checaCoxinhas(){
    for(int i = 0; i < nCoxinhas; i++){
        coxinha = CheckCollisionRecs(coxinhas[i].Collision, player.Collision);
        if(coxinha){ 
            if(player.Vida <= 100){
                player.Vida += coxinhas[i].cura;
            }
            coxinhas[i].Position = (Vector2) {10000.0, 10000.0};
            coxinhas[i].Collision = (Rectangle) {10000.0, 10000.0, 1.0, 1.0};
            UnloadTexture(coxinhas[i].Img);
        }
    }
}*/

void terminarPersonagens() {
    UnloadTexture(player.Img);
    UnloadTexture(boss.Img);
    UnloadTexture(enemie.Img);
    UnloadTexture(monstro.Img);
    UnloadTexture(voador.Img);
}