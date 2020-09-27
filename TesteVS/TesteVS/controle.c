#include "classes.h"
#include "macros.h"


void le_teclado_baixo(struct Carinha* Principal,struct Hitbox* Chao[10],int codigo) {
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
				if (colisao(&Principal->caixa, Chao)) {
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
void personagem_principal(struct Carinha* Principal, struct Hitbox* Chao[10], struct Inimigo Ativos) {
	Principal->caixa.x0 = Principal->cx - 25;
	Principal->caixa.x1 = Principal->cx + 20;
	Principal->caixa.y0 = Principal->cy - 30;
	Principal->caixa.y1 = Principal->cy + 35;
	Principal->espera++;
	if (Principal->espera > 15) {
		Principal->ataca = true;
		Principal->espera = 0;
	}
	if (Principal->acao_atual == CORRENDO_PRINCIPAL || Principal->acao_atual == DESLIZA_PRINCIPAL) {
		if (Principal->direita == 0)
			Principal->dx += Principal->veloc;
		else
			Principal->dx -= Principal->veloc;
	}
	else if ((Principal->acao_atual == ATAQUE1_PRINCIPAL || Principal->acao_atual == ATAQUE2_PRINCIPAL || Principal->acao_atual == ATAQUE3_PRINCIPAL) && dist(Principal->cx, Principal->cy, Goblin->cx, Goblin->cy) < 50 && Goblin->apanha) {
		if (Goblin->acao_atual != APANHA_GOBLIN)
			Goblin->vida_atual -= Principal->dano;
		Goblin->acao_atual = APANHA_GOBLIN;
		Goblin->block = true;
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

	if (!colisao(&Principal->caixa, &Chao[0]) && (Principal->acao_atual != PULO1_PRINCIPAL && Principal->acao_atual != PULO2_PRINCIPAL)) {
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
	if (colisao(&Principal->caixa, &Chao[0])) {
		Principal->queda = 0;
		Principal->conta_pulo = 0;
	}
}