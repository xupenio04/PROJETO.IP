#include<stdio.h>
#include "monstros.h"
#include "raylib.h"

float enemyColisao(Rectangle enemy, Rectangle player){
    float collision = CheckCollisionRecs(enemy, player);
    return collision;
}
