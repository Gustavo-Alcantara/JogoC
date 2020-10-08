#include "classes.h"
#include "macros.h"


void le_teclado_baixo(struct Carinha* Principal,struct Hitbox (*Chao)[10],int codigo) {
		switch (codigo) {
		case ALLEGRO_KEY_D:
			reseta_acoes(Principal, 20, CORRENDO_PRINCIPAL, Principal->direita);
			Principal->direita = 0;
			Principal->acao_atual = CORRENDO_PRINCIPAL;
			Principal->acao_espera = CORRENDO_PRINCIPAL;
			Principal->movendo = true;
			break;
		case ALLEGRO_KEY_A:
			reseta_acoes(Principal, 20, CORRENDO_PRINCIPAL, Principal->direita);
			Principal->direita = ALLEGRO_FLIP_HORIZONTAL;
			Principal->acao_atual = CORRENDO_PRINCIPAL;
			Principal->acao_espera = CORRENDO_PRINCIPAL;
			Principal->movendo = true;
			break;
		case ALLEGRO_KEY_LSHIFT:
			reseta_acoes(Principal, 20, CORRENDO_PRINCIPAL, Principal->direita);
			Principal->acao_atual = DESLIZA_PRINCIPAL;
			Principal->block = true;
			Principal->apanha = false;
			break;
		case ALLEGRO_KEY_S:
			reseta_acoes(Principal, 20, ABAIXADO_PRINCIPAL, Principal->direita);
			Principal->acao_atual = ABAIXADO_PRINCIPAL;
			Principal->apanha = true;
			break;
		case ALLEGRO_KEY_W:
			reseta_acoes(Principal, 20, PULO1_PRINCIPAL, Principal->direita);
			if (Principal->conta_pulo == 0) {
				if (colisao_chao(&Principal->caixa, Chao)) {
					Principal->acao_atual = PULO1_PRINCIPAL;
				}
				else {
					Principal->acao_atual = PULO2_PRINCIPAL;
					Principal->conta_pulo++;
				}
			}
			break;
		case ALLEGRO_KEY_J:
			reseta_acoes(Principal, 20, ATAQUE1_PRINCIPAL, Principal->direita);
			if (Principal->ataca) {
				if (Principal->conta_ataque == 2) {
					Principal->acao_atual = ATAQUE3_PRINCIPAL;
					Principal->conta_ataque = 0;
					Principal->ataca = false;
				}
				else if (Principal->conta_ataque == 1) {
					Principal->acao_atual = ATAQUE2_PRINCIPAL;
					Principal->conta_ataque++;
				}
				else {
					Principal->acao_atual = ATAQUE1_PRINCIPAL;
					Principal->conta_ataque++;
				}
				Principal->espera = 0;
				Principal->block = true;
			}
			break;
		}
	if(Principal->acao_atual != ATAQUE1_PRINCIPAL && Principal->acao_atual != ATAQUE2_PRINCIPAL)
		Principal->conta_ataque = 0;
}

