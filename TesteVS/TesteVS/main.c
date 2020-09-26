#include "classes.h"
#include "macros.h"
//#define DESENHA
#define GRID

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
	struct Inimigo Goblin;
	struct Projetil Bomba;
	struct Hitbox Vetor_Chao[2];


	inicia_goblin(&Goblin,7 * LARGURA_TELA / 10,(28 * ALTURA_TELA / 40));
	inicializa_cara(&Principal);
	carrega_projetil_goblin(&Bomba, &Goblin);

	reseta_acoes(&Principal, 20, 30,Principal.direita);
	reseta_acoes_inimigo(&Goblin, 10, 30,Goblin.direita);

	inicia_goblin(&Goblin, 7 * LARGURA_TELA / 10, (28 * ALTURA_TELA / 40));
	inicializa_cara(&Principal);
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
				le_teclado_baixo(&Principal, &Vetor_Chao[0], evento.keyboard.keycode);
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP)
				le_teclado_alto(&Principal, evento.keyboard.keycode);

			else if (evento.type == ALLEGRO_EVENT_TIMER){
				
				personagem_principal(&Principal, &Vetor_Chao, &Goblin);
				comportamento_goblin(&Goblin, &Principal, &Bomba);

				if (Bomba.existe) {
					int a = 1;
					
					if (Goblin.direita == 0)
						a = -1;

					if (Bomba.estado == 0) {
						Bomba.dx -= a*Bomba.veloc;
						Bomba.dy =Bomba.yi +0.0025*(Bomba.dx - Bomba.xi)*(Bomba.dx - x1);
					}
					Bomba.caixa.x0 = Bomba.dx + Bomba.img.largura/2-10;
					Bomba.caixa.x1 = Bomba.dx + Bomba.img.largura/2+10;
					Bomba.caixa.y0 = Bomba.dy + Bomba.img.altura/2-10;
					Bomba.caixa.y1 = Bomba.dy + Bomba.img.altura/2+10;

					if (colisao(&Bomba.caixa, &Vetor_Chao[0]))
						Bomba.estado = 1;
					else if (colisao(&Bomba.caixa, &Principal.caixa)&& Principal.apanha) {
						if(Bomba.estado == 0)
							Principal.vida_atual -= Bomba.dano;
						Bomba.estado = 1;
						Principal.acao_atual = APANHA_PRINCIPAL;
						Principal.block = true;
					}
					
				}
				else {
					
					 x1 = Principal.cx -50 ;
				}

				for (int i = 10; i > 0; i--)
					al_draw_scaled_bitmap(layers[i], 0, 230 , LARGURA_TELA, 533, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);

				for (int j = 0; j < Principal.vida_atual; j++)
					al_draw_scaled_bitmap(coracoes, 0, 0, 256, 256, j * 25 + 10, 10, 25, 25, 0);

				al_draw_text(fonte, al_map_rgb(255,255, 255), 10, 40, ALLEGRO_ALIGN_LEFT, "Marcos");
				if(Goblin.vida_atual>0 && !Goblin.morto)
					al_draw_line(Goblin.caixa.x0, Goblin.caixa.y0, Goblin.caixa.x0 + (Goblin.caixa.x1 - Goblin.caixa.x0) * Goblin.vida_atual/ Goblin.vida_total, Goblin.caixa.y0,al_map_rgb(255,0,0),2);
				if(!Goblin.morto)
					anima_Inimigo(&Goblin, Goblin.acao_atual);
				anima_personagem(&Principal, Principal.acao_atual);
				if(Bomba.existe)
					anima_projetil(&Bomba);

				#ifdef DESENHA //Hitboxes
				desenha_hitbox(&Vetor_Chao[0]);
				desenha_hitbox(&Bomba.caixa);
				desenha_hitbox(&Principal.caixa);
				desenha_hitbox(&Goblin.caixa);
				al_draw_circle(Principal.cx, Principal.cy, 50,al_map_rgb(255,255,255),1);
				al_draw_circle(Goblin.cx, Goblin.cy, 50,al_map_rgb(255,255,255),1);
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
	//addon que da suporte as extensoes de audio
	if (!al_init_acodec_addon()) {
		return false;
	}

	//cria o mixer (e torna ele o mixer padrao), e adciona 5 samples de audio nele
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