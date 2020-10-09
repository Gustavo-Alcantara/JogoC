#include "classes.h"
#include "macros.h"

void comportamento_magocaveira(struct Inimigo* MagoCaveira, struct Carinha* Principal) {
	int a = 1;

	MagoCaveira->caixa.x0 = MagoCaveira->cx + 30;
	MagoCaveira->caixa.x1 = MagoCaveira->cx - 25;
	MagoCaveira->caixa.y0 = MagoCaveira->cy + 70;
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
		if (MagoCaveira->acao_atual == ATAQUE1 && Principal->apanha && dist(MagoCaveira->cx, MagoCaveira->cy, Principal->cx, Principal->cy) < 200 && MagoCaveira->ac[ATAQUE1].col_atual >= MagoCaveira->ac[ATAQUE1].inicioX + 1) {
			if (Principal->acao_atual != APANHA_PRINCIPAL)
				Principal->vida_atual -= MagoCaveira->dano;
			Principal->acao_atual = APANHA_PRINCIPAL;
		}
	}
	MagoCaveira->caixa.x0 = MagoCaveira->cx + 30;
	MagoCaveira->caixa.x1 = MagoCaveira->cx - 25;
	MagoCaveira->caixa.y0 = MagoCaveira->cy + 70;
	MagoCaveira->caixa.y1 = MagoCaveira->cy + 90;
}
void comportamento_slime(struct Inimigo* Slime, struct Carinha* Principal) {
	int a = 1;

	Slime->caixa.x0 = Slime->cx + 30;
	Slime->caixa.x1 = Slime->cx - 25;
	Slime->caixa.y0 = Slime->cy + 70;
	Slime->caixa.y1 = Slime->cy + 90;


	if (!Slime->morto) {
		if (!Slime->block) {
			if (Slime->cx < Principal->cx)
				Slime->direita = ALLEGRO_FLIP_HORIZONTAL;
			else Slime->direita = 0;

			if (Slime->direita == 0)
				a = -1;

			Slime->acao_atual = PARADO;
			if (dist(Slime->cx, Slime->cy, Principal->cx, Principal->cy) < 100) {
				Slime->acao_atual = ATAQUE1;
				Slime->block = true;
			}
			else if (dist(Slime->cx, Slime->cy, Principal->cx, Principal->cy) < 600) {
				Slime->acao_atual = CORRENDO;
				Slime->dx += a * Slime->veloc;
			}
			if (Slime->vida_atual <= 0) {
				Slime->acao_atual = MORRE;
				Slime->block = true;
				Slime->apanha = false;
			}
		}
		else if (Slime->ac[MORRE].col_atual == Slime->ac[MORRE].finalX - 1)
			Slime->morto = true;
		if (Slime->acao_atual == ATAQUE1 && Principal->apanha && dist(Slime->cx, Slime->cy, Principal->cx, Principal->cy) < 150 && Slime->ac[ATAQUE1].col_atual == Slime->ac[ATAQUE1].inicioX + 1) {
			if (Principal->acao_atual != APANHA_PRINCIPAL)
				Principal->vida_atual -= Slime->dano;
			Principal->acao_atual = APANHA_PRINCIPAL;
		}
	}
	Slime->caixa.x0 = Slime->cx - 25;
	Slime->caixa.x1 = Slime->cx + 25;
	Slime->caixa.y0 = Slime->cy - 10;
	Slime->caixa.y1 = Slime->cy + 35;
}