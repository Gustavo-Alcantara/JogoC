#include "classes.h"

void inicializa_cara(struct Carinha* Principal) {
	strcpy(Principal->nome, "Marcos");
	Principal->dx = (LARGURA_TELA / 40);
	Principal->dy = (32 * ALTURA_TELA / 40);
	Principal->direita = 0;
	Principal->veloc = 4;
	Principal->block = false;
	Principal->imagem_personagem.png = al_load_bitmap("cara2.png");
	Principal->imagem_personagem.altura_folha = 37;
	Principal->imagem_personagem.largura_folha = 50;
	Principal->imagem_personagem.altura = 70;
	Principal->imagem_personagem.largura = 90;
	Principal->imagem_personagem.num_col = 7;
	Principal->imagem_personagem.num_lin = 11;
	Principal->cx = Principal->dx + Principal->imagem_personagem.largura / 2;
	Principal->cy = Principal->dy + Principal->imagem_personagem.altura / 2;
	Principal->ac[0].inicioX = 0;
	Principal->ac[0].inicioY = 0;
	Principal->ac[0].finalX = 3;
	Principal->ac[0].finalY = 0;
	Principal->ac[0].num_frames = 10;
	Principal->ac[2].inicioX = 1;
	Principal->ac[2].inicioY = 1;
	Principal->ac[2].finalX = 6;
	Principal->ac[2].finalY = 1;
	Principal->ac[2].num_frames = 7;
	Principal->ac[8].inicioX = 1;
	Principal->ac[8].inicioY = 6;
	Principal->ac[8].finalX = 5;
	Principal->ac[8].finalY = 6;
	Principal->ac[8].num_frames = 5;
	Principal->ac[8].frame_atual = 0;
	Principal->ac[9].inicioX = 3;
	Principal->ac[9].inicioY = 3;
	Principal->ac[9].finalX = 0;
	Principal->ac[9].finalY = 4;
	Principal->ac[9].num_frames = 5;
	Principal->ac[9].frame_atual = 0;
	Principal->ac[10].inicioX = 0;
	Principal->ac[10].inicioY = 7;
	Principal->ac[10].finalX = 2;
	Principal->ac[10].finalY = 7;
	Principal->ac[10].num_frames = 5;
	Principal->ac[10].frame_atual = 0;
	Principal->ac[11].inicioX = 3;
	Principal->ac[11].inicioY = 7;
	Principal->ac[11].finalX = 2;
	Principal->ac[11].finalY = 8;
	Principal->ac[11].num_frames = 5;
	Principal->ac[11].frame_atual = 0;

}
void inicia_goblin(struct Carinha* Goblin, int dx,int dy) {
	strcpy(Goblin->nome ,"Piolho");
	Goblin->dx = dx;
	Goblin->dy = dy;
	Goblin->direita = ALLEGRO_FLIP_HORIZONTAL;
	Goblin->veloc = 3;
	Goblin->block = false;
	Goblin->imagem_personagem.png = al_load_bitmap("Goblin.png");
	Goblin->imagem_personagem.altura_folha = 150;
	Goblin->imagem_personagem.largura_folha = 150;
	Goblin->imagem_personagem.altura = 175;
	Goblin->imagem_personagem.largura = 175;
	Goblin->imagem_personagem.num_col = 32;
	Goblin->imagem_personagem.num_lin = 1;
	Goblin->cx = Goblin->dx + Goblin->imagem_personagem.largura / 2;
	Goblin->cy = Goblin->dy + Goblin->imagem_personagem.altura / 2;
	Goblin->ac[0].inicioX = 0;
	Goblin->ac[0].inicioY = 0;
	Goblin->ac[0].finalX = 3;
	Goblin->ac[0].finalY = 0;
	Goblin->ac[0].num_frames = 10;
	Goblin->ac[1].inicioX = 4;
	Goblin->ac[1].inicioY = 0;
	Goblin->ac[1].finalX = 15;
	Goblin->ac[1].finalY = 0;
	Goblin->ac[1].num_frames = 6;
	Goblin->ac[2].inicioX = 16;
	Goblin->ac[2].inicioY = 0;
	Goblin->ac[2].finalX = 23;
	Goblin->ac[2].finalY = 0;
	Goblin->ac[2].num_frames = 5;
	Goblin->ac[3].inicioX = 24;
	Goblin->ac[3].inicioY = 0;
	Goblin->ac[3].finalX = 31;
	Goblin->ac[3].finalY = 0;
	Goblin->ac[3].num_frames = 5;
}
void carrega_projetil_goblin(struct Projetil*Bomba,struct Carinha*Goblin) {
	Bomba->dx = Goblin->cx;
	Bomba->dy = Goblin->cy;
	Bomba->img.png = al_load_bitmap("Bomb_sprite.png");
	Bomba->img.altura_folha = 100;
	Bomba->img.largura_folha = 100;
	Bomba->img.altura = 130;
	Bomba->img.largura = 130;
	Bomba->img.num_col=19;
	Bomba->img.num_lin=1;
	Bomba->col_atual=0;
	Bomba->lin_atual=0;
	Bomba->frame_atual=0;
	Bomba->num_frames=5;
	Bomba->existe = false;
	Bomba->veloc = 6;

}