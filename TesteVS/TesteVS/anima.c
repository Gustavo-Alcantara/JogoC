#include "classes.h"

void anima(ALLEGRO_EVENT* evento,ALLEGRO_EVENT_QUEUE* fila,struct Carinha* boneco, int indice) {
	int col = boneco->ac[indice].inicio[0];
	int lin = boneco->ac[indice].inicio[1];
	int frames = 0;
	int x_folha;
	int y_folha;

	while (col <= boneco->ac[indice].final[0] && lin <= boneco->ac[indice].final[1]){
		al_wait_for_event(fila, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			frames++;
			if (frames >= boneco->ac[indice].num_frames) {
				frames = 0;
				col++;
				if (col > boneco->imagem_personagem.num_col) {
					col = 0;
					lin++;
				}
				y_folha = lin * boneco->imagem_personagem.altura;
				x_folha = col * boneco->imagem_personagem.largura;

				if (boneco->direita)
					al_draw_scaled_bitmap(boneco->imagem_personagem.png, x_folha, y_folha, boneco->imagem_personagem.largura_folha, 
						boneco->imagem_personagem.altura_folha, boneco->dx, boneco->dy, 
						boneco->imagem_personagem.largura, boneco->imagem_personagem.altura,0);
				else { al_draw_scaled_bitmap(boneco->imagem_personagem.png, x_folha, y_folha, boneco->imagem_personagem.largura_folha, 
					boneco->imagem_personagem.altura_folha, boneco->dx, boneco->dy, 
					boneco->imagem_personagem.largura, boneco->imagem_personagem.altura,ALLEGRO_FLIP_HORIZONTAL); }
				al_flip_display();
			}
		}
	}
}
