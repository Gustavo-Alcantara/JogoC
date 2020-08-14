#include "classes.h"

void anima(ALLEGRO_EVENT* evento, Personagem* boneco,int indice) {
	int coluna_atual = boneco->ac[indice].inicio[0];
	int linha_atual = boneco->ac[indice].inicio[1];
	int cont_frames = 0;

	while (coluna_atual<= boneco->ac[indice].final[0] && linha_atual <= boneco->ac[indice].final[1]) {
		al_wait_for_event(fila_eventos, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			cont_frames++;
			if (cont_frames >= boneco->ac[indice].num_frames) {
				cont_frames = 0;
				coluna_atual++;
				if (coluna_atual >= boneco->imagem_boneco.numero_col) {
					linha_atual++;
					coluna_atual = 0;
				}
			}
			
		}
	}
}
void anima_respirando(ALLEGRO_EVENT* evento) {
	bool desenha = false;
	coluna_atual = 0;
	linha_atual = 0;
	desloc += 3;
	while (evento->type != ALLEGRO_EVENT_KEY_DOWN) {
		al_wait_for_event(fila_eventos, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			cont_frames++;
			if (cont_frames >= frames_sprite) {
				cont_frames = 0;
				coluna_atual++;
				if (coluna_atual >= 4)
					coluna_atual = 0;
				regiao_y_folha = linha_atual * sprite_altura;
				regiao_x_folha = coluna_atual * sprite_largura;
			}
			for (i = 10; i > 0; i--)
				al_draw_scaled_bitmap(layers[i], 0, 200, LARGURA_TELA, 593, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
			al_draw_scaled_bitmap(folha, regiao_x_folha, regiao_y_folha, sprite_largura, sprite_altura, (LARGURA_TELA / 400) + desloc, 30 * ALTURA_TELA / 40, 90, 70, 0);
			al_flip_display();
		}
	}
}