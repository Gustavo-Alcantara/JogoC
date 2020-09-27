#include "classes.h"
#include "macros.h"
//#define DESENHA
//#define GRID

ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_BITMAP* layers[11];
ALLEGRO_BITMAP* folha = NULL;
ALLEGRO_FONT* fonte = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_KEYBOARD_STATE* teclado = NULL;
ALLEGRO_AUDIO_STREAM* musica = NULL;
ALLEGRO_BITMAP* coracoes = NULL;


bool inicializar();
void desenha_grid(int lin, int col);

int main(void) {
	bool inicio = inicializar();
	struct Carinha Principal;
	struct Inimigo Ativos[5];
	struct Projetil Bomba[2];
	struct Hitbox Vetor_Chao[10];

	for (int k = 0; k < 5; k++)
		Ativos[k].morto = true;

	inicia_goblin(&Ativos[0],7 * LARGURA_TELA / 10,(28 * ALTURA_TELA / 40));
	inicia_goblin(&Ativos[1],5 * LARGURA_TELA / 10,(28 * ALTURA_TELA / 40));
	inicializa_cara(&Principal);
	carrega_projetil_goblin(&Bomba[0], &Ativos[0]);
	carrega_projetil_goblin(&Bomba[1], &Ativos[1]);

	reseta_acoes(&Principal, 20, 30,Principal.direita);
	reseta_acoes_inimigo(&Ativos[0], 10, 30,Ativos[0].direita);
	reseta_acoes_inimigo(&Ativos[1], 10, 30,Ativos[1].direita);

	Vetor_Chao[0].x0 = 0;
	Vetor_Chao[0].y0 = (32 * ALTURA_TELA / 40) + Principal.imagem_personagem.altura;
	Vetor_Chao[0].x1 = LARGURA_TELA;
	Vetor_Chao[0].y1 = ALTURA_TELA;

	bool sair = false;
	int desloc = 0;
	float x1;
	float queda = 0;
	if (!inicio)
		return -1;
	fonte = al_load_font("Toothy.ttf", 24, 0);
	coracoes = al_load_bitmap("vida.png");
	layers[0] = al_load_bitmap("Layer_0000_9.png");
	layers[1] = al_load_bitmap("Layer_0001_8.png");
	layers[2] = al_load_bitmap("Layer_0002_7.png");
	layers[3] = al_load_bitmap("Layer_0003_6.png");
	layers[4] = al_load_bitmap("Layer_0004_Lights.png");
	layers[5] = al_load_bitmap("Layer_0005_5.png");
	layers[6] = al_load_bitmap("Layer_0006_4.png");
	layers[7] = al_load_bitmap("Layer_0007_Lights.png");
	layers[8] = al_load_bitmap("Layer_0008_3.png");
	layers[9] = al_load_bitmap("Layer_0009_2.png");
	layers[10] = al_load_bitmap("Layer_0010_1.png");

	Principal.acao_atual = RESPIRA_PRINCIPAL;
	
	while (!sair) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			strcpy(Principal.nome, "Marcos");
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN && Principal.acao_atual != APANHA_PRINCIPAL) {
				if (Principal.conta_ataque > 2)
					Principal.conta_ataque = 0;
				le_teclado_baixo(&Principal, &Vetor_Chao, evento.keyboard.keycode);
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP)
				le_teclado_alto(&Principal, evento.keyboard.keycode);

			else if (evento.type == ALLEGRO_EVENT_TIMER){
				
				personagem_principal(&Principal, &Vetor_Chao, &Ativos[0]);
				comportamento_goblin(&Ativos[0], &Principal, &Bomba);
				comportamento_goblin(&Ativos[1], &Principal, &Bomba);
				fisica_bomba(&Bomba[0], &Ativos[0], &Principal, &Vetor_Chao);
				fisica_bomba(&Bomba[1], &Ativos[1], &Principal, &Vetor_Chao);
				

				for (int i = 10; i > 0; i--)
					al_draw_scaled_bitmap(layers[i], 0, 230 , LARGURA_TELA, 533, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);

				for (int j = 0; j < Principal.vida_atual; j++)
					al_draw_scaled_bitmap(coracoes, 0, 0, 256, 256, j * 25 + 10, 10, 25, 25, 0);

				al_draw_text(fonte, al_map_rgb(255,255, 255), 10, 40, ALLEGRO_ALIGN_LEFT, "Marcos");

				for (int i = 0; i < 5; i++)
					atualiza_inimigos(&Ativos[i], 5);

				anima_personagem(&Principal, Principal.acao_atual);
				
				if(Bomba[0].existe)
					anima_projetil(&Bomba[0]);
				if (Bomba[1].existe)
					anima_projetil(&Bomba[1]);

				#ifdef DESENHA //Hitboxes
				desenha_hitbox(&Vetor_Chao[0]);
				desenha_hitbox(&Bomba.caixa);
				desenha_hitbox(&Principal.caixa);
				desenha_hitbox(&Ativos[0].caixa);
				al_draw_circle(Principal.cx, Principal.cy, 50,al_map_rgb(255,255,255),1);
				al_draw_circle(Ativos[0].cx, Ativos[0].cy, 50,al_map_rgb(255,255,255),1);
				#endif // Desenha Hitboxes
				#ifdef GRID
				desenha_grid(20,10);
				#endif

				al_flip_display();
			}
			else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				sair = true;
		}
	}
	al_destroy_bitmap(folha);
	al_destroy_timer(timer);
	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);

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
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!janela)
		return false;
	al_set_window_title(janela, "Caminhando e cantando");
	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		al_destroy_display(janela);
		return false;
	}
	folha = al_load_bitmap("cara2.png");
	if (!folha) {
		al_destroy_event_queue(fila_eventos);
		al_destroy_display(janela);
		return false;
	}

	musica = al_load_audio_stream("soundtrack.ogg", 4, 1024);
	//liga o stream no mixer
	al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
	//define que o stream vai tocar no modo repeat
	al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
	fonte = al_create_builtin_font();
	timer = al_create_timer(1.0 / FPS);
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