#include "classes.h"

void carrega_mapa(char mapa[20][20],int dx,struct Hitbox Vetor_Chao[10],int LARGURA_TELA, int ALTURA_TELA) {
	char matriz[20][22];
	int i = 0;
	int n = 0;
	ALLEGRO_FILE* arquivo;
	arquivo = al_fopen("Mapas/mapa.txt", "r");
	while (!al_feof(arquivo)) {
		al_fgets(arquivo, (char*)&matriz[i], 22);
		i++;
	}
	for (i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			mapa[i][j] = matriz[i][j];
			if (mapa[i][j] == '1' && n <= 9) {
				Vetor_Chao[n].x0 = LARGURA_TELA / 20 * j + dx + LARGURA_TELA;
				Vetor_Chao[n].x1 = LARGURA_TELA / 20 * j + LARGURA_TELA/20 + dx + LARGURA_TELA;
				Vetor_Chao[n].y0 = ALTURA_TELA / 20 * i;
				Vetor_Chao[n].y1 = ALTURA_TELA / 20 * i + ALTURA_TELA / 20;
				n++;
			}

		}
	}

}