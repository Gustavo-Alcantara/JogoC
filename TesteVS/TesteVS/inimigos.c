#include "classes.h"

void atualiza_inimigos(struct Inimigo* Ativos, int tam) {
	if (Ativos->vida_atual > 0 && !Ativos->morto)
		al_draw_line(Ativos->caixa.x0, Ativos->caixa.y0, Ativos->caixa.x0 + (Ativos->caixa.x1 - Ativos->caixa.x0) * Ativos->vida_atual / Ativos->vida_total, Ativos->caixa.y0, al_map_rgb(255, 0, 0), 2);
	if (!Ativos->morto)
		anima_Inimigo(Ativos, Ativos->acao_atual);
}
void comportamento(struct Inimigo* Ativos,struct Carinha* Principal, struct Projetil* Bomba) {
	if (!Ativos->morto) {
		switch (Ativos->tipo) {
		case GOBLIN:
			comportamento_goblin(Ativos, Principal, Bomba);
			break;
		case ARMADURA:
			comportamento_armadura(Ativos, Principal);
			break;
		case OLHO:
			comportamento_olho(Ativos, Principal);
			break;
		}
	}
}
void inicia_inimigo(struct Inimigo*Ativos, int dx, int dy, int LARGURA_TELA, int ALTURA_TELA, int tipo) {
	switch (tipo) {
	case GOBLIN:
		inicia_goblin(Ativos,dx,dy,LARGURA_TELA,ALTURA_TELA);
		break;
	case ARMADURA:
		inicia_armadura(Ativos, dx, dy, LARGURA_TELA, ALTURA_TELA);
		break;
	case OLHO:
		inicia_olho(Ativos, dx, dy, LARGURA_TELA, ALTURA_TELA);
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