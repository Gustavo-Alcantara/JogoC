#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LARGURA_TELA 640
#define ALTURA_TELA 480
#define FPS 60.0

ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_BITMAP* layers[11];
ALLEGRO_BITMAP* folha = NULL;
ALLEGRO_FONT* fonte = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_KEYBOARD_STATE* teclado = NULL;

struct acao{
	int inicio[2];
	int final[2];
	int num_frames;
};
struct Sprite{
	char folha[20];
	int largura;
	int altura;
	int largura_folha;
	int altura_folha;
	int num_col;
	int num_lin;
};
struct  Carinha{
	struct Sprite imagem_personagem;
	struct acao ac[20];
	char nome[20];
	int vida_total;
	int vida_atual;
	int posicao[2];
	bool direita;
	int veloc;
	int dx;
	int dy;
};

bool desenha = false;
int tecla = 0;
int k = 0, i;
int frames_sprite = 10, cont_frames = 0;
int sprite_largura = 50, sprite_altura = 37;
int colunas_folha = 7, coluna_atual = 0;
int linhas_folha = 11, linha_atual = 0;
int pos_x_sprite = 320, pos_y_sprite = 240;
int regiao_y_folha = 0, regiao_x_folha = 0,desloc = 0;

void anima_respirando(ALLEGRO_EVENT* evento);
void anima_correndo(ALLEGRO_EVENT* evento, bool invertido, int al);
void anima_pulando(ALLEGRO_EVENT* evento);
void anima_ataque(ALLEGRO_EVENT* evento, int conta_ataque);
void anima_abaixado(ALLEGRO_EVENT* evento);
void anima(ALLEGRO_EVENT* evento, Carinha* boneco, int indice);