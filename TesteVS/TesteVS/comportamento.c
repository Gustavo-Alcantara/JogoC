#include "classes.h"
#include "macros.h"
double dist(float cx0, float cy0, float cx1, float cy1) {
	return sqrt((cx1 - cx0) * (cx1 - cx0) + (cy1 - cy0) * (cy1 - cy0));
}
bool colisao(struct Hitbox* caixa1, struct Hitbox* caixa2) {
	if (caixa1->x1 > caixa2->x0 && caixa1->x1 < caixa2->x1 && caixa1->y1 > caixa2->y0 && caixa1->y1 < caixa2->y1) 
		return true;
	else if(caixa1->x0 > caixa2->x0 && caixa1->x0 < caixa2->x1 && caixa1->y0 > caixa2->y0 && caixa1->y0 < caixa2->y1){
		return true;
	}
	else if (caixa2->x0 > caixa1->x0 && caixa2->x0 < caixa1->x1 && caixa2->y0 > caixa1->y0 && caixa2->y0 < caixa1->y1) {
		return true;
	}
	else if (caixa2->x1 > caixa1->x0 && caixa2->x1 < caixa1->x1 && caixa2->y1 > caixa1->y0 && caixa2->y1 < caixa1->y1) {
		return true;
	}
	return false;
}
void comportamento_goblin(struct Inimigo* Goblin, struct Carinha* Principal, struct Projetil* Bomba) {
	int a = 1;
	if (!Goblin->morto){
		if (!Goblin->block) {
			if (Goblin->dx < Principal->dx - 50)
				Goblin->direita = 0;
			else Goblin->direita = ALLEGRO_FLIP_HORIZONTAL;

			if (Goblin->cx + 50 > Principal->cx && Principal->cx > Goblin->cx - 50) {
				Goblin->acao_atual = GOBLIN_BATENDO;
				Goblin->block = true;
			}
			else if (Goblin->cx + 200 > Principal->cx && Principal->cx > Goblin->cx - 200)
				Goblin->acao_atual = CORRENDO_GOBLIN;
			else if (Goblin->cx + 400 > Principal->cx && Principal->cx > Goblin->cx - 400 && !Bomba->existe) {
				Goblin->acao_atual = TACA_BOMBAGOBLIN;
				if (Goblin->direita == 0)
					a = -1;
				Goblin->block = true;
				Bomba->xi = Goblin->cx - Bomba->img.largura / 2 - a * 40;
				Bomba->yi = Goblin->cy - Bomba->img.largura / 2 - 10;
				Bomba->dx = Bomba->xi;
			}

			else
				Goblin->acao_atual = PARADO_GOBLIN;
			if (Goblin->acao_atual == CORRENDO_GOBLIN) {
				if (Goblin->direita == 0)
					Goblin->dx += Goblin->veloc;
				else Goblin->dx -= Goblin->veloc;
			}
			if (Goblin->vida_atual <= 0) {
				Goblin->acao_atual = MORRE_GOBLIN;
				Goblin->block = true;
				Goblin->apanha = false;
			}
			Goblin->caixa.x0 = Goblin->cx - 30;
			Goblin->caixa.x1 = Goblin->cx + 30;
			Goblin->caixa.y0 = Goblin->cy - 30;
			Goblin->caixa.y1 = Goblin->cy + 35;
			

		}
		else {
			if (Goblin->ac[MORRE_GOBLIN].col_atual == 39)
				Goblin->morto = true;
		}
		if (dist(Principal->cx, Principal->cy, Goblin->cx, Goblin->cy) < 50 && Principal->apanha && Goblin->ac[GOBLIN_BATENDO].col_atual == Goblin->ac[GOBLIN_BATENDO].finalX - 2) {
			if (Principal->acao_atual != APANHA_PRINCIPAL)
				Principal->vida_atual -= Goblin->dano;
			Principal->acao_atual = APANHA_PRINCIPAL;
			Principal->block = true;
		}
	if (Goblin->acao_atual == TACA_BOMBAGOBLIN && Goblin->ac[TACA_BOMBAGOBLIN].col_atual == Goblin->ac[TACA_BOMBAGOBLIN].finalX)
		Bomba->existe = true;
	}
}
