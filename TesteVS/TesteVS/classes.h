#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "tipos.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#define FPS 60.0

struct Hitbox{
	float x0;
	float y0;
	float x1;
	float y1;
};
struct acao {
	int inicioX;
	int inicioY;
	int finalX;
	int finalY;
	int num_frames;
	int frame_atual;
	int col_atual;
	int lin_atual;
};
struct Sprite{
	ALLEGRO_BITMAP* png;
	int largura;
	int altura;
	int largura_folha;
	int altura_folha;
	int num_col;
	int num_lin;
};
struct Projetil {
	struct Sprite img;
	struct acao ac[2];
	struct Hitbox caixa;
	int estado;
	int xi;
	int yi;
	float dx;
	float dy;
	float veloc;
	float dano;
	float raiz;
	bool existe;
};
struct Carinha{
	struct Sprite imagem_personagem;
	struct acao ac[20];
	struct Hitbox caixa;
	char nome[20];
	int conta_ataque;
	int conta_pulo;
	int acao_atual;
	int vida_total;
	int vida_atual;
	int direita;
	int veloc;
	int altura_pulo;
	int acao_espera;
	int espera;
	int dano;
	float dx;
	float dy;
	float cx;
	float cy;
	float queda;
	bool ataca;
	bool movendo;
	bool pula;
	bool morto;
	bool apanha;
	bool block;
};
struct Inimigo {
	struct Sprite imagem_personagem;
	struct acao ac[10];
	struct Hitbox caixa;
	int tipo;
	int acao_atual;
	int vida_total;
	int vida_atual;
	int direita;
	int veloc;
	int altura_pulo;
	int dano;
	int espera;
	float queda;
	float dx;
	float dy;
	float cx;
	float cy;
	bool morto;
	bool apanha;
	bool block;
};
struct Fundo {
	ALLEGRO_BITMAP* imagem;
	int dx;
	int dy;
	int largura;
	int largura_folha;
	int altura;
	int altura_folha;
};

void anima_personagem(struct Carinha* boneco, int indice);
void anima_Inimigo(struct Inimigo* boneco, int indice);
void reseta_acoes(struct Carinha*boneco,int num_acoes ,int indice,int direita);
void reseta_acoes_inimigo(struct Inimigo*boneco,int num_acoes ,int indice,int direita);

void inicializa_cara(struct Carinha* Principal, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void inicia_goblin(struct Inimigo* Goblin, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void carrega_projetil_goblin(struct Projetil* Bomba, struct Inimigo* Goblin);
void reseta_acao(struct acao*ac);
void anima_projetil(struct Projetil* Bomba);
void desenha_hitbox(struct Hitbox* caixa);
bool colisao(struct Hitbox* caixa1, struct Hitbox* caixa2);
bool colisao_chao(struct Hitbox* Bicho, struct Hitbox Vetor_Chao[10]);
void comportamento_goblin(struct Inimigo* Goblin, struct Carinha* Principal, struct Projetil* Bomba);
double dist(float cx0, float cy0, float cx1, float cy1);
void le_teclado_baixo(struct Carinha* Principal, struct Hitbox* Chao[10], int codigo);
void le_teclado_alto(struct Carinha* Principal, int codigo);
void personagem_principal(struct Carinha* Principal, struct Hitbox* Chao[10], struct Inimigo Goblin[5], int desloc_tela);
void fisica_bomba(struct Projetil* Bomba, struct Inimigo* Goblin, struct Carinha* Principal, struct Hitbox* Vetor_Chao[10]);
void atualiza_inimigos(struct Inimigo* Ativos, int tam);
void inicia_armadura(struct Inimigo* Armadura, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void comportamento_armadura(struct Inimigo* Armadura, struct Carinha* Principal);
void inicia_olho(struct Inimigo* Olho, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void comportamento_olho(struct Inimigo* Olho, struct Carinha* Principal);
void carrega_mapa(char mapa[20][20], int dx, struct Hitbox Vetor_Chao[10], int LARGURA_TELA, int ALTURA_TELA);
void desenha_bloco(struct ALLEGRO_BITMAP* Bloco[6], int dx0, int dy0, int dx1, int dy1);
void atualiza_fundo(struct Fundo* fundo, int LARGURA_TELA, int ALTURA_TELA);
void comportamento(struct Inimigo* Ativos, struct Carinha* Principal, struct Projetil* Bomba);
void inicia_inimigo(struct Inimigo* Ativos, int dx, int dy, int LARGURA_TELA, int ALTURA_TELA, int tipo);
bool mortos(struct Inimigo Ativos[5]);
void comportamento_magocaveira(struct Inimigo* MagoCaveira, struct Carinha* Principal);
void comportamento_mago(struct Inimigo* Mago, struct Carinha* Principal);
void inicia_magocaveira(struct Inimigo* MagoCaveira, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void inicia_mago(struct Inimigo* Mago, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);