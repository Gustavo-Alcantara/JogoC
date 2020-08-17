#include "classes.h"

void inicializa_cara(struct Carinha* Principal) {

	Principal->dx = (LARGURA_TELA / 40);
	Principal->dy = (32 * ALTURA_TELA / 40);
	Principal->direita = true;
	Principal->veloc = 3;
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
	Principal->ac[2].num_frames = 8;
	Principal->ac[7].inicioX = 1;
	Principal->ac[7].inicioY = 6;
	Principal->ac[7].finalX = 6;
	Principal->ac[7].finalY = 6;
	Principal->ac[7].num_frames = 3;
}