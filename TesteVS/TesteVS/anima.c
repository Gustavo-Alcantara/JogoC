#include "classes.h"

void anima_personagem(struct Carinha* boneco, int indice) {
	/*
		Recebe a estrutura do personagem principal;
		Confere se o frame atual � maior que o frame max da anima�ao do personagem, se for aumenta o numero de colunas
		Se a coluna atual for maior que o n�mero de colunas zera a coluna atual e passa para a proxima linha
		Confere se a linha atual � igual a linha final da a��o e a coluna atual � maior que a coluna final,
		se for coloca o personagem em a��o 0 e reseta a acao
		No final, desenha a parte da imagem condizente com a acao.

	*/

	int x_folha;
	int y_folha;

	boneco->cx = boneco->dx + boneco->imagem_personagem.largura / 2;
	boneco->cy = boneco->dy + boneco->imagem_personagem.altura / 2;

	if (boneco->ac[indice].frame_atual >= boneco->ac[indice].num_frames) {
		boneco->ac[indice].frame_atual = 0;
		boneco->ac[indice].col_atual++;
		if (boneco->ac[indice].lin_atual >= boneco->ac[indice].finalY && boneco->ac[indice].col_atual > boneco->ac[indice].finalX) {
			boneco->block = false;
			reseta_acao(&boneco->ac[indice]);
			if (indice > 2) {
				boneco->acao_atual = boneco->acao_espera;
				boneco->acao_espera = 0;
			}
			if (!boneco->apanha)
				boneco->apanha = true;
			
		}
		if (boneco->ac[indice].col_atual == boneco->imagem_personagem.num_col) {
			boneco->ac[indice].col_atual = 0;
			boneco->ac[indice].lin_atual++;
		}
	}
	
	y_folha = boneco->ac[indice].lin_atual * boneco->imagem_personagem.altura_folha;
	x_folha = boneco->ac[indice].col_atual * boneco->imagem_personagem.largura_folha;

	al_draw_scaled_bitmap(boneco->imagem_personagem.png, x_folha, y_folha, boneco->imagem_personagem.largura_folha,
			boneco->imagem_personagem.altura_folha, boneco->dx, boneco->dy,
			boneco->imagem_personagem.largura, boneco->imagem_personagem.altura, boneco->direita);

		boneco->ac[indice].frame_atual++;
}
void anima_Inimigo(struct Inimigo* boneco, int indice) {

	// Mesma fun��o, por�m recebe a estrutura do inimigo

	int x_folha;
	int y_folha;

	boneco->cx = boneco->dx + boneco->imagem_personagem.largura / 2;
	boneco->cy = boneco->dy + boneco->imagem_personagem.altura / 2;

	if (boneco->ac[indice].frame_atual >= boneco->ac[indice].num_frames) {
		boneco->ac[indice].frame_atual = 0;
		boneco->ac[indice].col_atual++;
		if (boneco->ac[indice].lin_atual >= boneco->ac[indice].finalY && boneco->ac[indice].col_atual > boneco->ac[indice].finalX) {
			boneco->block = false;
			reseta_acao(&boneco->ac[indice]);
			if (!boneco->apanha)
				boneco->apanha = true;

		}
		if (boneco->ac[indice].col_atual == boneco->imagem_personagem.num_col) {
			boneco->ac[indice].col_atual = 0;
			boneco->ac[indice].lin_atual++;
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

	// Recebe um personagem faz o mesmo que a funcao reseta_acao para todas as acoes diferentes do indice

	for (int i = 0; i <= num_acoes; i++) {
		if (i != indice) {
			boneco->ac[i].frame_atual = 0;
			boneco->ac[i].col_atual = boneco->ac[i].inicioX;
			boneco->ac[i].lin_atual = boneco->ac[i].inicioY;
		}
	}
	boneco->direita = direita;
}
void reseta_acoes_inimigo(struct Inimigo* boneco, int num_acoes, int indice) {

	//Fun��o igual � fun��o acima, porem recebe a estrutura inimigos

	for (int i = 0; i < num_acoes; i++) {
		if (i != indice) {
			boneco->ac[i].frame_atual = 0;
			boneco->ac[i].col_atual = boneco->ac[i].inicioX;
			boneco->ac[i].lin_atual = boneco->ac[i].inicioY;
		}
	}
}
void reseta_acao(struct acao*ac) {
	// Recebe uma estrutura acao e coloca o numero de frames como 0 coluna e lina atual como inicio da acao
	ac->frame_atual = 0;
	ac->col_atual = ac->inicioX;
	ac->lin_atual = ac->inicioY;
}
void anima_projetil(struct Projetil* Bomba) {

	// Fun��o an�loga � anima personagem, por�m recebe a estrutura Projetil

	int x_folha;
	Bomba->ac[Bomba->estado].frame_atual++;
	
	if (Bomba->ac[Bomba->estado].frame_atual >= Bomba->ac[Bomba->estado].num_frames) {
			Bomba->ac[Bomba->estado].frame_atual = 0;
			Bomba->ac[Bomba->estado].col_atual++;
	}
	if (Bomba->ac[Bomba->estado].col_atual > Bomba->ac[Bomba->estado].finalX) {
		Bomba->ac[Bomba->estado].col_atual = Bomba->ac[Bomba->estado].inicioX;
		Bomba->ac[Bomba->estado].frame_atual = 0;
		if (Bomba->estado == 1) {
			Bomba->existe = false;
			Bomba->estado = 0;
		}
		else
			Bomba->ac[Bomba->estado].frame_atual++;
	}
	x_folha = Bomba->ac[Bomba->estado].col_atual * Bomba->img.largura_folha;
	al_draw_scaled_bitmap(Bomba->img.png, x_folha, 0,Bomba->img.largura_folha,
		Bomba->img.altura_folha, Bomba->dx, Bomba->dy,
		Bomba->img.largura, Bomba->img.altura,0);
	
}
void atualiza_fundo(struct Fundo* fundo, int LARGURA_TELA, int ALTURA_TELA) {

	/*
		Funciona tanto para o sentido positivo quanto negativo;
		Recebe um ponteiro para a estrutura fundo e a largura e altura da tela onde fundo ser� desenhado;
		Essa fun��o funcionar� somente para fundos que ocupam a tela inteira;
		Quando o fundo se desloca do inicio da tela, outro fundo � desenhado no ponto dx - Largura da tela, de forma a encaixar-se
		Quando o fundo se desloca num valor igual � Largura da tela seu valor dx volta a ser 0;
	*/


	if (-fundo->dx >= LARGURA_TELA)
		fundo->dx = 0;
	if (-fundo->dx + LARGURA_TELA <= 0)
		fundo->dx = 0;
	al_draw_scaled_bitmap(fundo->imagem, 0, 230, 928, 533, -fundo->dx, 0, LARGURA_TELA, ALTURA_TELA, 0);
	if (-fundo->dx > 0) {
		al_draw_scaled_bitmap(fundo->imagem, 0, 230, 928, 533, -fundo->dx - LARGURA_TELA, 0, LARGURA_TELA, ALTURA_TELA, 0);
	}
	if (-fundo->dx + LARGURA_TELA < LARGURA_TELA) {
		al_draw_scaled_bitmap(fundo->imagem, 0, 230, 928, 533, -fundo->dx + LARGURA_TELA, 0, LARGURA_TELA, ALTURA_TELA, 0);
	}
}
void desenha_hitbox(struct Hitbox* caixa){

	//Recebe a estrutura Hitbox e desenha um retangulo correspondente aos seus pontos

	al_draw_rectangle(caixa->x0, caixa->y0, caixa->x1, caixa->y1, al_map_rgb(255, 255, 255), 1);
}
void desenha_bloco(struct ALLEGRO_BITMAP* Bloco[6],int dx0, int dy0,int dx1,int dy1) {

	//Define qual bloco ser� desenhado com base na altura da hitbox

	switch ((int)(dy1 - dy0)){
	case 48:
		al_draw_scaled_bitmap(Bloco[0], 0, 0, 54, 24, dx0, dy0, 108, 48, 0);
		break;
	case 108:
		al_draw_scaled_bitmap(Bloco[1], 0, 0, 54, 54, dx0, dy0, 108, 108, 0);
		break;
	case 20:
		al_draw_scaled_bitmap(Bloco[5], 0, 0, 80, 55, dx0, dy0 - 20, 320, 220, 0);
		break;
	default:
		al_draw_scaled_bitmap(Bloco[0], 0, 0, 54, 24, dx0, dy0, 108, 48, 0);
		break;
	}
	
}
void desenha_grid(int lin, int col,int LARGURA_TELA,int ALTURA_TELA) {
	for (int i = 0; i < lin; i++)
		al_draw_line(0, ALTURA_TELA / lin * i, LARGURA_TELA, ALTURA_TELA / lin * i, al_map_rgb(255, 255, 255), 1);
	for (int i = 0; i < col; i++)
		al_draw_line(LARGURA_TELA / col * i, 0, LARGURA_TELA / col * i, ALTURA_TELA, al_map_rgb(255, 255, 255), 1);
}