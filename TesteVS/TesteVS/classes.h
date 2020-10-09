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
	bool nochao;
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
	bool nochao;
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

//Funções Relativas à inicialização de inimigos, estão nos arquivos Inicializa, Inicializa_2 e Inimigos.c 
void inicia_inimigo(struct Inimigo* Ativos, struct ALLEGRO_BITMAP* img[NUM_INIMIGOS],int dx, int dy, int LARGURA_TELA, int ALTURA_TELA, int tipo);
void inicia_goblin(struct Inimigo* Goblin, struct ALLEGRO_BITMAP* img, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void inicia_armadura(struct Inimigo* Armadura, struct ALLEGRO_BITMAP* img, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void inicia_olho(struct Inimigo* Olho, struct ALLEGRO_BITMAP* img, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void inicia_magocaveira(struct Inimigo* MagoCaveira, struct ALLEGRO_BITMAP* img,int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void inicia_mago(struct Inimigo* Mago, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void carrega_projetil_goblin(struct Projetil* Bomba, struct Inimigo* Goblin);

//Funções reliativas à animação, estão todas no arquivo anima.c
void anima_personagem(struct Carinha* boneco, int indice);
void anima_Inimigo(struct Inimigo* boneco, int indice);
void anima_projetil(struct Projetil* Bomba);
void desenha_hitbox(struct Hitbox* caixa);
void desenha_bloco(struct ALLEGRO_BITMAP* Bloco[6], int dx0, int dy0, int dx1, int dy1);
void atualiza_fundo(struct Fundo* fundo, int LARGURA_TELA, int ALTURA_TELA);

//Funções de gerenciamento de ações dos personagens
void reseta_acoes(struct Carinha*boneco,int num_acoes ,int indice,int direita);
void reseta_acoes_inimigo(struct Inimigo*boneco,int num_acoes ,int indice);
void reseta_acao(struct acao*ac);

//Funções relativas ao gerenciamento de colisão, todas presentes no arquivo comportamento.c
bool colisao(struct Hitbox* caixa1, struct Hitbox* caixa2);
int colisao_chao(struct Hitbox* Bicho, struct Hitbox Vetro_Chao[10] );
double dist(float cx0, float cy0, float cx1, float cy1);

//Funções relativas ao personagem principal
void inicializa_cara(struct Carinha* Principal, struct ALLEGRO_BITMAP* img,int dx, int dy, int ALTURA_TELA, int LARGURA_TELA);
void le_teclado_baixo(struct Carinha* Principal, struct Hitbox Chao[10], int codigo);
void le_teclado_alto(struct Carinha* Principal, int codigo);
void personagem_principal(struct Carinha* Principal, struct Hitbox Chao[10], struct Inimigo Goblin[5], int desloc_tela);

//Funções de gerenciamento do comportamento dos personagens, presentes nos arquivos comportamento, e comportamento_2.c
void comportamento(struct Inimigo* Ativos, struct Carinha* Principal, struct Projetil* Bomba);
void comportamento_goblin(struct Inimigo* Goblin, struct Carinha* Principal, struct Projetil* Bomba);
void comportamento_armadura(struct Inimigo* Armadura, struct Carinha* Principal);
void comportamento_olho(struct Inimigo* Olho, struct Carinha* Principal);
void comportamento_magocaveira(struct Inimigo* MagoCaveira, struct Carinha* Principal);
void comportamento_mago(struct Inimigo* Mago, struct Carinha* Principal);
void fisica_bomba(struct Projetil* Bomba, struct Inimigo* Goblin, struct Carinha* Principal, struct Hitbox  (*)[10]);

//Funções relativas a carregamento do mapa, presente no arquivo mapa.c
void carrega_mapa(char mapa[20][20], int dx, struct Hitbox Vetor_Chao[10], int LARGURA_TELA, int ALTURA_TELA);

//Funções relativas a gerenciamento dos inimigos presentes no arquivo inimigos.c
bool mortos(struct Inimigo Ativos[5]);
void atualiza_inimigos(struct Inimigo* Ativos, int tam);