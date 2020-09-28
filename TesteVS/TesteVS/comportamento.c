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
void fisica_bomba(struct Projetil* Bomba,struct Inimigo* Goblin, struct Carinha* Principal, struct Hitbox* Vetor_Chao[10]) {
	if (Bomba->existe) {
		int a = 1;

		if (Goblin->direita == 0)
			a = -1;

		if (Bomba->estado == 0) {
			Bomba->dx -= a * Bomba->veloc;
			Bomba->dy = Bomba->yi + 0.0025 * (Bomba->dx - Bomba->xi) * (Bomba->dx - Bomba->raiz);
		}
		Bomba->caixa.x0 = Bomba->dx + Bomba->img.largura / 2 - 10;
		Bomba->caixa.x1 = Bomba->dx + Bomba->img.largura / 2 + 10;
		Bomba->caixa.y0 = Bomba->dy + Bomba->img.altura / 2 - 10;
		Bomba->caixa.y1 = Bomba->dy + Bomba->img.altura / 2 + 10;

		if (colisao(&Bomba->caixa, &Vetor_Chao[0]))
			Bomba->estado = 1;
		else if (colisao(&Bomba->caixa, &Principal->caixa) && Principal->apanha) {
			if (Bomba->estado == 0)
				Principal->vida_atual -= Bomba->dano;
			Bomba->estado = 1;
			Principal->acao_atual = APANHA_PRINCIPAL;
			Principal->block = true;
		}

	}
	else
		Bomba->raiz = Principal->cx - 50;
}
void comportamento_armadura(struct Inimigo* Armadura, struct Carinha* Principal) {
	Armadura->cx = Armadura->dx + Armadura->imagem_personagem.largura / 2;
	Armadura->cy = Armadura->dy + Armadura->imagem_personagem.altura / 2;
	Armadura->caixa.x0 = Armadura->cx + 30;
	Armadura->caixa.x1 = Armadura->cx - 30;
	Armadura->caixa.y0 = Armadura->cy - 30;
	Armadura->caixa.y1 = Armadura->cy + 37;
	Armadura->espera++;

	int a = 1;

	if (Armadura->direita == 0)
		a = -1;

	if (!Armadura->morto) {
		if (Principal->acao_atual == ATAQUE1_PRINCIPAL && Armadura->apanha && dist(Armadura->cx,Armadura->cy,Principal->cx,Principal->cy) < 75 && Armadura->espera >= 180) {
			Armadura->acao_atual = 6;
			Armadura->block = true;
			Armadura->apanha = false;
			Armadura->espera = 0;
		}
		if (!Armadura->block) {
			

			if (Armadura->cx < Principal->cx)
				Armadura->direita = 0;
			else Armadura->direita = ALLEGRO_FLIP_HORIZONTAL;

			Armadura->acao_atual = 0;

			if (Armadura->cx + 50 > Principal->cx && Principal->cx > Armadura->cx - 50) {
				Armadura->acao_atual = 3;
				Armadura->block = true;
			}
			else if (Armadura->cx + 75 > Principal->cx && Principal->cx > Armadura->cx - 75) {
				Armadura->acao_atual = 5;
				Armadura->block = true;
			}
			else if (Armadura->cx + 200 > Principal->cx && Principal->cx > Armadura->cx - 200)
				Armadura->acao_atual = 2;
			

		}
		if ((Armadura->acao_atual == 3 || Armadura->acao_atual == 5) && Principal->apanha && dist(Armadura->cx, Armadura->cy, Principal->cx, Principal->cy) < 75 && Armadura->ac[Armadura->acao_atual].col_atual == Armadura->ac[Armadura->acao_atual].inicioX + 1) {
			if (Principal->acao_atual != APANHA_PRINCIPAL)
				Principal->vida_atual -= Armadura->dano;
			Principal->acao_atual = APANHA_PRINCIPAL;
		}

		if (Armadura->vida_atual <= 0)
			Armadura->morto = true;
		if(Armadura->acao_atual == 6)
			Armadura->dx += a * Armadura->veloc;
	}
}