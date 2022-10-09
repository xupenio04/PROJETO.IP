
#include "raylib.h"
#include <stdio.h>

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
} Player;

//-----MENU
void opening_menu(){ 
    char gameplay[] = "Nossa aventura consiste na sobrevivência dos nossos garotos e garotas de programa dentro do Centro de informática.\n  Para isso, será necessário enfrentar as mais diversas cadeiras, com maléficos professores e monstros tenebrosos.";
    char op_robocin[] = "ROBÔS DO CIN";
    char robo_cin[] = "Meus caros garotos de programa, um dos piores inimigos a ser\nenfrentados serão os famigerados arduinos vermelhos,\ncomandados pelo terrível general ROBOCIN.";
    //char op_integralistas []= "Os integralistas";
    //char integralistas [] = "Além disso, para piorar a situação dos nossos garotos de programas, os destemidos monstros integralistas da área 2 chegam para acabar com nossos programadores";
    char op_general_robocin [] = "GENERAL ROBOCIN";
    char general_robocin[] = "Após um árdua batalha contra os maléficos robôs e os integralistas,\nvocês aventureiros de programas, terão de enfrentar o famoso\nGeneral RoboCIn, conhecido pela sua imensa força e agilidade.";

    DrawText(gameplay, 250, 250, 25, WHITE);
    DrawText(op_robocin, 400, 350, 50, GREEN);
    DrawText(robo_cin, 400, 400, 20, WHITE);
    DrawText(op_general_robocin, 400, 550, 50, GREEN);
    DrawText(general_robocin, 400, 600, 20, WHITE);
    //Drawtext(op_integralistas, 70, 150, 20, GREEN);
    //DrawText(integralistas, 200, 280, 20, BLACK);
}

void carregar_jogo(){ //tela pos start
    char intro_game[] = "Parabéns, você é o mais novo aprovado no curso de engenharia da computação do CIN-UFPE.\n                      Entretanto, seus tempos de glória chegaram ao fim.";
    //char tutorial[] = "Após a escolha do seu personagem, utilize as teclas de baixo, cima, esquerda e direita para se movimentar pelo mapa. Utilize a tecla espaço para atacar os inimigos."; 

    DrawText(intro_game, 210, 500, 30, WHITE);
    //DrawText(tutorial, 300, 400, 20, WHITE);
}

Rectangle botao_start(char path[], Texture2D *start){
    Image image_start = LoadImage(path);
    ImageResize(&image_start, 355, 145);
    (*start) = LoadTextureFromImage(image_start);
    Rectangle button_start = {1020, 660, start -> width, start -> height};
    UnloadImage(image_start);

    return button_start;
}

Rectangle botao_menu(char path[], Texture2D *menu){
    Image image_menu = LoadImage(path);
    ImageResize(&image_menu, 355, 145);
    (*menu) = LoadTextureFromImage(image_menu);
    Rectangle button_menu = {515,  660, menu -> width, menu -> height};
    UnloadImage(image_menu);

    return button_menu;
}

