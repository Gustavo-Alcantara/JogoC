#include "classes.h"

void anima(ALLEGRO_EVENT* evento, Carinha* boneco, int indice) {
	int coluna_atual = boneco->ac[indice].inicio[0];
	int linha_atual = boneco->ac[indice].inicio[1];
	int cont_frames = 0;

	while (coluna_atual <= boneco->ac[indice].final[0] && linha_atual <= boneco->ac[indice].final[1]){
		al_wait_for_event(fila_eventos, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			cont_frames++;
			if (cont_frames >= boneco->ac[indice].num_frames) {
				cont_frames = 0;
				coluna_atual++;
				if (coluna_atual > boneco->imagem_boneco.num_col) {
					coluna_atual = 0;
					linha_atual++;
				}
			}
		}

	}

}