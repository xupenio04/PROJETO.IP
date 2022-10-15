#include <stdio.h>
#include <string.h> 
#include "raylib.h"
#include "menu.h"
#include "colisao.h"
#include "player.h"
#include "enemies.h"

int main(){
    iniciarJogo();
    iniciarPlayer();
    iniciarBoss();
    iniciarEnemie();
    iniciarMonstro();
    iniciarVoador();
    carregarTelas();
    carregarVida();
    carregarBotoes();
    carregarFundoMapa();

    Coxinhas coxinhas[nCoxinhas];
    for(int i = 0; i < nCoxinhas; i++){
        coxinhas[i].Img = (Texture2D) LoadTexture("assets/coxinha.png");

        if(i==0) coxinhas[i].Position = (Vector2) {1200.0, 775.0};
        else if(i == 1) coxinhas[i].Position = (Vector2) {1500.0, 735.0};
        else if(i==2) coxinhas[i].Position = (Vector2) {1200.0, 260.0};
        else if(i==3) coxinhas[i].Position = (Vector2) {364.0, 788.0};
        else if(i==4) coxinhas[i].Position = (Vector2) {320.0, 280.0};
        else if(i==5) coxinhas[i].Position = (Vector2) {556.0, 450.0};

        coxinhas[i].Collision = (Rectangle) {coxinhas[i].Position.x, coxinhas[i].Position.y, coxinhas[i].Img.width - 40, coxinhas[i].Img.height - 40 };
        coxinhas[i].cura = 40;
    }

    while(!WindowShouldClose()){
        UpdateMusicStream(audio_menu);
        //pegar a posição do mouse
        mouse_move = GetMousePosition();
        Rectangle mouse_aux = {mouse_move.x, mouse_move.y, 20, 20};
        mouse = mouse_aux;
        
        //abrindo tela inicial
        BeginDrawing();   
            if(!stopTelaInicial) abrirTelaInicial();
            checaBotao();
        EndDrawing();

        //abrindo Menu
        if(click_menu && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) abreMenu();
        //abrindo jogo
        if(click_start && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) abrePreJogo();
        
        //mapa do jogo
        while(stopTelaInicial && !jogo_pausado && !tela_gameover && !tela_gamewin){
            BeginDrawing();
                ClearBackground(BLACK);
                DrawTexture(mapa, 0, 0, WHITE); 

                ColorPlayer = RAYWHITE;
                if(player.Vida > 120.0) player.Vida = 120.0;

                if(acabou == 1){
                    ataque = 0;
                    CurrentFrameAtaq = 4; //comecando um antes por causa da incrementacao
                }

                checkTeclaPressionada(); //checa movimento do player
                //checaCoxinhas(); //checa se player passou pelas coxinhas
                for(int i = 0; i < nCoxinhas; i++){
                    coxinha = CheckCollisionRecs(coxinhas[i].Collision, player.Collision);
                    if(coxinha){ 
                        if(player.Vida <= 120){
                            player.Vida += coxinhas[i].cura;
                        }
                        coxinhas[i].Position = (Vector2) {10000.0, 10000.0};
                        coxinhas[i].Collision = (Rectangle) {10000.0, 10000.0, 1.0, 1.0};
                        UnloadTexture(coxinhas[i].Img);
                    }
                }
                checaColisao(); //checa colisoes

                int thresholdWidth = player.Position.x;
                int thresholdHeight = player.Position.y;

                //---------monstro
                if(monstro.Position.x > thresholdWidth ){
                    monstro.Position.x -= 1.8;
                    if(monstro.Width > 0){
                        monstro.Width *= -1;
                    }
                    } else if(monstro.Position.x < thresholdWidth){ 
                        monstro.Position.x += 1.8;
                        if(monstro.Width < 0){
                        monstro.Width *= -1;
                        } 
                    } 

                    if(monstro.Position.y > thresholdHeight){
                    monstro.Position.y -= 1.8;
                    } else if(monstro.Position.y < thresholdHeight) {
                        monstro.Position.y += 1.8;
                    }
                    if(monstro.Position.x == thresholdWidth && monstro.Position.y == thresholdHeight){
                    monstroAtaca = true;
                    estadoMonstro = 3;
                }

                //---------enemie
                if(enemie.Position.x > thresholdWidth ){
                    enemie.Position.x -= 1.0;
                    if(enemie.Width > 0){
                        enemie.Width *= -1;
                    }
                } else if(enemie.Position.x < thresholdWidth){ 
                    enemie.Position.x += 1.0;
                    if(enemie.Width < 0){
                        enemie.Width *= -1;
                    } 
                } 

                if(enemie.Position.y > thresholdHeight){
                    enemie.Position.y -= 1.0;
                } else if(enemie.Position.y < thresholdHeight) {
                    enemie.Position.y += 1.0;
                }
                if(enemie.Position.x == thresholdWidth && enemie.Position.y == thresholdHeight){
                    enemyAtaca = true;
                    estadoEnemy = 4;
                }

                //---------voador
                if(voador.Position.x > thresholdWidth ){
                    voador.Position.x -= 2.5;
                    if(voador.Width > 0){
                        voador.Width *= -1;
                    }
                } else if(voador.Position.x < thresholdWidth){ 
                    voador.Position.x += 2.5;
                    if(voador.Width < 0){
                      voador.Width *= -1;
                    } 
                } 

                if(voador.Position.y > thresholdHeight){
                  voador.Position.y -= 2.5;
                } else if(voador.Position.y < thresholdHeight) {
                    voador.Position.y += 2.5;
                }
                if(voador.Position.x == thresholdWidth && voador.Position.y == thresholdHeight){
                  voadorAtaca = true;
                  estadoVoador = 2;
                }

                //-------------boss
                if(boss.Position.x > thresholdWidth){
                    boss.Position.x -= 0.5;
                    if(boss.Width > 0){
                    boss.Width *= -1;
                    contrario = !contrario;
                    }
                } 
                else if(boss.Position.x < thresholdWidth) { 
                    boss.Position.x += 0.5;
                    if(boss.Width < 0){
                        boss.Width *= -1;
                        contrario = !contrario;
                    } 
                }

    
                if(boss.Position.y > thresholdHeight){
                boss.Position.y -= 0.5;
                } else if(boss.Position.y < thresholdHeight) {
                    boss.Position.y += 0.5;
                }
                
                if(boss.Position.x == thresholdWidth && boss.Position.y == thresholdHeight){
                    //boss.CurrentFrame = 6; 
                    ataqueBoss = true;
                }
                    
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
                    ataqueBoss = false;
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
                    bossMorreu = true;
                    ColorPlayer = RAYWHITE;
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


                voador.Temp += GetFrameTime();
                if(!voadorAtaca){
                  if(voador.Temp > voador.FrameSpeed){
                    voador.Temp = 0;
                    voador.CurrentFrame += 1;
                  }
                }
                else if(voadorAtaca){
                  if(voador.Temp > voador.FrameSpeed){
                    voador.Temp = 0;
                    voador.CurrentFrameAtaq += 1;
                    player.Vida -= 0.5;
                    if(voador.CurrentFrameAtaq >= 4){
                      voadorAtaca = false;
                      voador.CurrentFrameAtaq = 0;
                    }
                  }
                }
                voador.CurrentFrame = voador.CurrentFrame % 4;
              
                if(voadorAtaca){
                  estadoVoador = 2;
                  ColorPlayer = DARKGREEN;
                  voador.FrameRec = (Rectangle) {voador.Width *  voador.CurrentFrameAtaq, voador.Height * estadoVoador, voador.Width, voador.Height};
                }
                else if(!voadorAtaca){
                  estadoVoador = 1;
                  voador.FrameRec = (Rectangle) {voador.Width *  voador.CurrentFrame, voador.Height * estadoVoador, voador.Width, voador.Height};
                  //ColorPlayer = RAYWHITE;    
                }

                player.Temp += GetFrameTime();
                player.CurrentFrame = player.CurrentFrame % 4;
                //movimentacao do player
                if(flag > 0 && flag <= 4){
                    ataqueConfirmado = false;
                    ataqueEnemy = false;
                    ataqueMonstro = false;
                    ataqueVoador = false;
                    Colorboss = RAYWHITE;
                    ColorEnemy = RAYWHITE;
                    ColorMonstro = RAYWHITE;
                    ColorVoador = RAYWHITE;


                    if(player.Temp > player.FrameSpeed){
                        player.Temp = 0;
                        player.CurrentFrame += 1;
                    }
                    player.FrameRec  = (Rectangle) { player.Width * player.CurrentFrame , player.Height*(flag-1), player.Width, player.Height};
                    DrawTextureRec (player.Img,  player.FrameRec , player.Position , ColorPlayer);
                    aux = player.Height*(flag-1);

                }else{ // player fica parado
                    if(ataque == 0){
                        ataqueConfirmado = false;
                        ataqueEnemy = false;
                        ataqueMonstro = false;
                        ataqueVoador = false;

                        Colorboss = RAYWHITE;
                        ColorEnemy = RAYWHITE;
                        ColorMonstro = RAYWHITE;
                        ColorVoador = RAYWHITE;

                        player.FrameRec  = (Rectangle) { player.Width * 4, aux , player.Width, player.Height};
                        DrawTextureRec (player.Img,  player.FrameRec , player.Position, ColorPlayer);
                    
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
                        if(ataqueMonstro){
                            ColorMonstro = RED;
                            monstro.Vida -= 0.9;
                        }
                        if(ataqueVoador){
                            ColorVoador = RED;
                            voador.Vida -= 0.9;
                        }
                        
                        if(!ataqueConfirmado) Colorboss = RAYWHITE;
                        if(!ataqueEnemy) ColorEnemy = RAYWHITE;
                        if(!ataqueMonstro)  ColorMonstro = RAYWHITE;
                        if(!ataqueVoador) ColorVoador = RAYWHITE;

                        player.FrameRec = (Rectangle) { player.Width * CurrentFrameAtaq, aux, player.Width, player.Height};
                        DrawTextureRec(player.Img, player.FrameRec, player.Position, ColorPlayer);
                        //a ideia e que ele passe nessa condicao 3 vezes pra concluir a animacao de ataque, usando as flags p/ isso
                        if(CurrentFrameAtaq > 7){
                            acabou = 1;
                        }

                    }
                }

                DrawTextureRec(voador.Img, voador.FrameRec, voador.Position, ColorVoador);
                DrawTextureRec(monstro.Img, monstro.FrameRec, monstro.Position, ColorMonstro);

                //vamos ver se o monstro tbm n morreu pra fazer a animacao
                if(monstro.Vida <= 0){
                    monstroAtaca = false;
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
                    monstroMorreu = true;
                    ColorPlayer = RAYWHITE;
                    //UnloadTexture(monstro.Img);
                }  
                DrawTextureRec (enemie.Img, enemie.FrameRec, enemie.Position, ColorEnemy);
                
                //vendo se o enemie n morreu pra poder fazer a animacao de morte
                if(enemie.Vida <= 0){
                    enemyAtaca = false;
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
                    enemieMorreu = true;
                    ColorPlayer = RAYWHITE;
                    //UnloadTexture(enemie.Img);
                }

                if(voador.Vida<=0){
                    voadorAtaca = false;
                    estadoVoador = 3;
                    voador.Temp = 0;
                    voador.CurrentFrame = 0;
                    //boss.FrameSpeed = 8;
                    while(voador.CurrentFrame !=5){
                        voador.Temp += GetFrameTime();
                        if(voador.Temp > voador.FrameSpeed){
                        voador.Temp = 0;
                        voador.CurrentFrame += 1;

                        }
                        voador.FrameRec = (Rectangle) {voador.Width *  voador.CurrentFrame, voador.Height * estadoVoador, voador.Width, voador.Height};
                        DrawTextureRec(voador.Img, voador.FrameRec, voador.Position, ColorVoador); 

                        }
                    voador.Position = (Vector2) {12000.0, 12000.0};
                    voador.Collision = (Rectangle) {12000.0, 12000.0, 1.0, 1.0};
                    voadorMorreu = true;
                    ColorPlayer = RAYWHITE;
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
                    colorVida = RAYWHITE;
                }
                rec = (Rectangle) { 0.0, lifeHeight * currentLife, lifeWidth, lifeHeight};
                DrawTxtureRec (imglife, rec , posicaoVida, colorVida);
                //DrawRectangle(830, 40, player.Vida, 30, RED);

                if(player.Vida <= 0) tela_gameover = 1;
                else if(monstroMorreu && enemieMorreu && bossMorreu && voadorMorreu) tela_gamewin = 1;
                if(IsKeyPressed(KEY_ENTER)) jogo_pausado = 1;
            EndDrawing();
        
            paused();
            gameover();
            gamewin();

            if(IsKeyPressed(KEY_SPACE)) stopTelaInicial = 0; //volta p telaInicial
            
        }
    }

    terminar();
    terminarPersonagens();
    UnloadTexture(coxinhas[0].Img);
    UnloadTexture(coxinhas[1].Img);
    UnloadTexture(coxinhas[2].Img);
    
    
    return 0;
}