void le_teclado_alto(struct Carinha* Principal, int codigo){
	switch (codigo) {
	case ALLEGRO_KEY_D:
		Principal->acao_espera = 0;
		if(Principal->direita == 0)
			Principal->movendo = false;
		if (Principal->acao_atual == CORRENDO_PRINCIPAL && Principal->direita == 0){}
			Principal->acao_atual = RESPIRA_PRINCIPAL;
		reseta_acao(&Principal->ac[CORRENDO_PRINCIPAL]);
		break;
	case ALLEGRO_KEY_A:
		Principal->acao_espera = 0;
		if (Principal->direita == ALLEGRO_FLIP_HORIZONTAL)
			Principal->movendo = false;
		if (Principal->acao_atual == CORRENDO_PRINCIPAL && Principal->direita == ALLEGRO_FLIP_HORIZONTAL)
			Principal->acao_atual = RESPIRA_PRINCIPAL;
		reseta_acao(&Principal->ac[CORRENDO_PRINCIPAL]);
		break;
	case ALLEGRO_KEY_S:
		Principal->acao_espera = 0;
		if (Principal->acao_atual == ABAIXADO_PRINCIPAL )
			Principal->acao_atual = RESPIRA_PRINCIPAL;
		reseta_acao(&Principal->ac[CORRENDO_PRINCIPAL]);
		break;
	}
}
void personagem_principal(struct Carinha* Principal, struct Hitbox (*Chao)[10], struct Inimigo Goblin[5],int desloc_tela) {
	Principal->caixa.x0 = Principal->cx - 50;
	Principal->caixa.x1 = Principal->cx + 40;
	Principal->caixa.y0 = Principal->cy - 60;
	Principal->caixa.y1 = Principal->cy + 70;
	Principal->espera++;
	if (Principal->espera > 15) {
		Principal->ataca = true;
		Principal->espera = 0;
	}
	if (Principal->acao_atual == CORRENDO_PRINCIPAL || Principal->acao_atual == DESLIZA_PRINCIPAL) {
		if (Principal->direita == 0) {
			Principal->dx += Principal->veloc;
		}
		else {
			Principal->dx -= Principal->veloc;
		}
	}
	else if (Principal->acao_atual == ATAQUE1_PRINCIPAL || Principal->acao_atual == ATAQUE2_PRINCIPAL || Principal->acao_atual == ATAQUE3_PRINCIPAL) {
		for (int i = 0; i < 5; i++) {
			if (!Goblin[i].morto) {
				if (dist(Principal->cx, Principal->cy, Goblin[i].cx, Goblin[i].cy) < 100 && Goblin[i].apanha) {
					if (Principal->ac[Principal->acao_atual].col_atual == Principal->ac[Principal->acao_atual].inicioX + 1)
						Goblin[i].vida_atual -= Principal->dano;
					Goblin[i].acao_atual = APANHA;
					Goblin[i].block = true;
				}
			}
		}
	}
	else if (Principal->acao_atual == PULO1_PRINCIPAL || Principal->acao_atual == PULO2_PRINCIPAL) {
		if (!Principal->pula && Principal->ac[PULO2_PRINCIPAL].col_atual == Principal->ac[PULO2_PRINCIPAL].finalX && Principal->ac[PULO2_PRINCIPAL].lin_atual == Principal->ac[PULO2_PRINCIPAL].finalY)
			Principal->acao_atual = CAIR_PRINCIPAL;
		if (Principal->acao_atual == PULO1_PRINCIPAL && Principal->ac[PULO1_PRINCIPAL].col_atual == 3)
			Principal->dy -= 2 * Principal->altura_pulo;
		else if (Principal->acao_atual == PULO2_PRINCIPAL)
			Principal->dy -= Principal->altura_pulo;
		if (Principal->movendo) {
			if (Principal->direita == 0)
				Principal->dx += Principal->veloc;
			else
				Principal->dx -= Principal->veloc;
		}
	}
	else if (Principal->acao_atual == RESPIRA_PRINCIPAL && Principal->ac[RESPIRA_PRINCIPAL].col_atual > 2) {
		Principal->conta_ataque = 0;
	}
	int coli = colisao_chao(&(Principal->caixa), Chao);
	if (colisao_chao(&(Principal->caixa), Chao)) {
		Principal->queda = 0;
		Principal->conta_pulo = 0;
		Principal->acao_espera = RESPIRA_PRINCIPAL;
	}
	else if ((Principal->acao_atual != PULO1_PRINCIPAL && Principal->acao_atual != PULO2_PRINCIPAL)) {
		Principal->dy += Principal->queda;
		Principal->queda += 0.2;
		Principal->acao_atual = CAIR_PRINCIPAL;
		if (Principal->movendo) {
			if (Principal->direita == 0)
				Principal->dx += Principal->veloc;
			else
				Principal->dx -= Principal->veloc;
		}
		Principal->block = true;
	}
}