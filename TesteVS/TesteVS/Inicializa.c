#include "classes.h"

void inicializa_cara(struct Carinha* Principal, struct ALLEGRO_BITMAP* img, int dx, int dy) {
	strcpy(Principal->nome, "Marcos");
	Principal->morto = false;
	Principal->dx = dx;
	Principal->dy = dy;
	Principal->dano = 1;
	Principal->direita = 0;
	Principal->veloc = 8;
	Principal->altura_pulo = 12;
	Principal->block = false;
	Principal->apanha = true;
	Principal->vida_total = 5;
	Principal->vida_atual = Principal->vida_total;
	Principal->pula = false;
	Principal->conta_ataque = 0;
	Principal->conta_pulo = 0;
	Principal->espera = 0;
	Principal->movendo = false;
	Principal->queda = 0;
	Principal->imagem_personagem.png = img;
	Principal->imagem_personagem.altura_folha = 37;
	Principal->imagem_personagem.largura_folha = 50;
	Principal->imagem_personagem.altura = 140;
	Principal->imagem_personagem.largura = 180;
	Principal->imagem_personagem.num_col = 7;
	Principal->imagem_personagem.num_lin = 11;
	Principal->cx = Principal->dx + Principal->imagem_personagem.largura / 2;
	Principal->cy = Principal->dy + Principal->imagem_personagem.altura / 2;
	Principal->caixa.x0 = Principal->cx - 50;
	Principal->caixa.x1 = Principal->cx + 40;
	Principal->caixa.y0 = Principal->cy - 60;
	Principal->caixa.y1 = Principal->cy + 70;
	Principal->ac[0].inicioX = 0;
	Principal->ac[0].inicioY = 0;
	Principal->ac[0].finalX = 3;
	Principal->ac[0].finalY = 0;
	Principal->ac[0].num_frames = 10;
	Principal->ac[1].inicioX = 4;
	Principal->ac[1].inicioY = 0;
	Principal->ac[1].finalX = 0;
	Principal->ac[1].finalY = 1;
	Principal->ac[1].num_frames = 10;
	Principal->ac[2].inicioX = 1;
	Principal->ac[2].inicioY = 1;
	Principal->ac[2].finalX = 6;
	Principal->ac[2].finalY = 1;
	Principal->ac[2].num_frames = 7;
	Principal->ac[3].inicioX = 2;
	Principal->ac[3].inicioY = 2;
	Principal->ac[3].finalX = 3;
	Principal->ac[3].finalY = 2;
	Principal->ac[3].num_frames = 7;
	Principal->ac[4].inicioX = 4;
	Principal->ac[4].inicioY = 2;
	Principal->ac[4].finalX = 0;
	Principal->ac[4].finalY = 3;
	Principal->ac[4].num_frames = 5;
	Principal->ac[5].inicioX = 1;
	Principal->ac[5].inicioY = 3;
	Principal->ac[5].finalX = 2;
	Principal->ac[5].finalY = 3;
	Principal->ac[5].num_frames = 7;
	Principal->ac[8].inicioX = 1;
	Principal->ac[8].inicioY = 6;
	Principal->ac[8].finalX = 5;
	Principal->ac[8].finalY = 6;
	Principal->ac[8].num_frames = 3;
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
	Principal->ac[10].num_frames = 4;
	Principal->ac[10].frame_atual = 0;
	Principal->ac[11].inicioX = 3;
	Principal->ac[11].inicioY = 7;
	Principal->ac[11].finalX = 2;
	Principal->ac[11].finalY = 8;
	Principal->ac[11].num_frames = 4;
	Principal->ac[11].frame_atual = 0;
	Principal->ac[12].inicioX = 3;
	Principal->ac[12].inicioY = 8;
	Principal->ac[12].finalX = 5;
	Principal->ac[12].finalY = 8;
	Principal->ac[12].num_frames = 9;
	Principal->ac[12].frame_atual = 0;
	Principal->caixa.x0 = Principal->cx + 25;
	Principal->caixa.x1 = Principal->cx - 25;
	Principal->caixa.y0 = Principal->cy- 30;
	Principal->caixa.y1 = Principal->cy + 40;

}
void inicia_goblin(struct Inimigo* Goblin, struct ALLEGRO_BITMAP* img, int dx, int dy) {
	Goblin->tipo = GOBLIN;
	Goblin->dano = 1;
	Goblin->vida_total = 3;
	Goblin->vida_atual = Goblin->vida_total;
	Goblin->dx = dx;
	Goblin->dy = dy;
	Goblin->direita = ALLEGRO_FLIP_HORIZONTAL;
	Goblin->veloc = 6;
	Goblin->block = false;
	Goblin->morto = false;
	Goblin->queda = 0;
	Goblin->espera = 180;
	Goblin->imagem_personagem.png = img;
	Goblin->imagem_personagem.altura_folha = 150;
	Goblin->imagem_personagem.largura_folha = 150;
	Goblin->imagem_personagem.altura = 350;
	Goblin->imagem_personagem.largura = 350;
	Goblin->imagem_personagem.num_col = 50;
	Goblin->imagem_personagem.num_lin = 1;
	Goblin->cx = Goblin->dx + Goblin->imagem_personagem.largura / 2;
	Goblin->cy = Goblin->dy + Goblin->imagem_personagem.altura / 2;
	Goblin->caixa.x0 = Goblin->cx + 30;
	Goblin->caixa.x1 = Goblin->cx - 30;
	Goblin->caixa.y0 = Goblin->cy - 30;
	Goblin->caixa.y1 = Goblin->cy + 40;
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
	Goblin->ac[4].inicioX = 32;
	Goblin->ac[4].inicioY = 0;
	Goblin->ac[4].finalX = 35;
	Goblin->ac[4].finalY = 0;
	Goblin->ac[4].num_frames = 5;
	Goblin->ac[5].inicioX = 36;
	Goblin->ac[5].inicioY = 0;
	Goblin->ac[5].finalX = 40;
	Goblin->ac[5].finalY = 0;
	Goblin->ac[5].num_frames = 10;
	Goblin->ac[6].inicioX = 40;
	Goblin->ac[6].inicioY = 0;
	Goblin->ac[6].finalX = 48;
	Goblin->ac[6].finalY = 0;
	Goblin->ac[6].num_frames = 5;
}
void inicia_armadura(struct Inimigo* Armadura, struct ALLEGRO_BITMAP* img, int dx, int dy) {
	Armadura->tipo = ARMADURA;
	Armadura->dano = 1;
	Armadura->vida_total = 7;
	Armadura->vida_atual = Armadura->vida_total;
	Armadura->dx = dx;
	Armadura->dy = dy;
	Armadura->queda = 0;
	Armadura->direita = ALLEGRO_FLIP_HORIZONTAL;
	Armadura->veloc = 4;
	Armadura->espera = 60;
	Armadura->block = false;
	Armadura->morto = false;
	Armadura->imagem_personagem.png = img;
	Armadura->imagem_personagem.altura_folha = 80;
	Armadura->imagem_personagem.largura_folha = 90;
	Armadura->imagem_personagem.altura = 160;
	Armadura->imagem_personagem.largura = 180;
	Armadura->imagem_personagem.num_col = 5;
	Armadura->imagem_personagem.num_lin = 4;
	Armadura->cx = Armadura->dx + Armadura->imagem_personagem.largura / 2;
	Armadura->cy = Armadura->dy + Armadura->imagem_personagem.altura / 2;
	Armadura->caixa.x0 = Armadura->cx + 30;
	Armadura->caixa.x1 = Armadura->cx - 30;
	Armadura->caixa.y0 = Armadura->cy - 30;
	Armadura->caixa.y1 = Armadura->cy + 50;
	Armadura->ac[0].inicioX = 0;
	Armadura->ac[0].inicioY = 0;
	Armadura->ac[0].finalX = 0;
	Armadura->ac[0].finalY = 0;
	Armadura->ac[0].num_frames = 10;
	Armadura->ac[1].inicioX = 3;
	Armadura->ac[1].inicioY = 3;
	Armadura->ac[1].finalX = 4;
	Armadura->ac[1].finalY = 3;
	Armadura->ac[1].num_frames = 15;
	Armadura->ac[2].inicioX = 1;
	Armadura->ac[2].inicioY = 0;
	Armadura->ac[2].finalX = 4;
	Armadura->ac[2].finalY = 0;
	Armadura->ac[2].num_frames = 15;
	Armadura->ac[3].inicioX = 0;
	Armadura->ac[3].inicioY = 1;
	Armadura->ac[3].finalX = 0;
	Armadura->ac[3].finalY = 2;
	Armadura->ac[3].num_frames = 15;
	Armadura->ac[4].inicioX = 1;
	Armadura->ac[4].inicioY = 2;
	Armadura->ac[4].finalX = 2;
	Armadura->ac[4].finalY = 2;
	Armadura->ac[4].num_frames = 15;
	Armadura->ac[5].inicioX = 1;
	Armadura->ac[5].inicioY = 2;
	Armadura->ac[5].finalX = 0;
	Armadura->ac[5].finalY = 3;
	Armadura->ac[5].num_frames = 10;
	Armadura->ac[6].inicioX = 1;
	Armadura->ac[6].inicioY = 3;
	Armadura->ac[6].finalX = 2;
	Armadura->ac[6].finalY = 3;
	Armadura->ac[6].num_frames = 15;
}
void inicia_olho(struct Inimigo* Olho, struct ALLEGRO_BITMAP* img, int dx, int dy) {
	Olho->tipo = OLHO;
	Olho->dano = 1;
	Olho->vida_total = 2;
	Olho->vida_atual = Olho->vida_total;
	Olho->dx = dx;
	Olho->dy = dy;
	Olho->queda = 0;
	Olho->direita = ALLEGRO_FLIP_HORIZONTAL;
	Olho->veloc = 4;
	Olho->espera = 60;
	Olho->block = false;
	Olho->morto = false;
	Olho->imagem_personagem.png = img;
	Olho->imagem_personagem.altura_folha = 150;
	Olho->imagem_personagem.largura_folha = 150;
	Olho->imagem_personagem.altura = 300;
	Olho->imagem_personagem.largura = 300;
	Olho->imagem_personagem.num_col = 50;
	Olho->imagem_personagem.num_lin = 1;
	Olho->cx = Olho->dx + Olho->imagem_personagem.largura / 2;
	Olho->cy = Olho->dy + Olho->imagem_personagem.altura / 2;
	Olho->caixa.x0 = Olho->cx + 20;
	Olho->caixa.x1 = Olho->cx - 20;
	Olho->caixa.y0 = Olho->cy - 10;
	Olho->caixa.y1 = Olho->cy + 15;
	Olho->ac[6].inicioX = 0;
	Olho->ac[6].inicioY = 0;
	Olho->ac[6].finalX = 7;
	Olho->ac[6].finalY = 0;
	Olho->ac[6].num_frames = 10;
	Olho->ac[1].inicioX = 8;
	Olho->ac[1].inicioY = 0;
	Olho->ac[1].finalX = 15;
	Olho->ac[1].finalY = 0;
	Olho->ac[1].num_frames = 10;
	Olho->ac[4].inicioX = 16;
	Olho->ac[4].inicioY = 0;
	Olho->ac[4].finalX = 19;
	Olho->ac[4].finalY = 0;
	Olho->ac[4].num_frames = 5;
	Olho->ac[5].inicioX = 19;
	Olho->ac[5].inicioY = 0;
	Olho->ac[5].finalX = 22;
	Olho->ac[5].finalY = 0;
	Olho->ac[5].num_frames = 5;
}
void carrega_projetil_goblin(struct Inimigo* Goblin,struct ALLEGRO_BITMAP* img) {
	Goblin->prj.dx = Goblin->cx + 50;
	Goblin->prj.dy = Goblin->cy - 100;
	Goblin->prj.img.png = img;
	Goblin->prj.img.altura_folha = 100;
	Goblin->prj.img.largura_folha = 100;
	Goblin->prj.img.altura = 260;
	Goblin->prj.img.largura = 260;
	Goblin->prj.img.num_col=19;
	Goblin->prj.img.num_lin=1;
	Goblin->prj.veloc = 13;
	Goblin->prj.dano = 1;
	Goblin->prj.ac[0].inicioX = 0;
	Goblin->prj.ac[0].inicioY = 0;
	Goblin->prj.ac[0].finalX = 8;
	Goblin->prj.ac[0].finalY = 0;
	Goblin->prj.ac[0].num_frames = 5;
	Goblin->prj.ac[0].col_atual = 0;
	Goblin->prj.ac[0].frame_atual = 0;
	Goblin->prj.ac[1].inicioX = 9;
	Goblin->prj.ac[1].inicioY = 0;
	Goblin->prj.ac[1].finalX = 18;
	Goblin->prj.ac[1].finalY = 0;
	Goblin->prj.ac[1].num_frames = 5;
	Goblin->prj.ac[1].col_atual = 8;
	Goblin->prj.ac[1].frame_atual = 0;
	Goblin->prj.estado = 0;
}