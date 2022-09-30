#include "raylib.h"
// ainda precisa do outro boss e mob
// ainda precisa dos efeitos sonoros dos botões
 void opening_boss_enemy{
      char op_robocin[]=" ROBOS DO CIN";
   char robo_ic[]= "Meus caros garotos de programa, um dos piores inimigos a ser enfrentados serão os famigerados arduinos vermelhos, comandados pelo terrível general ROBOCIN.";

   char op_general_robocin[]=" GENERAL ROBOCIN";
   char general_robocin[]=" Apos um árdua batalha contra os maléficos robôs, vocês aventureiros de programas, terão de enfrentar o famoso General RoboCIn, conhecido pela sua imensa força e agilidade.";

   char op_mobscalculo=" MOBS CALCULO";
   char mobs_calculo=" ainda não foi decidido";

   char op_isaacnewton[]=" ISAAC NEWTON";
   char isaac_newton[]="Apesar das batalhas desafiadoras, as coisas não se tornarão mais fáceis. O grande inventor da Cáluclo Diferencial Integral será seu mais novo vilão. Utilizando seus conhecimentos de limites, derivadas e integrais, faça o possível e o impossível para derrotar esse complicador de vidas da área 2";

   Drawtext(op_robocin, 70, 150, GREEN);
   DrawText(robo_cin, 200, 280,BLACK);
   Drawtext(op_general_robocin, 70, 150, GREEN);
   DrawText(general_robocin, 200, 280, BLACK);
   Drawtext(op_mobscalculo, 70, 150, GREEN);
   DrawText(mobs_calculo, 200, 280, BLACK);
   Drawtext(op_isaacnewton, 70, 150, GREEN);
   DrawText(isaac_newton, 200, 280, BLACK);
   
 }

 void objetivo_jogo(){
   
   char gameplay[]="Nossa aventura consiste na sobrevivência dos nossos garotos e garotas de programa dentro do Centro de informática. Para isso, será necessário enfrentar as mais diversas cadeiras, com maléficos professores e monstros tenebrosos.";

  DrawText(gameplay, 200, 280, BLACK);
 }

  int mostrar_infos(Texture2D robo_cin, Texture2D general_robocin, Texture2D isaac_newton, Texture2D mobs_calculo, Texture2D limite, Texture2D ultima, Texture2D megazord ){

    const char infos_jogo[]="INFORMAÇÕES SOBRE O JOGO";

    Vector2 botao_mouse={0.0f, 0.0f};

    int botao_gameplay=0;
    int botao_enemys_boss_calculo=0;
    int botao_enemys_boss_ip=0;
    int botao_enemys_boss_ic=0;
    
    mouse.x=GetMouseX();
    mouse.Y=GetMouseY();
    double p = GetScreenWidth()/(double)1366;
    SetMouseScale(1/p, 1/p);
    SetTargetFPS(60);

    if(mouse.x >=120 && mouse.x<=230 && mouse.y>=300 && mouse.y<450){
      botao_gameplay=1;
    }
    
    else{
        botao_gameplay=0;
      }

   if(mouse.x >=240 && mouse.x<=330 && mouse.y>=300 && mouse.y<450){
      botao_enemys_boss_calculo=1;
  }

     else{
       botao_enemys_boss_calculo=0;
     }

   if(mouse.x >=340 && mouse.x<=450 && mouse.y>=300 && mouse.y<450){
      botao_enemys_boss_ic=1;
  }

     else{
       botao_enemys_boss_ic=0;
     }

   if(mouse.x >=480 && mouse.x<=570 && mouse.y>=300 && mouse.y<450) {
      botao_enemys_boss_ip=1;
  }

    else{
      botao_enemys_boss_ip=0;
    }


    int click_calculo=0;
    int click_ic=0;
    int click_ip=0;

    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawText(info_jogos, 450, 25, 60, BLUE);

    if(botao_enemys_boss_calculo==1){
        // depois voltar em menu para renomear cada textura
        DrawTexture(limite, 120,100, BLACK);
        DrawTexture(megazord, 510, 100, WHITE);
        DrawTexture(ultima, 920, 100, BLACK);
    }    

    else if(botao_enemys_boss_ic==1){
        DrawTexture(limite, 120,100, BLACK);
        DrawTexture(megazord, 510, 100, WHITE);
        DrawTexture(ultima, 920, 100, BLACK);
    }

    else if(botao_enemys_boss_ic==1){
        DrawTexture(limite, 120,100, BLACK);
        DrawTexture(megazord, 510, 100, WHITE);
        DrawTexture(ultima, 920, 100, BLACK);
    }

   else{
        DrawTexture(limite, 120,100, BLACK);
        DrawTexture(megazord, 510, 100, WHITE);
        DrawTexture(ultima, 920, 100, BLACK);
   }

    EndDrawing();
    return 0;
  }


