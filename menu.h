#ifndef MENU
#define MENU

#include"raylib.h"

extern int click_start;
extern int click_menu;

extern int stopTelaInicial;
extern int jogo_pausado;
extern int tela_gameover;
extern int tela_gamewin;

extern Sound botao_jogo;
extern Sound audio_espada;
extern Sound audio_boss;
extern Sound audio_battle;
extern Music audio_menu;

extern Texture2D telaInicial;
extern Texture2D telaMenu;
extern Texture2D mapa;
extern Texture2D telaPreta;
extern Texture2D pause;
extern Texture2D imglife;
extern Texture2D gameOver;
extern Texture2D gameWin;
extern Image fundoMapa;

extern Texture2D start1;
extern Rectangle button_start1;
extern Texture2D start;
extern Rectangle button_start;

extern Texture2D menu;
extern Rectangle button_menu;
extern Texture2D menu1;
extern Rectangle button_menu1;

extern Vector2 mouse_move;
extern Rectangle mouse;

extern float lifeHeight;
extern float lifeWidth;
extern Vector2 posicaoVida;
extern Rectangle rec;
extern int currentLife;


void iniciarJogo();
Rectangle botao_start(char path[], Texture2D *start);
Rectangle botao_menu(char path[], Texture2D *menu);
void carregar_jogo();
Texture2D carregarTela(char path[]);
void carregarTelas();
void carregarVida();
void abrirTelaInicial();
void carregarBotoes();
void checaBotao();
void abreMenu();
void abrePreJogo();
void carregarFundoMapa();
void paused();
void gameover();
void gamewin();
void terminar();

#endif
