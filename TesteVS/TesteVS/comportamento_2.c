#include "classes.h"
#include "macros.h"

void comportamento_magocaveira(struct Inimigo* MagoCaveira, struct Carinha* Principal) {
	int a = 1;

	MagoCaveira->caixa.x0 = MagoCaveira->cx + 60;
	MagoCaveira->caixa.x1 = MagoCaveira->cx - 50;
	MagoCaveira->caixa.y0 = MagoCaveira->cy - 60;
	MagoCaveira->caixa.y1 = MagoCaveira->cy + 90;
	

	if (!MagoCaveira->morto) {
		if (!MagoCaveira->block) {
			if (MagoCaveira->cx < Principal->cx)
				MagoCaveira->direita = 0;
			else MagoCaveira->direita = ALLEGRO_FLIP_HORIZONTAL;

			if (MagoCaveira->direita == 0)
				a = -1;
			
			MagoCaveira->acao_atual = PARADO;
			if (dist(MagoCaveira->cx, MagoCaveira->cy, Principal->cx, Principal->cy) < 200) {
				MagoCaveira->acao_atual = ATAQUE1;
				MagoCaveira->block = true;
			}
			else if (dist(MagoCaveira->cx, MagoCaveira->cy, Principal->cx, Principal->cy) < 600) {
				MagoCaveira->acao_atual = CORRENDO;
				MagoCaveira->dx -= a * MagoCaveira->veloc;
			}
			if (MagoCaveira->vida_atual <= 0) {
				MagoCaveira->acao_atual = MORRE;
				MagoCaveira->block = true;
				MagoCaveira->apanha = false;
			}
		}
		else if (MagoCaveira->ac[MORRE].col_atual == MagoCaveira->ac[MORRE].finalX - 1)
			MagoCaveira->morto = true;
	}
}
void comportamento_mago(struct Inimigo* Mago, struct Carinha* Principal) {
	int a = 1;

	Mago->caixa.x0 = Mago->cx + 60;
	Mago->caixa.x1 = Mago->cx - 50;
	Mago->caixa.y0 = Mago->cy - 60;
	Mago->caixa.y1 = Mago->cy + 90;

	Mago->acao_atual = 0;

	if (Mago->vida_total <= 0)
		Mago->morto = true;
}