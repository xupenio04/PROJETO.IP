#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "enemies.h"
#include "menu.h"
#include "colisao.h"

int main(){
    iniciarJogo();
    iniciarPlayer();
    iniciarBoss();
    iniciarEnemie();
    iniciarMonstro();
    Coxinhas coxinhas[nCoxinhas];
    for(int i = 0; i < nCoxinhas; i++){
        coxinhas[i].Img = (Texture2D) LoadTexture("assets/coxinha.png");
        coxinhas[i].Position = (Vector2) {300.0 + i*230.0, 300.0 + i*15.0};
        coxinhas[i].Collision = (Rectangle) {coxinhas[i].Position.x, coxinhas[i].Position.y, coxinhas[i].Img.width - 40, coxinhas[i].Img.height - 40 };
        coxinhas[i].cura = 20;
    }
    carregarTelas();
    carregarVida();
    carregarBotoes();

    while(!WindowShouldClose()){
        UpdateMusicStream(audio_menu);
        //pegar a posição do mouse
        mouse_move = GetMousePosition();
        Rectangle mouse_aux = {mouse_move.x, mouse_move.y, 20, 20};
        mouse = mouse_aux;

        BeginDrawing();
            //abrindo tela inicial
            if(!stopTelaInicial) abrirTelaInicial();
            checaBotao();
        EndDrawing();

        //abrindo Menu
        if(click_menu && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            abreMenu();
        }

        //abrindo jogo
        if(click_start && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            abrePreJogo();
        }

        //mapa do jogo
        while(stopTelaInicial && !jogo_pausado){
            BeginDrawing();
                ClearBackground(BLACK);
                DrawTexture(mapa, 0, 0, WHITE); 

                if(acabou == 1){
                    ataque = 0;
                    CurrentFrameAtaq = 4; //comecando um antes por causa da incrementacao
                }
                
                checkTeclaPressionada(carregarFundoMapa());
                
                ///aqui vamos checar se o player passou pelas coxinhas
                for(int i = 0; i < nCoxinhas; i++){
                    coxinha = CheckCollisionRecs(coxinhas[i].Collision, player.Collision);
                    if(coxinha){ //&& abs(player.Position.x - coxinhas[i].Position.x) < 20 && abs(player.Position.x - coxinhas[i].Position.y) < 20){
                    if(player.Vida <= 100){
                        player.Vida += coxinhas[i].cura;
                    }
                    coxinhas[i].Position = (Vector2) {10000.0, 10000.0};
                    coxinhas[i].Collision = (Rectangle) {10000.0, 10000.0, 1.0, 1.0};
                    UnloadTexture(coxinhas[i].Img);
                    }
                }

                checaColisao();

                int thresholdWidth = player.Position.x;
                int thresholdHeight = player.Position.y;

                if(monstro.Position.x > thresholdWidth ){
                    monstro.Position.x -= 2.0;
                    if(monstro.Width > 0){
                        monstro.Width *= -1;
                    }
                    } else if(monstro.Position.x < thresholdWidth){ 
                        monstro.Position.x += 2.0;
                        if(monstro.Width < 0){
                        monstro.Width *= -1;
                        } 
                    } 

                    if(monstro.Position.y > thresholdHeight){
                    monstro.Position.y -= 2.0;
                    } else if(monstro.Position.y < thresholdHeight) {
                        monstro.Position.y += 2.0;
                    }
                    if(monstro.Position.x == thresholdWidth && monstro.Position.y == thresholdHeight){
                    monstroAtaca = true;
                    estadoMonstro = 3;
                }
                //agora e so repetir o codigo do monstro para o enemie
                if(enemie.Position.x > thresholdWidth ){
                    enemie.Position.x -= 2.0;
                    if(enemie.Width > 0){
                        enemie.Width *= -1;
                    }
                } else if(enemie.Position.x < thresholdWidth){ 
                    enemie.Position.x += 2.0;
                    if(enemie.Width < 0){
                        enemie.Width *= -1;
                    } 
                } 

                if(enemie.Position.y > thresholdHeight){
                    enemie.Position.y -= 2.0;
                } else if(enemie.Position.y < thresholdHeight) {
                    enemie.Position.y += 2.0;
                }
                if(enemie.Position.x == thresholdWidth && enemie.Position.y == thresholdHeight){
                    enemyAtaca = true;
                    estadoEnemy = 4;
                }

                ///comeca o do boss///////////////////////////////////////////////////////
    
                /*
                if(!contrario){
                thresholdWidth = player.Position.x - 100; //pra ele poder ficar na frente do player, muda qd ele ta ao contrario
                thresholdHeight = player.Position.y - 70;
                }
                else if(contrario){
                thresholdWidth = player.Position.x + 40;
                thresholdHeight = player.Position.y - 70;
                }*/
    
                if(boss.Position.x > thresholdWidth){
                boss.Position.x -= 1;
                    if(boss.Width > 0){
                    boss.Width *= -1;
                    contrario = !contrario;
                    }
                } 
                else if(boss.Position.x < thresholdWidth) { 
                boss.Position.x += 1;
                if(boss.Width < 0){
                    boss.Width *= -1;
                    contrario = !contrario;
                } 
                }

    
                if(boss.Position.y > thresholdHeight){
                boss.Position.y -= 1.0;
                } else if(boss.Position.y < thresholdHeight) {
                    boss.Position.y += 1.0;
                }
                
                if(boss.Position.x == thresholdWidth && boss.Position.y == thresholdHeight){
                //boss.CurrentFrame = 6; 
                ataqueBoss = true;
                
                }

    
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(mapa, 0, 0, RAYWHITE);
                    
                for(int i = 0; i < nCoxinhas; i++){
                    DrawTexture(coxinhas[i].Img, coxinhas[i].Position.x, coxinhas[i].Position.y, RAYWHITE);
                    
                }  
  
    
                boss.Temp += GetFrameTime();
                if(!ataqueBoss){
                    if(boss.Temp > boss.FrameSpeed){
                        boss.Temp = 0;
                        if(contrario){
                        if(boss.CurrentFrame < 0){
                            boss.CurrentFrame = 6;
                        }
                        boss.CurrentFrame -= 1;
                        }
                        else if(!contrario){
                        boss.CurrentFrame += 1;
                        }
                    }
                    boss.CurrentFrame = boss.CurrentFrame % 6; //mexer nessa variavel para deixar o andar do boss menos feio
                }else if(ataqueBoss){
                    if(!contrario){
                        if(boss.Temp > boss.FrameSpeed){
                        boss.Temp = 0;
                        boss.CurrentFrameAtaq += 1;
                        }
                        if(boss.CurrentFrameAtaq >= 7){
                        ataqueBoss = false;
                        boss.CurrentFrameAtaq = 0;
                        }
                    }
                    else if(contrario){
                        if(boss.Temp > boss.FrameSpeed){
                        boss.CurrentFrameAtaq -= 1;
                        boss.Temp = 0; //se tiver o contrario o ataque precisa percorrer ao contrario a imagem
                        }
                        if(boss.CurrentFrameAtaq < 0){
                        boss.CurrentFrameAtaq = 6;
                        ataqueBoss = false;
                        }
                    }
                }
    
    
                if(ataqueBoss){
                    player.Vida -= 0.5;
                    estadoBoss = 2;
                    ColorPlayer = GREEN;
                    boss.FrameRec = (Rectangle) {boss.Width *  boss.CurrentFrameAtaq, boss.Height * estadoBoss, boss.Width, boss.Height};
                }
                else{
                    estadoBoss = 1;
                    ColorPlayer = RAYWHITE;
                    boss.FrameRec = (Rectangle) {boss.Width *  boss.CurrentFrame, boss.Height * estadoBoss, boss.Width, boss.Height};
                }
  
                DrawTextureRec(boss.Img, boss.FrameRec, boss.Position, Colorboss);    
  
                if(boss.Vida <= 0){
                    estadoBoss = 3;
                    boss.Temp = 0;
                    boss.CurrentFrame = 0;
                    //boss.FrameSpeed = 8;
                    while(boss.CurrentFrame !=5){
                    boss.Temp += GetFrameTime();
                    if(boss.Temp > boss.FrameSpeed){
                        boss.Temp = 0;
                        boss.CurrentFrame += 1;
                
                    }
                    boss.FrameRec = (Rectangle) {boss.Width *  boss.CurrentFrame, boss.Height * estadoBoss, boss.Width, boss.Height};
                    DrawTextureRec(boss.Img, boss.FrameRec, boss.Position, Colorboss); 
                    //WaitTime(10);
                    }
                    boss.Position = (Vector2) {12000.0, 12000.0};
                    boss.Collision = (Rectangle) {12000.0, 12000.0, 1.0, 1.0};
                    //UnloadTexture(boss.Img);
                }
    
    
                ///aqui comeca as coisas do enemy 
                enemie.Temp += GetFrameTime();
                if(!enemyAtaca){
                    if(enemie.Temp > enemie.FrameSpeed){
                    enemie.Temp = 0;
                    enemie.CurrentFrame += 1;
                    }
                }
                else if(enemyAtaca){
                    if(enemie.Temp > enemie.FrameSpeed){
                    enemie.Temp = 0;
                    enemie.CurrentFrameAtaq += 1;
                    player.Vida -= 0.5;
                    if(enemie.CurrentFrameAtaq >= 4){
                        enemyAtaca = false;
                        enemie.CurrentFrameAtaq = 0;
                    }
                    }
                }
                enemie.CurrentFrame = enemie.CurrentFrame % 4;

                if(enemyAtaca){
                    estadoEnemy = 4;
                    ColorPlayer = DARKGREEN;
                    enemie.FrameRec = (Rectangle) {enemie.Width *  enemie.CurrentFrameAtaq, enemie.Height * estadoEnemy, enemie.Width, enemie.Height};
                }
                else if(!enemyAtaca){
                    estadoEnemy = 3;
                    enemie.FrameRec = (Rectangle) {enemie.Width *  enemie.CurrentFrame, enemie.Height * estadoEnemy, enemie.Width, enemie.Height};
                    //ColorPlayer = RAYWHITE;    
                }
  
                //aqui comeca as coisas do monstro
                monstro.Temp += GetFrameTime();
                if(!monstroAtaca){
                    if(monstro.Temp > monstro.FrameSpeed){
                    monstro.Temp = 0;
                    monstro.CurrentFrame += 1;
                    }
                }
                else if(monstroAtaca){
                    if(monstro.Temp > monstro.FrameSpeed){
                    monstro.Temp = 0;
                    monstro.CurrentFrameAtaq += 1;
                    player.Vida -= 0.5;
                    if(monstro.CurrentFrameAtaq >= 4){
                        monstroAtaca = false;
                        monstro.CurrentFrameAtaq = 0;
                    }
                    }
                }
                monstro.CurrentFrame = monstro.CurrentFrame % 4;

                if(monstroAtaca){
                    estadoMonstro = 2;
                    ColorPlayer = LIME;
                    monstro.FrameRec = (Rectangle) {monstro.Width *  monstro.CurrentFrameAtaq, monstro.Height * estadoMonstro, monstro.Width, monstro.Height};
                }
                else if(!monstroAtaca){
                    estadoMonstro = 1;
                    monstro.FrameRec = (Rectangle) {monstro.Width *  monstro.CurrentFrame, monstro.Height * estadoMonstro, monstro.Width, monstro.Height};
                    //ColorPlayer = RAYWHITE;    
                } 


                //movimentacao do player
                if(flag > 0 && flag <= 4){
                    ataqueConfirmado = false;
                    ataqueEnemy = false;
                    ataqueMonstro = false;
                    Colorboss = RAYWHITE;
                    ColorEnemy = RAYWHITE;
                    ColorMonstro = RAYWHITE;


                    if(player.Temp > player.FrameSpeed){
                        player.Temp = 0;
                        player.CurrentFrame += 1;
                    }
                    player.FrameRec  = (Rectangle) { player.Width * player.CurrentFrame , player.Height*(flag-1), player.Width, player.Height};
                    DrawTextureRec (player.Img,  player.FrameRec , player.Position , RAYWHITE);
                    aux = player.Height*(flag-1);

                }else{ // player fica parado
                    if(ataque == 0){
                        ataqueConfirmado = false;
                        ataqueEnemy = false;
                        ataqueMonstro = false;
                        Colorboss = RAYWHITE;
                        ColorEnemy = RAYWHITE;
                        ColorMonstro = RAYWHITE;
                        player.FrameRec  = (Rectangle) { player.Width * 4, aux , player.Width, player.Height};
                        DrawTextureRec (player.Img,  player.FrameRec , player.Position, RAYWHITE);
                    
                    }else{
                        if(player.Temp > player.FrameSpeed){
                            player.Temp = 0;
                            CurrentFrameAtaq++;
                        }

                        if(ataqueConfirmado){
                            Colorboss = RED;
                            boss.Vida -= 0.9; //coloquei aqui pq se n ele vai passar varias vezes pela condicao
                            //tirando mais dano do q deveria, ou nao kk
                        }
                        if(ataqueEnemy){
                            ColorEnemy = RED;
                            enemie.Vida -= 0.9;
                        }
                        
                        if(!ataqueConfirmado){
                            Colorboss = RAYWHITE;
                        }
                        if(!ataqueEnemy){
                            ColorEnemy = RAYWHITE;
                        }
                        if(ataqueMonstro){
                            ColorMonstro = RED;
                            monstro.Vida -= 0.9;
                        }
                        if(!ataqueMonstro){
                            ColorMonstro = RAYWHITE;
                        }

                        player.FrameRec = (Rectangle) { player.Width * CurrentFrameAtaq, aux, player.Width, player.Height};
                        DrawTextureRec(player.Img, player.FrameRec, player.Position, RAYWHITE);
                        //a ideia e que ele passe nessa condicao 3 vezes pra concluir a animacao de ataque, usando as flags p/ isso
                        if(CurrentFrameAtaq > 7){
                            acabou = 1;
                        }

                    }
                }

                DrawTextureRec(monstro.Img, monstro.FrameRec, monstro.Position, ColorMonstro);
                //vamos ver se o monstro tbm n morreu pra fazer a animacao
                if(monstro.Vida <= 0){
                    estadoMonstro = 3;
                    monstro.Temp = 0;
                    monstro.CurrentFrame = 0;
                    //boss.FrameSpeed = 8;

                    while(monstro.CurrentFrame !=5){
                    monstro.Temp += GetFrameTime();
                    if(monstro.Temp > monstro.FrameSpeed){
                        monstro.Temp = 0;
                        monstro.CurrentFrame += 1;
                
                    }
                    monstro.FrameRec = (Rectangle) {monstro.Width *  monstro.CurrentFrame, monstro.Height * estadoMonstro, monstro.Width, monstro.Height};
                    DrawTextureRec(monstro.Img, monstro.FrameRec, monstro.Position, ColorMonstro); 
                    //WaitTime(10);
                    }
                    monstro.Position = (Vector2) {12000.0, 12000.0};
                    monstro.Collision = (Rectangle) {12000.0, 12000.0, 1.0, 1.0};
                    //UnloadTexture(monstro.Img);
                }  
                DrawTextureRec (enemie.Img, enemie.FrameRec, enemie.Position, ColorEnemy);
                //vendo se o enemie n morreu pra poder fazer a animacao de morte
                if(enemie.Vida <= 0){
                    estadoEnemy = 5;
                    enemie.Temp = 0;
                    enemie.CurrentFrame = 0;
                    //boss.FrameSpeed = 8;
                    while(enemie.CurrentFrame !=5){
                    enemie.Temp += GetFrameTime();
                    if(enemie.Temp > enemie.FrameSpeed){
                        enemie.Temp = 0;
                        enemie.CurrentFrame += 1;
                
                    }
                    enemie.FrameRec = (Rectangle) {enemie.Width *  enemie.CurrentFrame, enemie.Height * estadoEnemy, enemie.Width, enemie.Height};
                    DrawTextureRec(enemie.Img, enemie.FrameRec, enemie.Position, ColorEnemy); 
                    //WaitTime(10);
                    }
                    enemie.Position = (Vector2) {12000.0, 12000.0};
                    enemie.Collision = (Rectangle) {12000.0, 12000.0, 1.0, 1.0};
                    //UnloadTexture(enemie.Img);
                }

                Color colorVida = RAYWHITE;
                if(player.Vida >=120){
                    currentLife = 0;
                }
                else if(player.Vida >=100 && player.Vida <120){
                    currentLife = 1;
                }
                else if(player.Vida >=80 && player.Vida <100){
                    currentLife = 2;
                }
                else if(player.Vida >=60 && player.Vida <80){
                    currentLife = 3;
                }
                else if(player.Vida >=40 && player.Vida <60){
                    currentLife = 4;
                }
                else if(player.Vida >=20 && player.Vida <40){
                    currentLife = 5;
                }
                else{
                    colorVida = WHITE;
                }
                rec = (Rectangle) { 0.0, lifeHeight * currentLife, lifeWidth, lifeHeight};
                DrawTextureRec (imglife, rec , posicaoVida, colorVida);
	
                if(IsKeyPressed(KEY_ENTER)) jogo_pausado = 1;
            EndDrawing();
        
            while(jogo_pausado){
                BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTexture(pause, 0, 0, WHITE);
                    if(IsKeyPressed(KEY_ENTER)) jogo_pausado = 0;
                EndDrawing();
            }
            if(IsKeyPressed(KEY_SPACE)) stopTelaInicial = 0; //volta p telaInicial
            
        }
    }

    terminar();
    UnloadTexture(coxinhas[0].Img);
    UnloadTexture(coxinhas[1].Img);
    UnloadTexture(coxinhas[2].Img);
    return 0;
}