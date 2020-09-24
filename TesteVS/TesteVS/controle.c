#include "classes.h"
#include "macros.h"


void le_teclado_baixo(struct Carinha* Principal,struct Hitbox* Chao,int codigo) {
		switch (codigo) {
		case ALLEGRO_KEY_D:
			reseta_acoes(Principal, 20, CORRENDO_PRINCIPAL, Principal->direita);
			Principal->direita = 0;
			Principal->acao_atual = CORRENDO_PRINCIPAL;
			Principal->acao_espera = CORRENDO_PRINCIPAL;
			break;
		case ALLEGRO_KEY_A:
			reseta_acoes(Principal, 20, CORRENDO_PRINCIPAL, Principal->direita);
			Principal->direita = ALLEGRO_FLIP_HORIZONTAL;
			Principal->acao_atual = CORRENDO_PRINCIPAL;
			Principal->acao_espera = CORRENDO_PRINCIPAL;
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
			if (Principal->conta_pulo == 1) {
			Principal->acao_espera = PULO2_PRINCIPAL;
			Principal->conta_pulo ++;
			}
			else if(colisao(&Principal->caixa, Chao)) {
			Principal->acao_atual = PULO1_PRINCIPAL;
			Principal->conta_pulo++;
			}
			if (Principal->conta_pulo > 1)
				Principal->conta_pulo = 0;
			Principal->block = true;
			break;
		case ALLEGRO_KEY_J:
			reseta_acoes(Principal, 20, ATAQUE1_PRINCIPAL, Principal->direita);
			if (Principal->conta_ataque == 2) {
				Principal->acao_espera = ATAQUE3_PRINCIPAL;
				Principal->conta_ataque = 0;
			}
			else if (Principal->conta_ataque == 1) {
				Principal->acao_espera= ATAQUE2_PRINCIPAL;
				Principal->conta_ataque++;
			}
			else if(!Principal->block){
				Principal->acao_atual = ATAQUE1_PRINCIPAL;
				Principal->conta_ataque ++;
			}
			Principal->block = true;
			break;
		}
	if(Principal->acao_atual != ATAQUE1_PRINCIPAL && Principal->acao_atual != ATAQUE2_PRINCIPAL && Principal->ac[Principal->acao_atual].col_atual <= 2)
		Principal->conta_ataque = 0;
}

void le_teclado_alto(struct Carinha* Principal, int codigo){
	switch (codigo) {
	case ALLEGRO_KEY_D:
		Principal->acao_espera = 0;
		if (Principal->acao_atual == CORRENDO_PRINCIPAL && Principal->direita == 0)
			Principal->acao_atual = RESPIRA_PRINCIPAL;
		reseta_acao(&Principal->ac[CORRENDO_PRINCIPAL]);
		break;
	case ALLEGRO_KEY_A:
		Principal->acao_espera = 0;
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