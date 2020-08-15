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


struct acao{
	int inicio[2];
	int final[2];
	int num_frames;
};
struct Sprite{
	ALLEGRO_BITMAP* png;
	const char folha[20];
	int largura;
	int altura;
	int largura_folha;
	int altura_folha;
	int num_col;
	int num_lin;
};
	
struct Carinha{
	struct Sprite imagem_personagem;
	struct acao ac[20];
	char nome[20];
	int vida_total;
	int vida_atual;
	bool direita;
	int veloc;
	int altura_pulo;
	int dx;
	int dy;
};

void anima_respirando(ALLEGRO_EVENT* evento, bool invertido);
void anima_correndo(ALLEGRO_EVENT* evento, bool invertido, int al);
void anima_pulando(ALLEGRO_EVENT* evento, bool invertido);
void anima_ataque(ALLEGRO_EVENT* evento, int conta_ataque, bool invertido);
void anima(ALLEGRO_EVENT* evento, ALLEGRO_EVENT_QUEUE* fila, struct Carinha* boneco, int indice);