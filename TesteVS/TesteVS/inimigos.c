#include "classes.h"

void atualiza_inimigos(struct Inimigo* Ativos, int tam) {
	if (!Ativos->morto)
		anima_Inimigo(Ativos, Ativos->acao_atual);
}
void comportamento(struct Inimigo* Ativos,struct Carinha* Principal) {
	if (!Ativos->morto) {
		switch (Ativos->tipo) {
		case GOBLIN:
			comportamento_goblin(Ativos, Principal);
			break;
		case ARMADURA:
			comportamento_armadura(Ativos, Principal);
			break;
		case OLHO:
			comportamento_olho(Ativos, Principal);
			break;
		case MAGOCAVEIRA:
			comportamento_magocaveira(Ativos, Principal);
			break;
		case SLIME:
			comportamento_slime(Ativos, Principal);
			break;
		}
	}
}
void inicia_inimigo(struct Inimigo* Ativos, struct ALLEGRO_BITMAP* img[NUM_INIMIGOS], int dx, int dy, int LARGURA_TELA, int ALTURA_TELA, int tipo) {
	switch (tipo) {
	case GOBLIN:
		inicia_goblin(Ativos,img[GOBLIN - 1],dx,dy,LARGURA_TELA,ALTURA_TELA);
		break;
	case ARMADURA:
		inicia_armadura(Ativos, img[ARMADURA - 1], dx, dy, LARGURA_TELA, ALTURA_TELA);
		break;
	case OLHO:
		inicia_olho(Ativos, img[OLHO - 1], dx, dy, LARGURA_TELA, ALTURA_TELA);
		break;
	case MAGOCAVEIRA:
		inicia_magocaveira(Ativos, img[MAGOCAVEIRA - 1], dx, dy, LARGURA_TELA, ALTURA_TELA);
		break;
	case SLIME:
		inicia_slime(Ativos, img[SLIME - 1],dx, dy, LARGURA_TELA, ALTURA_TELA);
		break;
	default:
		inicia_olho(Ativos, img[OLHO - 1], dx, dy, LARGURA_TELA, ALTURA_TELA);
		break;
	}
}
bool mortos(struct Inimigo Ativos[5]) {
	for (int i = 0; i < 5; i++) {
		if (!Ativos[i].morto)
			return false;
	}
	return true;
}