#ifndef COLISAO
#define COLISAO

#include "raylib.h"

typedef struct{
    Texture2D Img;
    Vector2 Position;
    Rectangle Collision;
    float cura;
} Coxinhas;

extern bool flagcollisionPlayerMonstro;
extern bool flagcollisionPlayerboss;
extern bool flagcollisionPlayerEnemy;
extern bool flagcollisionPlayerVoador;
extern bool ataqueConfirmado; //player ataca boss
extern bool ataqueEnemy;//player ataca enemy
extern bool ataqueBoss; //boss ataca player
extern bool contrario; //se o boss tiver ao contrario
extern bool enemyAtaca; //quando o enemy ataca
extern bool ataqueMonstro; //player ataca monstro do oculos
extern bool monstroAtaca; //monstro do oculos ataca
extern bool ataqueVoador; //player ataca voador 
extern bool voadorAtaca; 
extern bool coxinha;

extern Rectangle collisionPlayerboss;
extern Rectangle collisionPlayerEnemy;
extern Rectangle collisionPlayerMonstro;


extern int nCoxinhas;
//extern Coxinhas coxinhas[nCoxinhas];

void checaColisao();
//void checaCoxinhas();
void terminarPersonagens();
#endif
