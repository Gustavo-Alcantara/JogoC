#include "classes.h"

void carrega_mapa(char mapa[20][20], int dx, struct Hitbox Vetor_Chao[10], int LARGURA_TELA, int ALTURA_TELA) {

	// Carrega o mapa de um dos arquivos de texto da pasta mapas e o copia para uma matriz, al�m de carregar as hitboxes do vetor_chao

	char matriz[20][22];
	int i = 0;
	int n = 0;
	int e = 0;
	int aleatorio;
	srand(time(NULL));
	ALLEGRO_FILE* arquivo = NULL;
	aleatorio = rand() % 3;
	
	switch (aleatorio) {
	case 0:
		arquivo = al_fopen("Mapas/mapa.txt", "r");
		break;
	case 1:
		arquivo = al_fopen("Mapas/mapa1.txt", "r");
		break;
	case 2:
		arquivo = al_fopen("Mapas/mapa2.txt", "r");
		break;
	}
	if (arquivo){
		while (!al_feof(arquivo)) {
			al_fgets(arquivo, (char*)&matriz[i], 22);
			i++;
		}
	al_fclose(arquivo);
	}
	for (i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			mapa[i][j] = matriz[i][j];
			if (n <= 9) {
				switch (mapa[i][j]) {
				case '1':
					Vetor_Chao[n].x0 = LARGURA_TELA / 20 * j + dx + LARGURA_TELA;
					Vetor_Chao[n].x1 = LARGURA_TELA / 20 * j + 108 + dx + LARGURA_TELA;
					Vetor_Chao[n].y0 = ALTURA_TELA / 20 * i;
					Vetor_Chao[n].y1 = ALTURA_TELA / 20 * i + 48;
					n++;
					break;
				case '2':
					Vetor_Chao[n].x0 = LARGURA_TELA / 20 * j + dx + LARGURA_TELA;
					Vetor_Chao[n].x1 = LARGURA_TELA / 20 * j + 108 + dx + LARGURA_TELA;
					Vetor_Chao[n].y0 = ALTURA_TELA / 20 * i;
					Vetor_Chao[n].y1 = ALTURA_TELA / 20 * i + 108;
					n++;
					break;
				case '5':
					Vetor_Chao[n].x0 = LARGURA_TELA / 20 * j + dx + LARGURA_TELA;
					Vetor_Chao[n].x1 = LARGURA_TELA / 20 * j + 320 + dx + LARGURA_TELA;
					Vetor_Chao[n].y0 = ALTURA_TELA / 20 * i;
					Vetor_Chao[n].y1 = ALTURA_TELA / 20 * i + 20;
					n++;
					break;

				}
			}
		}
	}
}