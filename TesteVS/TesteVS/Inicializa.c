#include "classes.h"

void inicializa_cara(struct Carinha* Principal) {
	strcpy(Principal->nome, "Marcos");
	Principal->dx = (LARGURA_TELA / 40);
	Principal->dy = (32 * ALTURA_TELA / 40);
	Principal->direita = 0;
	Principal->veloc = 4;
	Principal->imagem_personagem.png = al_load_bitmap("cara2.png");
	Principal->imagem_personagem.altura_folha = 37;
	Principal->imagem_personagem.largura_folha = 50;
	Principal->imagem_personagem.altura = 70;
	Principal->imagem_personagem.largura = 90;
	Principal->imagem_personagem.num_col = 7;
	Principal->imagem_personagem.num_lin = 11;
	Principal->ac[0].inicioX = 0;
	Principal->ac[0].inicioY = 0;
	Principal->ac[0].finalX = 3;
	Principal->ac[0].finalY = 0;
	Principal->ac[0].num_frames = 10;
	Principal->ac[2].inicioX = 1;
	Principal->ac[2].inicioY = 1;
	Principal->ac[2].finalX = 6;
	Principal->ac[2].finalY = 1;
	Principal->ac[2].num_frames = 7;
	Principal->ac[8].inicioX = 1;
	Principal->ac[8].inicioY = 6;
	Principal->ac[8].finalX = 6;
	Principal->ac[8].finalY = 6;
	Principal->ac[8].num_frames = 3;
}
void inicia_goblin(struct Carinha* Goblin, int dx,int dy) {
	strcpy(Goblin->nome ,"Piolho");
	Goblin->dx = dx;
	Goblin->dy = dy;
	Goblin->direita = ALLEGRO_FLIP_HORIZONTAL;
	Goblin->veloc = 3;
	Goblin->imagem_personagem.png = al_load_bitmap("Goblin.png");
	Goblin->imagem_personagem.altura_folha = 150;
	Goblin->imagem_personagem.largura_folha = 150;
	Goblin->imagem_personagem.altura = 210;
	Goblin->imagem_personagem.largura = 210;
	Goblin->imagem_personagem.num_col = 32;
	Goblin->imagem_personagem.num_lin = 1;
	Goblin->ac[0].inicioX = 0;
	Goblin->ac[0].inicioY = 0;
	Goblin->ac[0].finalX = 3;
	Goblin->ac[0].finalY = 0;
	Goblin->ac[0].num_frames = 10;
	Goblin->ac[1].inicioX = 4;
	Goblin->ac[1].inicioY = 0;
	Goblin->ac[1].finalX = 15;
	Goblin->ac[1].finalY = 0;
	Goblin->ac[1].num_frames = 9;
	Goblin->ac[2].inicioX = 16;
	Goblin->ac[2].inicioY = 0;
	Goblin->ac[2].finalX = 23;
	Goblin->ac[2].finalY = 0;
	Goblin->ac[2].num_frames = 5;
	Goblin->ac[3].inicioX = 24;
	Goblin->ac[3].inicioY = 0;
	Goblin->ac[3].finalX = 31;
	Goblin->ac[3].finalY = 0;
	Goblin->ac[3].num_frames = 5;
}