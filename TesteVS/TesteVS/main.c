#include "classes.h"
#include "macros.h"

ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_BITMAP* layers[11];
ALLEGRO_BITMAP* folha = NULL;
ALLEGRO_FONT* fonte = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_KEYBOARD_STATE* teclado = NULL;

bool inicializar();


int main(void) {
	bool inicio = inicializar();

	//Vai virar função de inicialização depois
	struct Carinha Principal;
	inicializa_cara(&Principal);
	
	bool sair = false;
	int conta_ataque = 0;
	if (!inicio)
		return -1;

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

	reseta_acoes(&Principal, 20, 30);

	int acao_atual = 0;
	while (!sair) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (evento.keyboard.keycode) {
				case ALLEGRO_KEY_D:
					reseta_acoes(&Principal,20,CORRENDO_PRINCIPAL);
					Principal.direita = true;
					acao_atual = CORRENDO_PRINCIPAL;
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_A:
					reseta_acoes(&Principal, 20, CORRENDO_PRINCIPAL);
					Principal.direita = false;
					acao_atual = CORRENDO_PRINCIPAL;
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_W:
					//anima_pulando(&evento, invertido);
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_S:
					//anima_abaixado(&evento); 
					break;
				case ALLEGRO_KEY_J:
					if (conta_ataque == 1) {
						//anima_ataque(&evento, conta_ataque, invertido);
						conta_ataque = 0;
					}
					else {
						reseta_acoes(&Principal, 20,	ATAQUE1_PRINCIPAL);
						acao_atual = ATAQUE1_PRINCIPAL;
						conta_ataque++;
					}
					break;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
				if(acao_atual!=ATAQUE1_PRINCIPAL)
					reseta_acoes(&Principal, 20, 30);
				acao_atual = 0;
			}
			else if (evento.type == ALLEGRO_EVENT_TIMER){
				for (int i = 10; i > 0; i--)
					al_draw_scaled_bitmap(layers[i], 0, 230, LARGURA_TELA, 533, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
				anima_personagem(&Principal,acao_atual);
				//acao_atual = 0;
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
	
	if (!al_install_keyboard()) {
		return false;
	}
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!janela)
		return false;
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
	fonte = al_create_builtin_font();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	al_start_timer(timer);

	return true;
}