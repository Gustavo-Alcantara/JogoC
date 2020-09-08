#include "classes.h"
#include "macros.h"

bool colisao(struct Hitbox* caixa1, struct Hitbox* caixa2) {
	if (caixa1->x1 > caixa2->x0 && caixa1->x1 < caixa2->x1 && caixa1->y1 > caixa2->y0 && caixa1->y1 < caixa2->y1)
		return true;
	return false;
}
void comportamento_goblin(struct Carinha* Goblin, struct Carinha* Principal, struct Projetil* Bomba) {
	int a = 1;
	if (!Goblin->block) {
		if (Goblin->dx < Principal->dx - 50)
			Goblin->direita = 0;
		else Goblin->direita = ALLEGRO_FLIP_HORIZONTAL;

		if (Goblin->cx + 74 > Principal->cx && Principal->cx > Goblin->cx - 74) {
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
	}
	if (Goblin->acao_atual == TACA_BOMBAGOBLIN && Goblin->ac[TACA_BOMBAGOBLIN].col_atual == Goblin->ac[TACA_BOMBAGOBLIN].finalX)
		Bomba->existe = true;
}
