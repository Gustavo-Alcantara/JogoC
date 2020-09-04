#include "classes.h"

void anima_personagem(struct Carinha* boneco, int indice) {
	int x_folha;
	int y_folha;

	boneco->cx = boneco->dx + boneco->imagem_personagem.largura / 2;
	boneco->cy = boneco->dy + boneco->imagem_personagem.altura / 2;

	if (boneco->ac[indice].frame_atual >= boneco->ac[indice].num_frames) {
		boneco->ac[indice].frame_atual = 0;
		boneco->ac[indice].col_atual++;
		if (boneco->ac[indice].col_atual > boneco->imagem_personagem.num_col) {
			boneco->ac[indice].col_atual = 0;
			boneco->ac[indice].lin_atual++;
		}
		if (boneco->ac[indice].lin_atual >= boneco->ac[indice].finalY && boneco->ac[indice].col_atual > boneco->ac[indice].finalX) {
			boneco->ac[indice].col_atual = boneco->ac[indice].inicioX;
			boneco->ac[indice].lin_atual = boneco->ac[indice].inicioY;
		}
	}
	
	y_folha = boneco->ac[indice].lin_atual * boneco->imagem_personagem.altura_folha;
	x_folha = boneco->ac[indice].col_atual * boneco->imagem_personagem.largura_folha;

	al_draw_scaled_bitmap(boneco->imagem_personagem.png, x_folha, y_folha, boneco->imagem_personagem.largura_folha,
			boneco->imagem_personagem.altura_folha, boneco->dx, boneco->dy,
			boneco->imagem_personagem.largura, boneco->imagem_personagem.altura, boneco->direita);

		boneco->ac[indice].frame_atual++;
}
void reseta_acoes(struct Carinha*boneco, int num_acoes, int indice,int direita) {
	for (int i = 0; i <= num_acoes; i++) {
		if (i != indice) {
			boneco->ac[i].frame_atual = 0;
			boneco->ac[i].col_atual = boneco->ac[i].inicioX;
			boneco->ac[i].lin_atual = boneco->ac[i].inicioY;
		}
	}
	boneco->direita = direita;
}
void anima_projetil(struct Projetil* Bomba) {
	int x_folha;

	if (Bomba->frame_atual >= Bomba->num_frames) {
		Bomba->frame_atual = 0;
		Bomba->col_atual++;
		if (Bomba->col_atual == Bomba->img.num_col)
			al_destroy_bitmap(Bomba->img.png);
		else {
			x_folha = Bomba->col_atual * Bomba->img.largura_folha;
			al_draw_scaled_bitmap(Bomba->img.png, x_folha, 0,Bomba->img.largura_folha,
				Bomba->img.altura_folha, Bomba->dx, Bomba->dy,
				Bomba->img.largura, Bomba->img.altura,0);
			Bomba->frame_atual++;
		}
	}
}