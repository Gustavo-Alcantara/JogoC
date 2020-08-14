#include "classes.h"

bool inicializar();


int main(void) {
	bool inicio = inicializar();
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


	while (!sair) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			if (evento.type == 11) {
				switch (evento.keyboard.keycode){
				case ALLEGRO_KEY_D:
					anima_correndo(&evento, false, ALLEGRO_KEY_D);
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_A:
					anima_correndo(&evento, true, ALLEGRO_KEY_A);
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_W:
					anima_pulando(&evento);
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_S:
					//anima_abaixado(&evento);
					break;
				case ALLEGRO_KEY_J:
					if (conta_ataque == 1) {
						anima_ataque(&evento,conta_ataque);
						conta_ataque = 0;
					}
					else { 
						anima_ataque(&evento, conta_ataque);
						conta_ataque++;
					}
					break;
				default:
					anima_respirando(&evento);
					conta_ataque = 0;
					break;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				sair = true;
			else
				anima_respirando(&evento);
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