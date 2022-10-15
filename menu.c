#include "raylib.h"
#include "menu.h"

int click_start = 0;
int click_menu = 0;

int stopTelaInicial = 0;
int jogo_pausado = 0;
int tela_gameover = 0;
int tela_gamewin = 0;

Sound botao_jogo;
Sound audio_espada;
Sound audio_boss;
Sound audio_battle;
Music audio_menu;

Texture2D telaInicial;
Texture2D telaMenu;
Texture2D mapa;
Texture2D telaPreta;
Texture2D pause;
Texture2D imglife;
Texture2D gameOver;
Texture2D gameWin;
Image fundoMapa;

Texture2D start1;
Rectangle button_start1;
Texture2D start;
Rectangle button_start;

Texture2D menu;
Rectangle button_menu;
Texture2D menu1;
Rectangle button_menu1;

Vector2 mouse_move;
Rectangle mouse;

float lifeHeight = 100.0;
float lifeWidth = 600.0;
Vector2 posicaoVida = {20,20};
Rectangle rec = { 0 };
int currentLife = 0;

void iniciarJogo() {
    InitWindow(GetScreenWidth(), GetScreenHeight(), "GAME");
    ToggleFullscreen();
    SetTargetFPS(60);
    InitAudioDevice();
  
    botao_jogo = LoadSound("sounds/botao.mp3");
    audio_espada = LoadSound("sounds/espada.mp3");
    audio_boss = LoadSound("sounds/boss.mp3");
    audio_battle = LoadSound("sounds/battle.mp3");
    audio_menu = LoadMusicStream("sounds/menu.mp3");
    PlayMusicStream(audio_menu);
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

void carregar_jogo(){ //tela pos start
    char intro_game[] = "Parabéns, você é o mais novo aprovado no curso de engenharia da computação do CIN-UFPE.\n                      Entretanto, seus tempos de glória chegaram ao fim.";
    DrawText(intro_game, 210, 500, 30, WHITE);
}

Texture2D carregarTela(char path[]) {
    Image img = LoadImage(path);
    ImageResize(&img, GetScreenWidth(), GetScreenHeight());
    Texture2D tela = (Texture2D) LoadTextureFromImage(img);
    UnloadImage(img);

    return tela;
}

void carregarTelas() {
    telaMenu = carregarTela("assets/telaMenu.png");
    telaInicial = carregarTela("assets/telaInicial.png");
    mapa = carregarTela("assets/mapa.png");
    telaPreta = carregarTela("assets/telaPreta.png");
    pause = carregarTela("assets/pause.png");
    gameOver = carregarTela("assets/gameover.png");
    gameWin = carregarTela("assets/gamewin.png");
}

void carregarVida() { 
    Image img_life = LoadImage("assets/vida.png");
    imglife = (Texture2D) LoadTextureFromImage(img_life);
    UnloadImage(img_life);
}

void carregarBotoes() {
    //carregando botão start(iluminado)/start1(botao da tela)
    button_start1 = botao_start("assets/botao_start1.png", &start1);
    button_start = botao_start("assets/botao_start.png", &start);

    //carregando botão menu(iluminado)/menu1(botao da tela)
    button_menu = botao_menu("assets/botao_menu.png", &menu);
    button_menu1 = botao_menu("assets/botao_menu1.png", &menu1);
}

void abrirTelaInicial() {
    ClearBackground(PINK);
    DrawTexture(telaInicial, 0, 0, WHITE);
    DrawTexture(start1, button_start1.x, button_start1.y, WHITE);
    DrawTexture(menu1, button_menu1.x, button_menu1.y, WHITE);
    StopSound(audio_battle);
    PlayMusicStream(audio_menu);
}

void checaBotao() {
    // checando se o mouse bateu em algum dos botões
    if(CheckCollisionRecs(button_start, mouse)){
        DrawTexture(start, button_start.x, button_start.y, WHITE);
        click_start = 1;
        PlaySound(botao_jogo);

    }else click_start = 0;

    if(CheckCollisionRecs(button_menu,mouse)) {
        DrawTexture(menu, button_menu.x, button_menu.y, WHITE);
        click_menu = 1; 
        PlaySound(botao_jogo);
        
    }else click_menu = 0;
}

void abreMenu() {
    stopTelaInicial = 1;
    UpdateMusicStream(audio_menu);
    while(stopTelaInicial){
        UpdateMusicStream(audio_menu);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(telaMenu, 0, 0, WHITE); 
            if(IsKeyPressed(KEY_SPACE)) stopTelaInicial = 0; //volta p telaInicial
        EndDrawing();
    }
}

void abrePreJogo() {
    stopTelaInicial = 1;
    StopMusicStream(audio_menu);
    PlaySound(audio_battle);
    //intro do jogo
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(telaPreta, 0, 0, WHITE);
        carregar_jogo();
    EndDrawing();
    WaitTime(3); //delay
}

void carregarFundoMapa(){
    fundoMapa = LoadImage("assets/fundo_mapa.png");
    ImageResize(&fundoMapa, GetScreenWidth(), GetScreenHeight());
    //Color *colors = LoadImageColors(fundoMapa);
    //return colors;
}

void paused(){
    while(jogo_pausado){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(pause, 0, 0, WHITE);
            if(IsKeyPressed(KEY_ENTER)) jogo_pausado = 0;
        EndDrawing();
    }
}

void gameover(){
    while(tela_gameover){
        StopSound(audio_battle);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(gameOver, 0, 0, WHITE);
            if(IsKeyPressed(KEY_ENTER)) CloseWindow();
        EndDrawing();
    }
}

void gamewin(){
    while(tela_gamewin){
        StopSound(audio_battle);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(gameWin, 0, 0, WHITE);
            if(IsKeyPressed(KEY_ENTER)) CloseWindow();
        EndDrawing();
    }
}

void terminar() {
    UnloadTexture(telaInicial);
    UnloadTexture(telaMenu);
    UnloadTexture(mapa);
    UnloadTexture(telaPreta);
    UnloadTexture(pause);
    UnloadTexture(gameOver);
    UnloadTexture(gameWin);
    UnloadTexture(start);
    UnloadTexture(start1);
    UnloadTexture(menu);
    UnloadTexture(menu1);
    UnloadImage(fundoMapa);
    
    UnloadTexture(imglife);

    UnloadSound(botao_jogo);
    UnloadSound(audio_espada);
    UnloadSound(audio_battle);
    UnloadMusicStream(audio_menu);
    UnloadSound(audio_boss);
    
    CloseAudioDevice();
    CloseWindow();
}