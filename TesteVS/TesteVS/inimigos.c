#include "classes.h"

void atualiza_inimigos(struct Inimigo* Ativos, int tam) {
	if (Ativos->vida_atual > 0 && !Ativos->morto)
		al_draw_line(Ativos->caixa.x0, Ativos->caixa.y0, Ativos->caixa.x0 + (Ativos->caixa.x1 - Ativos->caixa.x0) * Ativos->vida_atual / Ativos->vida_total, Ativos->caixa.y0, al_map_rgb(255, 0, 0), 2);
	if (!Ativos->morto)
		anima_Inimigo(Ativos, Ativos->acao_atual);
}