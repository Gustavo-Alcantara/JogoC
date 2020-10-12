#include "classes.h"
#include "macros.h"

double dist(float cx0, float cy0, float cx1, float cy1) {
	return sqrt(((double)cx1 - cx0) * ((double)cx1 - cx0) + ((double)cy1 - cy0) * ((double)cy1 - cy0));
}
bool colisao(struct Hitbox* caixa1, struct Hitbox* caixa2) {
	if (caixa1->x1 >= caixa2->x0 && caixa1->x1 < caixa2->x1 && caixa1->y1 >= caixa2->y0 && caixa1->y1 <= caixa2->y1) 
		return true;
	else if(caixa1->x0 >= caixa2->x0 && caixa1->x0 <= caixa2->x1 && caixa1->y0 >= caixa2->y0 && caixa1->y0 <= caixa2->y1){
		return true;
	}
	else if (caixa2->x0 >= caixa1->x0 && caixa2->x0 <= caixa1->x1 && caixa2->y0 >= caixa1->y0 && caixa2->y0 < caixa1->y1) {
		return true;
	}
	else if (caixa2->x1 >= caixa1->x0 && caixa2->x1 <= caixa1->x1 && caixa2->y1 >= caixa1->y0 && caixa2->y1 <= caixa1->y1) {
		return true;
	}
	return false;
}
int colisao_chao(struct Hitbox* Bicho, struct Hitbox Vetor_Chao[10]) {
	struct Hitbox* p;
	for (int i = 0; i < 10; i++) {
		p = &Vetor_Chao[i];
		if (colisao(Bicho, p))
			return i + 1;
	}
	return 0;
}
void comportamento_goblin(struct Inimigo* Goblin, struct Carinha* Principal) {
	int a = 1;
	Goblin->espera++;
	if (!Goblin->morto){
		if (Principal->acao_atual == ATAQUE1_PRINCIPAL && Goblin->apanha && dist(Goblin->cx, Goblin->cy, Principal->cx, Principal->cy) < 75 && Goblin->espera >= 180) {
			Goblin->acao_atual = 6;
			Goblin->block = true;
			Goblin->apanha = false;
			Goblin->espera = 0;
		}
		if (!Goblin->block) {
			if (Goblin->dx < Principal->dx - 100)
				Goblin->direita = 0;
			else Goblin->direita = ALLEGRO_FLIP_HORIZONTAL;

			if (Goblin->cx + 100 > Principal->cx && Principal->cx > Goblin->cx - 100) {
				Goblin->acao_atual = ATAQUE2;
				Goblin->block = true;
			}
			else if (Goblin->cx + 400 > Principal->cx && Principal->cx > Goblin->cx - 400)
				Goblin->acao_atual = CORRENDO;
			else if (Goblin->cx + 800 > Principal->cx && Principal->cx > Goblin->cx - 800 /*&& !Bomba->existe*/) {
				Goblin->acao_atual = ATAQUE1;
				if (Goblin->direita == 0)
					a = -1;
				Goblin->block = true;
				/*Bomba->xi = Goblin->cx - Bomba->img.largura / 2 - a * 40;
				Bomba->yi = Goblin->cy - Bomba->img.largura / 2 - 10;
				Bomba->dx = Bomba->xi;*/
			}

			else
				Goblin->acao_atual = PARADO;
			if (Goblin->acao_atual == CORRENDO) {
				if (Goblin->direita == 0)
					Goblin->dx += Goblin->veloc;
				else Goblin->dx -= Goblin->veloc;
			}
			
			if (Goblin->vida_atual <= 0) {
				Goblin->acao_atual = MORRE;
				Goblin->block = true;
				Goblin->apanha = false;
			}
			Goblin->caixa.x0 = Goblin->cx - 30;
			Goblin->caixa.x1 = Goblin->cx + 30;
			Goblin->caixa.y0 = Goblin->cy - 30;
			Goblin->caixa.y1 = Goblin->cy + 70;
			

		}
		else {
			if (Goblin->ac[MORRE].col_atual == 39)
				Goblin->morto = true;
		}
		if (dist(Principal->cx, Principal->cy, Goblin->cx, Goblin->cy) < 100 && Principal->apanha && Goblin->ac[ATAQUE2].col_atual == Goblin->ac[ATAQUE2].finalX - 2) {
			if (Principal->acao_atual != APANHA_PRINCIPAL)
				Principal->vida_atual -= Goblin->dano;
			Principal->acao_atual = APANHA_PRINCIPAL;
			Principal->block = true;
		}
		if (dist(Principal->cx, Principal->cy, Goblin->cx, Goblin->cy) < 150 && Principal->apanha && Goblin->ac[6].col_atual == Goblin->ac[6].finalX - 2) {
			if (Principal->acao_atual != APANHA_PRINCIPAL)
				Principal->vida_atual -= Goblin->dano;
			Principal->acao_atual = APANHA_PRINCIPAL;
			Principal->block = true;
		}
		if (Goblin->acao_atual == 6) {
			if (Goblin->direita == 0)
				Goblin->dx -= 0.3*Goblin->veloc;
			else Goblin->dx += 0.3 * Goblin->veloc;
		}
	/*if (Goblin->acao_atual == ATAQUE1 && Goblin->ac[ATAQUE1].col_atual == Goblin->ac[ATAQUE1].finalX - 1)
		Bomba->existe = true;*/
	}
	Goblin->caixa.x0 = Goblin->cx - 40;
	Goblin->caixa.x1 = Goblin->cx + 40;
	Goblin->caixa.y0 = Goblin->cy - 50;
	Goblin->caixa.y1 = Goblin->cy + 70;
}
void fisica_bomba(struct Projetil* Bomba,struct Inimigo* Goblin, struct Carinha* Principal, struct Hitbox (*Vetor_Chao)[10]){
	if (Bomba->existe) {
		int a = 1;

		if (Goblin->direita == 0)
			a = -1;

		if (Bomba->estado == 0) {
			Bomba->dx -= a * Bomba->veloc;
			Bomba->dy = Bomba->yi + 0.0025 * ((double)Bomba->dx - Bomba->xi) * ((double)Bomba->dx - Bomba->raiz);
		}
		Bomba->caixa.x0 = Bomba->dx + Bomba->img.largura / 2 - 20;
		Bomba->caixa.x1 = Bomba->dx + Bomba->img.largura / 2 + 20;
		Bomba->caixa.y0 = Bomba->dy + Bomba->img.altura / 2 - 20;
		Bomba->caixa.y1 = Bomba->dy + Bomba->img.altura / 2 + 20;

		if (colisao(&Bomba->caixa, Vetor_Chao[0]))
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
	Armadura->caixa.x0 = Armadura->cx + 20;
	Armadura->caixa.x1 = Armadura->cx - 20;
	Armadura->caixa.y0 = Armadura->cy - 50;
	Armadura->caixa.y1 = Armadura->cy + 70;
	Armadura->espera++;

	int a = 1;

	if (Armadura->direita == 0)
		a = -1;

	if (!Armadura->morto) {
		if (Principal->acao_atual == ATAQUE1_PRINCIPAL && Armadura->apanha && dist(Armadura->cx,Armadura->cy,Principal->cx,Principal->cy) < 150 && Armadura->espera >= 180) {
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

			if (Armadura->cx + 100 > Principal->cx && Principal->cx > Armadura->cx - 100) {
				Armadura->acao_atual = 3;
				Armadura->block = true;
			}
			else if (Armadura->cx + 150 > Principal->cx && Principal->cx > Armadura->cx - 150) {
				Armadura->acao_atual = 5;
				Armadura->block = true;
			}
			else if (Armadura->cx + 400 > Principal->cx && Principal->cx > Armadura->cx - 400)
				Armadura->acao_atual = 2;
			

		}
		if ((Armadura->acao_atual == 3 || Armadura->acao_atual == 5) && Principal->apanha && dist(Armadura->cx, Armadura->cy, Principal->cx, Principal->cy) < 150 && Armadura->ac[Armadura->acao_atual].col_atual == Armadura->ac[Armadura->acao_atual].inicioX + 1) {
			if (Principal->acao_atual != APANHA_PRINCIPAL)
				Principal->vida_atual -= Armadura->dano;
			Principal->acao_atual = APANHA_PRINCIPAL;
		}

		if (Armadura->vida_atual <= 0)
			Armadura->morto = true;
		if(Armadura->acao_atual == 6)
			Armadura->dx += a * Armadura->veloc;
	}
	Armadura->cx = Armadura->dx + Armadura->imagem_personagem.largura / 2;
	Armadura->cy = Armadura->dy + Armadura->imagem_personagem.altura / 2;
	Armadura->caixa.x0 = Armadura->cx + 20;
	Armadura->caixa.x1 = Armadura->cx - 20;
	Armadura->caixa.y0 = Armadura->cy + 50;
	Armadura->caixa.y1 = Armadura->cy + 70;
}
void comportamento_olho(struct Inimigo* Olho, struct Carinha* Principal) {
	int a = 1;
	int b = 1;

	Olho->cx = Olho->dx + Olho->imagem_personagem.largura / 2;
	Olho->cy = Olho->dy + Olho->imagem_personagem.altura / 2;

	if (!Olho->morto) {
		if (!Olho->block) {
			if (Olho->cx < Principal->cx)
				Olho->direita = 0;
			else Olho->direita = ALLEGRO_FLIP_HORIZONTAL;

			if (Olho->direita == 0)
				a = -1;
			if (Olho->cy < Principal->cy)
				b = -1;
			Olho->acao_atual = VOA;
			if (dist(Olho->cx, Olho->cy, Principal->cx, Principal->cy) < 50) {
				Olho->acao_atual = 1;
				Olho->block = true;
			}
			else if (dist(Olho->cx, Olho->cy, Principal->cx, Principal->cy)<600) {
				if (Olho->cx < Principal->cx || Olho->cx > Principal->cx)
					Olho->dx -= a * Olho->veloc;
				if (Olho->cy < Principal->cy || Olho->cy > Principal->cy)
					Olho->dy -= b * Olho->veloc;
			}
			if (Olho->vida_atual <= 0) {
				Olho->acao_atual = MORRE;
				Olho->block = true;
				Olho->apanha = false;
			}
		}
		else if(Olho->ac[MORRE].col_atual == Olho->ac[MORRE].finalX-1)
			Olho->morto = true;
	}
}