int main(){
    int stopTelaInicial = 0;
    //int width = GetScreenWidth();
    //int height = GetScreenHeight();
    InitWindow(GetScreenWidth(), GetScreenHeight(), "GAME");
    ToggleFullscreen();
    SetTargetFPS(60);

    Player Player;
    Player.Img = (Texture2D) LoadTexture("pasta/sprite1.png");
    Player.Width = (float) Player.Img.width / 8;
    Player.Height = (float) Player.Img.height/4;
    Player.MaxFrame = 4;
    Player.CurrentFrame = 0;
    Player.Position = (Vector2) {GetScreenWidth()/2-100, GetScreenHeight()/2-100};
    Player.Temp = 0;
    Player.FrameSpeed = 0.1;

    int flag = 0, aux  = 0;
    int CurrentFrameAtaq = 5;
    int ataque = 0;
    int acabou = 0;

    //carregando telas inicial, menu, mapa e preta
    Texture2D telaInicial = LoadTexture("pasta/telaInicial.png");
    Texture2D telaMenu = LoadTexture("pasta/telaMenu.png");
    Texture2D mapa = LoadTexture("pasta/mapaa.png");
    Texture2D telaPreta = LoadTexture("pasta/telaPreta.png");

    //carregando botão start(iluminado)/start1(botao da tela)
    Texture2D start1;
    Rectangle button_start1 = botao_start("pasta/botao_start1.png", &start1);
    Texture2D start;
    Rectangle button_start = botao_start("pasta/botao_start.png", &start);

    //carregando botão menu(iluminado)/menu1(botao da tela)
    Texture2D menu;
    Rectangle button_menu = botao_menu("pasta/botao_menu.png", &menu);
    Texture2D menu1;
    Rectangle button_menu1 = botao_menu("pasta/botao_menu1.png", &menu1);

    //checando os botões para start e menu
    int click_start = 0;
    int click_menu = 0;

    while(!WindowShouldClose()){
        //pegar a posição do mouse
        Vector2 mouse_move = GetMousePosition();
        Rectangle mouse = {mouse_move.x, mouse_move.y, 20, 20};

        BeginDrawing();
            //abrindo tela inicial
            if(!stopTelaInicial){
                ClearBackground(RAYWHITE);
                DrawTexture(telaInicial, 0, 0, WHITE);
                DrawTexture(start1, button_start1.x, button_start1.y, WHITE);
                DrawTexture(menu1, button_menu1.x, button_menu1.y, WHITE);
            }

            // checando se o mouse bateu em algum dos botões
            if(CheckCollisionRecs(button_start, mouse)){
                DrawTexture(start, button_start.x, button_start.y, WHITE);
                click_start = 1;
            }else click_start = 0;

            if(CheckCollisionRecs(button_menu,mouse)) {
                DrawTexture(menu, button_menu.x, button_menu.y, WHITE);
                click_menu = 1;                
            }else click_menu = 0;

        EndDrawing();

        //abrindo Menu
        if(click_menu && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            stopTelaInicial = 1;
            while(stopTelaInicial){
                BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTexture(telaMenu, 0, 0, WHITE); 
                    opening_menu();
                    if(IsKeyPressed(KEY_SPACE)) stopTelaInicial = 0; //volta p telaInicial
                EndDrawing();
            }
        }

        //abrindo jogo
        if(click_start && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            stopTelaInicial = 1;

            //intro do jogo
            BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(telaPreta, 0, 0, WHITE);
                carregar_jogo();
            EndDrawing();
            WaitTime(3); //delay

            //mapa do jogo
            while(stopTelaInicial){
                BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTexture(mapa, 0, 0, WHITE); 

                    if(acabou == 1){
                        ataque = 0;
                        CurrentFrameAtaq = 4; //comecando um antes por causa da incrementacao
                    }
                    
                    if(flag != 5) flag = 0;
                    if(IsKeyDown(KEY_DOWN) && Player.Position.y < GetScreenHeight()-100){
                        Player.Position.y += 4;
                        flag = 1;
                    } 
                    if(IsKeyDown(KEY_UP) && Player.Position.y >= 0){
                        Player.Position.y -= 4;
                        flag = 2;
                    }
                    if(IsKeyDown(KEY_RIGHT) && Player.Position.x < GetScreenWidth()-100) {
                        Player.Position.x += 4;
                        flag = 3;
                    }
                    if(IsKeyDown(KEY_LEFT) && Player.Position.x > 20){
                        Player.Position.x -= 4;
                        flag = 4;
                    }
                    if(IsKeyDown(KEY_F)){
                        ataque = 1;
                        acabou = 0;
                    }

                    Player.Temp += GetFrameTime();
                    Player.CurrentFrame = Player.CurrentFrame % 4;
                    
                    //movimentacao do player
                    if(flag > 0 && flag <= 4){                        
                        if(Player.Temp > Player.FrameSpeed){
                            Player.Temp = 0;
                            Player.CurrentFrame += 1;
                        }
                        Player.FrameRec  = (Rectangle) { Player.Width * Player.CurrentFrame , Player.Height*(flag-1), Player.Width, Player.Height};
                            DrawTextureRec (Player.Img,  Player.FrameRec , Player.Position , RAYWHITE);
                        aux = Player.Height*(flag-1);

                    }else{ // player fica parado
                        if(ataque == 0){
                            Player.FrameRec  = (Rectangle) { Player.Width * 4, aux , Player.Width, Player.Height};
                            DrawTextureRec (Player.Img,  Player.FrameRec , Player.Position, RAYWHITE);
                        
                        }else{
                            if(Player.Temp > Player.FrameSpeed){
                                Player.Temp = 0;
                                CurrentFrameAtaq++;
                            }
                            Player.FrameRec = (Rectangle) { Player.Width * CurrentFrameAtaq, aux, Player.Width, Player.Height};
                            DrawTextureRec(Player.Img, Player.FrameRec, Player.Position, RAYWHITE);
                            //a ideia e que ele passe nessa condicao 3 vezes pra concluir a animacao de ataque, usando as flags p/ isso
                            if(CurrentFrameAtaq > 7){
                                acabou = 1;
                            }

                        }
                    }

                    if(IsKeyPressed(KEY_SPACE)) stopTelaInicial = 0; //volta p telaInicial
                EndDrawing();
            }
        }
    }

    UnloadTexture(telaInicial);
    UnloadTexture(telaMenu);
    UnloadTexture(mapa);
    UnloadTexture(telaPreta);
    UnloadTexture(start);
    UnloadTexture(start1);
    UnloadTexture(menu);
    UnloadTexture(menu1);
    CloseWindow();
    return 0;
}
