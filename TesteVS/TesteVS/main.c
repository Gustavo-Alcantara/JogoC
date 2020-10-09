#include "classes.h"
#include "macros.h"
//#define DESENHA
//#define GRID

ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_BITMAP* folha = NULL;
ALLEGRO_FONT* fonte = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_KEYBOARD_STATE* teclado = NULL;
ALLEGRO_AUDIO_STREAM* musica = NULL;
ALLEGRO_BITMAP* coracoes = NULL;
ALLEGRO_BITMAP* Bloco[6];
ALLEGRO_BITMAP* img_fundo[11];
ALLEGRO_BITMAP* img_inimigos[NUM_INIMIGOS];

int LARGURA_TELA = 640;
int ALTURA_TELA = 480;
char mapa[20][20];
int aleatorio;
int e = 0;

bool inicializar();
void desenha_grid(int lin, int col);

int main(void) {
	int x = 928;
	srand(time(NULL));
	bool inicio = inicializar();
	struct Carinha Principal;
	struct Inimigo Ativos[5];
	struct Projetil Bomba[2];
	struct Hitbox Vetor_Chao[10];
	struct Fundo fundo[11];
	

	fundo[0].imagem = img_fundo[0];
	fundo[1].imagem = img_fundo[1];
	fundo[2].imagem = img_fundo[2];
	fundo[3].imagem = img_fundo[3];
	fundo[4].imagem = img_fundo[4];
	fundo[5].imagem = img_fundo[5];
	fundo[6].imagem = img_fundo[6];
	fundo[7].imagem = img_fundo[7];
	fundo[8].imagem = img_fundo[8];
	fundo[9].imagem = img_fundo[9];
	fundo[10].imagem = img_fundo[10];


	for (int k = 0; k < 5; k++)
		Ativos[k].morto = true;
	for (int i = 0; i < 11; i++) {
		fundo[i].dx = 0;
		fundo[i].dy = 0;
	}
	inicializa_cara(&Principal, folha,(LARGURA_TELA / 2)-150, (10 * ALTURA_TELA / 40),ALTURA_TELA,LARGURA_TELA);
	carrega_mapa(mapa,Principal.dx,Vetor_Chao,LARGURA_TELA,ALTURA_TELA);

	aleatorio = rand() % NUM_INIMIGOS + 1;
	inicia_inimigo(&Ativos[0], img_inimigos, Principal.dx + LARGURA_TELA + 50 * 1, ALTURA_TELA / 20, LARGURA_TELA, ALTURA_TELA, aleatorio);
	reseta_acoes_inimigo(&Ativos[0], 10, 30);

	aleatorio = rand() % NUM_INIMIGOS + 1;
	inicia_inimigo(&Ativos[1], img_inimigos, Principal.dx + LARGURA_TELA + 50 * 2, ALTURA_TELA / 20, LARGURA_TELA, ALTURA_TELA, aleatorio);
	reseta_acoes_inimigo(&Ativos[1], 10, 30);

	aleatorio = rand() % NUM_INIMIGOS + 1;
	inicia_inimigo(&Ativos[2], img_inimigos, Principal.dx + LARGURA_TELA + 50 * 3, ALTURA_TELA / 20, LARGURA_TELA, ALTURA_TELA, aleatorio);
	reseta_acoes_inimigo(&Ativos[2], 10, 30);

	carrega_projetil_goblin(&Bomba[0], &Ativos[0]);
	reseta_acoes(&Principal, 20, 30,Principal.direita);
	

	Vetor_Chao[9].x0 = -LARGURA_TELA;
	Vetor_Chao[9].y0 = (38 * ALTURA_TELA / 40) ;
	Vetor_Chao[9].x1 = 3*LARGURA_TELA;
	Vetor_Chao[9].y1 = ALTURA_TELA;

	bool sair = false;
	int desloc = 0;

	if (!inicio)
		return -1;


	Principal.acao_atual = RESPIRA_PRINCIPAL;
	
	while (!sair) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			strcpy(Principal.nome, "Marcos");
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN && Principal.acao_atual != APANHA_PRINCIPAL) {
				if (Principal.conta_ataque > 2)
					Principal.conta_ataque = 0;
				le_teclado_baixo(&Principal, Vetor_Chao, evento.keyboard.keycode);
				if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					sair = true;
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP)
				le_teclado_alto(&Principal, evento.keyboard.keycode);

			else if (evento.type == ALLEGRO_EVENT_TIMER){
				desloc = 0;
				
				if (mortos(Ativos)) {
					carrega_mapa(mapa, Principal.dx, Vetor_Chao, LARGURA_TELA, ALTURA_TELA);
					e = 0;
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 20; j++) {
							aleatorio = rand() % NUM_INIMIGOS + 1;
							if (mapa[i][j] == 'E') {
								inicia_inimigo(&Ativos[e], img_inimigos, LARGURA_TELA / 20 * j + Principal.dx + LARGURA_TELA, ALTURA_TELA / 20 * i, LARGURA_TELA, ALTURA_TELA, aleatorio);
								reseta_acoes_inimigo(&Ativos[e], 10, 30);
								Ativos[e].acao_atual = 0;
								e++;
							}

						}
					}
					Vetor_Chao[9].x0 = -LARGURA_TELA;
					Vetor_Chao[9].y0 = (38 * ALTURA_TELA / 40);
					Vetor_Chao[9].x1 = 3 * LARGURA_TELA;
					Vetor_Chao[9].y1 = ALTURA_TELA;
				}

				personagem_principal(&Principal, Vetor_Chao,Ativos,desloc);
				for (int i = 0; i < 5; i++)
					Ativos[i].dx -= Principal.dx - ((LARGURA_TELA / 2) - 150);
				desloc = Principal.dx - ((LARGURA_TELA / 2) - 150);
				Principal.dx = (LARGURA_TELA / 2) - 150;
				
				for (int i = 0; i < 5; i++) {
					comportamento(&Ativos[i], &Principal, &Bomba[0]);
					if (!Ativos[i].nochao && Ativos[i].acao_atual != VOA) {
						Ativos[i].dy += Ativos[i].queda;
						Ativos[i].queda += 0.2;
					}
					else
						Ativos[i].queda = 0;
					if (Ativos[i].dy > ALTURA_TELA)
						Ativos[i].morto = true;
				}

				//fisica_bomba(&Bomba[0], &Ativos[0], &Principal, &Vetor_Chao);

				for (int i = 10; i >= 0; i--) {
					if (i < 9 && i>0) {
						Vetor_Chao[i].x0 -= desloc;
						Vetor_Chao[i].x1 -= desloc;
					}
					if (i > 0) {
						fundo[i].dx += desloc/i;
						atualiza_fundo(&fundo[i], LARGURA_TELA, ALTURA_TELA);
					}
				}

				for (int j = 0; j < Principal.vida_atual; j++)
					al_draw_scaled_bitmap(coracoes, 0, 0, 256, 256, j * 25 + 10, 10, 25, 25, 0);

				al_draw_text(fonte, al_map_rgb(255,255, 255), 10, 40, ALLEGRO_ALIGN_LEFT, "Marcos");

				for (int i = 0; i < 10; i++)
					desenha_bloco(Bloco,Vetor_Chao[i].x0, Vetor_Chao[i].y0, Vetor_Chao[i].x1, Vetor_Chao[i].y1);

				for (int i = 0; i < 5; i++)
					atualiza_inimigos(&Ativos[i], 5);

				anima_personagem(&Principal, Principal.acao_atual);
				
				/*if(Bomba[0].existe)
					anima_projetil(&Bomba[0]);*/

				#ifdef DESENHA //Hitboxes
				desenha_hitbox(&Principal.caixa);
				for (int i = 0; i < 10; i++)
					desenha_hitbox(&Vetor_Chao[i]);

				for (int i = 0; i < 5; i++) {
					if(!Ativos[i].morto)
						desenha_hitbox(&Ativos[i].caixa);
				}
				#endif // Desenha Hitboxes
				#ifdef GRID
				desenha_grid(20,20);
				#endif

				al_flip_display();
			}
			if (!colisao_chao(&Principal.caixa, Vetor_Chao) && !Principal.morto)
				Principal.nochao = false;
			else {
				Principal.nochao = true;
				Principal.queda = 0;
			}

			for (int i = 0; i < 5; i++) {
				if (!colisao_chao(&Ativos[i].caixa, Vetor_Chao) && !Ativos[i].morto)
					Ativos[i].nochao = false;
				else {
					Ativos[i].nochao = true;
					Ativos[i].queda = 0;
				}
				if (Ativos[i].dy > ALTURA_TELA)
					Ativos[i].morto = true;
			}
		}
	}

	al_destroy_event_queue(fila_eventos);
	al_destroy_display(janela);
	al_destroy_bitmap(folha);
	for (int i = 0; i <= 5; i++)
		al_destroy_bitmap(Bloco[i]);
	for (int i = 0; i < NUM_INIMIGOS; i++)
		al_destroy_bitmap(img_inimigos[i]);
	for (int i = 0; i < 11; i++)
		al_destroy_bitmap(img_fundo[i]);
	al_destroy_font(fonte);
	al_destroy_bitmap(coracoes);
	al_destroy_timer(timer);

	return 0;
}
bool inicializar() {
	if (!al_init()) {
		return false;
	}
	if (!al_init_image_addon()) {
		return false;
	}
	if(!al_init_primitives_addon())
		return false;
	if(!al_init_font_addon())
		return false;
	if (!al_install_keyboard()) {
		return false;
	}
	if (!al_install_audio()) {
		return false;
	}
	if (!al_init_acodec_addon()) {
		return false;
	}
	if (!al_reserve_samples(5)) {
		return false;
	}
	if (!al_init_ttf_addon())
		return false;

	ALLEGRO_MONITOR_INFO inf;
	al_get_monitor_info(0, &inf);

	LARGURA_TELA = inf.x2 - inf.x1;
	ALTURA_TELA = inf.y2 - inf.y1;

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);

	if (!janela)
		return false;

	al_set_window_title(janela, "Aventura Lo-Fi");

	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		al_destroy_display(janela);
		return false;
	}
	folha = al_load_bitmap("Principal/cara2.png");

	if (!folha) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		return false;
	}

	Bloco[0] = al_load_bitmap("Blocos/Bloco.png");
	Bloco[1] = al_load_bitmap("Blocos/Bloco_1.png");
	Bloco[2] = al_load_bitmap("Blocos/Bloco_2.png");
	Bloco[3] = al_load_bitmap("Blocos/Bloco_3.png");
	Bloco[4] = al_load_bitmap("Blocos/Bloco_4.png");
	Bloco[5] = al_load_bitmap("Blocos/Bloco_5.png");

	if (!Bloco) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		al_destroy_bitmap(folha);
		return false;
	}

	img_inimigos[0] = al_load_bitmap("Inimigos/Goblin.png");
	img_inimigos[1] = al_load_bitmap("Inimigos/Armadura.png");
	img_inimigos[2] = al_load_bitmap("Inimigos/Olho.png");
	img_inimigos[3] = al_load_bitmap("Inimigos/MagoCaveira.png");

	if (!img_inimigos) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		al_destroy_bitmap(folha);
		for(int i = 0; i <= 5; i++)
			al_destroy_bitmap(Bloco[i]);
		return false;
	}

	img_fundo[0] = al_load_bitmap("Fundo/Layer_0000_9.png");
	img_fundo[1] = al_load_bitmap("Fundo/Layer_0001_8.png");
	img_fundo[2] = al_load_bitmap("Fundo/Layer_0002_7.png");
	img_fundo[3] = al_load_bitmap("Fundo/Layer_0003_6.png");
	img_fundo[4] = al_load_bitmap("Fundo/Layer_0004_Lights.png");
	img_fundo[5] = al_load_bitmap("Fundo/Layer_0005_5.png");
	img_fundo[6] = al_load_bitmap("Fundo/Layer_0006_4.png");
	img_fundo[7] = al_load_bitmap("Fundo/Layer_0007_Lights.png");
	img_fundo[8] = al_load_bitmap("Fundo/Layer_0008_3.png");
	img_fundo[9] = al_load_bitmap("Fundo/Layer_0009_2.png");
	img_fundo[10] = al_load_bitmap("Fundo/Layer_0010_1.png");

	if (!img_fundo) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		al_destroy_bitmap(folha);
		for (int i = 0; i <= 5; i++)
			al_destroy_bitmap(Bloco[i]);
		for (int i = 0; i < NUM_INIMIGOS; i++)
			al_destroy_bitmap(img_inimigos[i]);
		return false;
	}

	fonte = al_load_font("Fontes/Toothy.ttf", 24, 0);

	if (!fonte) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		al_destroy_bitmap(folha);
		for (int i = 0; i <= 5; i++)
			al_destroy_bitmap(Bloco[i]);
		for (int i = 0; i < NUM_INIMIGOS; i++)
			al_destroy_bitmap(img_inimigos[i]);
		for(int i= 0; i <11;i++)
			al_destroy_bitmap(img_fundo[i]);
		return false;
	}

	coracoes = al_load_bitmap("Principal/vida.png");
	if (!coracoes) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		al_destroy_bitmap(folha);
		for (int i = 0; i <= 5; i++)
			al_destroy_bitmap(Bloco[i]);
		for (int i = 0; i < NUM_INIMIGOS; i++)
			al_destroy_bitmap(img_inimigos[i]);
		for (int i = 0; i < 11; i++)
			al_destroy_bitmap(img_fundo[i]);
		al_destroy_font(fonte);
		return false;
	}

	musica = al_load_audio_stream("soundtrack.ogg", 4, 1024);
	if (!musica) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		al_destroy_bitmap(folha);
		for (int i = 0; i <= 5; i++)
			al_destroy_bitmap(Bloco[i]);
		for (int i = 0; i < NUM_INIMIGOS; i++)
			al_destroy_bitmap(img_inimigos[i]);
		for (int i = 0; i < 11; i++)
			al_destroy_bitmap(img_fundo[i]);
		al_destroy_font(fonte);
		al_destroy_bitmap(coracoes);
		return false;
	}
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		al_destroy_bitmap(folha);
		for (int i = 0; i <= 5; i++)
			al_destroy_bitmap(Bloco[i]);
		for (int i = 0; i < NUM_INIMIGOS; i++)
			al_destroy_bitmap(img_inimigos[i]);
		for (int i = 0; i < 11; i++)
			al_destroy_bitmap(img_fundo[i]);
		al_destroy_font(fonte);
		al_destroy_bitmap(coracoes);
		al_destroy_timer(timer);
		return false;
	}
	
	//liga o stream no mixer
	al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
	//define que o stream vai tocar no modo repeat
	al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);


	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	al_start_timer(timer);

	return true;
}
void desenha_grid(int lin, int col) {
	for (int i = 0; i < lin; i++)
		al_draw_line(0, ALTURA_TELA / lin * i, LARGURA_TELA, ALTURA_TELA / lin * i, al_map_rgb(255, 255, 255), 1);
	for (int i = 0; i < lin; i++)
		al_draw_line(LARGURA_TELA/ col * i,0, LARGURA_TELA / col * i,ALTURA_TELA, al_map_rgb(255, 255, 255), 1);
}