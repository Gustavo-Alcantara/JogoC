#include "classes.h"


void inicia_magocaveira(struct Inimigo* MagoCaveira, struct ALLEGRO_BITMAP* img, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA) {
	MagoCaveira->tipo = MAGOCAVEIRA;
	MagoCaveira->dano = 1;
	MagoCaveira->vida_total = 7;
	MagoCaveira->vida_atual = MagoCaveira->vida_total;
	MagoCaveira->dx = dx;
	MagoCaveira->dy = dy;
	MagoCaveira->queda = 0;
	MagoCaveira->direita = ALLEGRO_FLIP_HORIZONTAL;
	MagoCaveira->veloc = 4;
	MagoCaveira->espera = 60;
	MagoCaveira->block = false;
	MagoCaveira->morto = false;
	MagoCaveira->imagem_personagem.png = img;
	MagoCaveira->imagem_personagem.altura_folha = 150;
	MagoCaveira->imagem_personagem.largura_folha = 150;
	MagoCaveira->imagem_personagem.altura = 450;
	MagoCaveira->imagem_personagem.largura = 450;
	MagoCaveira->imagem_personagem.num_col = 33;
	MagoCaveira->imagem_personagem.num_lin = 1;
	MagoCaveira->cx = MagoCaveira->dx + MagoCaveira->imagem_personagem.largura / 2;
	MagoCaveira->cy = MagoCaveira->dy + MagoCaveira->imagem_personagem.altura / 2;
	MagoCaveira->caixa.x0 = MagoCaveira->cx + 30;
	MagoCaveira->caixa.x1 = MagoCaveira->cx - 30;
	MagoCaveira->caixa.y0 = MagoCaveira->cy - 30;
	MagoCaveira->caixa.y1 = MagoCaveira->cy + 50;
	MagoCaveira->ac[0].inicioX = 0;
	MagoCaveira->ac[0].inicioY = 0;
	MagoCaveira->ac[0].finalX = 7;
	MagoCaveira->ac[0].finalY = 0;
	MagoCaveira->ac[0].num_frames = 10;
	MagoCaveira->ac[1].inicioX = 8;
	MagoCaveira->ac[1].inicioY = 0;
	MagoCaveira->ac[1].finalX = 15;
	MagoCaveira->ac[1].finalY = 0;
	MagoCaveira->ac[1].num_frames = 8;
	MagoCaveira->ac[2].inicioX = 16;
	MagoCaveira->ac[2].inicioY = 0;
	MagoCaveira->ac[2].finalX = 23;
	MagoCaveira->ac[2].finalY = 0;
	MagoCaveira->ac[2].num_frames = 15;
	MagoCaveira->ac[4].inicioX = 24;
	MagoCaveira->ac[4].inicioY = 0;
	MagoCaveira->ac[4].finalX = 27;
	MagoCaveira->ac[4].finalY = 0;
	MagoCaveira->ac[4].num_frames = 5;
	MagoCaveira->ac[5].inicioX = 28;
	MagoCaveira->ac[5].inicioY = 0;
	MagoCaveira->ac[5].finalX = 32;
	MagoCaveira->ac[5].finalY = 0;
	MagoCaveira->ac[5].num_frames = 10;
}
void inicia_mago(struct Inimigo* Mago, int dx, int dy, int ALTURA_TELA, int LARGURA_TELA) {
	Mago->tipo = MAGO;
	Mago->dano = 1;
	Mago->vida_total = 7;
	Mago->vida_atual = Mago->vida_total;
	Mago->dx = dx;
	Mago->dy = dy;
	Mago->queda = 0;
	Mago->direita = ALLEGRO_FLIP_HORIZONTAL;
	Mago->veloc = 4;
	Mago->espera = 60;
	Mago->block = false;
	Mago->morto = false;
	Mago->imagem_personagem.png = al_load_bitmap("Inimigos/Mago.png");
	Mago->imagem_personagem.altura_folha = 250;
	Mago->imagem_personagem.largura_folha = 250;
	Mago->imagem_personagem.altura = 500;
	Mago->imagem_personagem.largura = 500;
	Mago->imagem_personagem.num_col = 33;
	Mago->imagem_personagem.num_lin = 1;
	Mago->cx = Mago->dx + Mago->imagem_personagem.largura / 2;
	Mago->cy = Mago->dy + Mago->imagem_personagem.altura / 2;
	Mago->caixa.x0 = Mago->cx + 30;
	Mago->caixa.x1 = Mago->cx - 30;
	Mago->caixa.y0 = Mago->cy - 30;
	Mago->caixa.y1 = Mago->cy + 50;
	Mago->ac[0].inicioX = 0;
	Mago->ac[0].inicioY = 0;
	Mago->ac[0].finalX = 7;
	Mago->ac[0].finalY = 0;
	Mago->ac[0].num_frames = 10;
	Mago->ac[1].inicioX = 8;
	Mago->ac[1].inicioY = 0;
	Mago->ac[1].finalX = 15;
	Mago->ac[1].finalY = 0;
	Mago->ac[1].num_frames = 8;
	Mago->ac[2].inicioX = 16;
	Mago->ac[2].inicioY = 0;
	Mago->ac[2].finalX = 23;
	Mago->ac[2].finalY = 0;
	Mago->ac[2].num_frames = 15;
	Mago->ac[4].inicioX = 24;
	Mago->ac[4].inicioY = 0;
	Mago->ac[4].finalX = 27;
	Mago->ac[4].finalY = 0;
	Mago->ac[4].num_frames = 5;
	Mago->ac[5].inicioX = 28;
	Mago->ac[5].inicioY = 0;
	Mago->ac[5].finalX = 32;
	Mago->ac[5].finalY = 0;
	Mago->ac[5].num_frames = 10;
}