#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#define LARGURA_TELA 640
#define ALTURA_TELA 480
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
	bool existe;
};
struct Carinha{
	struct Sprite imagem_personagem;
	struct acao ac[20];
	struct Hitbox caixa;
	char nome[20];
	int acao_atual;
	int vida_total;
	int vida_atual;
	int direita;
	int veloc;
	int altura_pulo;
	float dx;
	float dy;
	float cx;
	float cy;
	int acao_espera;
	bool apanha;
	bool block;
};

void anima_personagem(struct Carinha* boneco, int indice);
void reseta_acoes(struct Carinha*boneco,int num_acoes ,int indice,int direita);

void inicializa_cara(struct Carinha* Principal);
void inicia_goblin(struct Carinha* Goblin, int dx, int dy);
void carrega_projetil_goblin(struct Projetil* Bomba, struct Carinha* Goblin);
void reseta_acao(struct acao*ac);
void anima_projetil(struct Projetil* Bomba);
void desenha_hitbox(struct Hitbox* caixa);
bool colisao(struct Hitbox* caixa1, struct Hitbox* caixa2);
void comportamento_goblin(struct Carinha* Goblin, struct Carinha* Principal, struct Projetil* Bomba);
double dist(float cx0, float cy0, float cx1, float cy1);
void le_teclado_baixo(struct Carinha* Principal, struct Hitbox* Chao, int codigo);
void le_teclado_alto(struct Carinha* Principal, int codigo);