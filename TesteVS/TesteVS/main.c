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
void anima_respirando(ALLEGRO_EVENT* evento) {
	bool desenha = false;
	coluna_atual = 0;
	linha_atual = 0;
	desloc += 3;
	while (evento->type != ALLEGRO_EVENT_KEY_DOWN) {
		al_wait_for_event(fila_eventos, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			cont_frames++;
			if (cont_frames >= frames_sprite) {
				cont_frames = 0;
				coluna_atual++;
				if (coluna_atual >= 4)
					coluna_atual = 0;
				regiao_y_folha = linha_atual * sprite_altura;
				regiao_x_folha = coluna_atual * sprite_largura;
			}
			for (i = 10; i > 0; i--)
				al_draw_scaled_bitmap(layers[i], 0, 200, LARGURA_TELA, 593, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
			al_draw_scaled_bitmap(folha, regiao_x_folha, regiao_y_folha, sprite_largura, sprite_altura, (LARGURA_TELA / 400) + desloc, 30 * ALTURA_TELA / 40, 90, 70, 0);
			al_flip_display();
		}
	}
}
void anima_correndo(ALLEGRO_EVENT* evento, bool invertido, int al) {
	int var = 0;
	coluna_atual = 2;
	linha_atual = 1;
	bool sair = false;
	while (1) {
		al_wait_for_event(fila_eventos, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			cont_frames++;
			if (cont_frames >= 8) {
				cont_frames = 0;
				coluna_atual++;
				if (coluna_atual >= 6)
					coluna_atual = 1;
				regiao_y_folha = linha_atual * sprite_altura;
				regiao_x_folha = coluna_atual * sprite_largura;
			}
			for (i = 10; i > 0; i--)
				al_draw_scaled_bitmap(layers[i], 0, 200, LARGURA_TELA, 593, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
			if (invertido) {
				desloc -=3;
				al_draw_scaled_bitmap(folha, regiao_x_folha, regiao_y_folha, sprite_largura, sprite_altura, (LARGURA_TELA / 40) + desloc, 30 * ALTURA_TELA / 40, 90, 70, ALLEGRO_FLIP_HORIZONTAL);
			}
			else {
				desloc +=3;
				al_draw_scaled_bitmap(folha, regiao_x_folha, regiao_y_folha, sprite_largura, sprite_altura, (LARGURA_TELA / 40) + desloc, 30 * ALTURA_TELA / 40, 90, 70, 0);
			}
			al_flip_display();
		}
		else if ((evento->type == ALLEGRO_EVENT_KEY_UP && evento->keyboard.keycode == al)|| (evento->type == ALLEGRO_EVENT_KEY_DOWN))
			break;
	}
}
void anima_pulando(ALLEGRO_EVENT* evento) {
	int altura = 0;
	coluna_atual = 1;
	linha_atual = 2;
	while (linha_atual <= 3 && coluna_atual <= 5) {
		al_wait_for_event(fila_eventos, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			cont_frames++;
			altura++;
			if (cont_frames >= 4) {
				cont_frames = 0;
				coluna_atual++;
				if (coluna_atual >= colunas_folha - 1) {
					coluna_atual = 0;
					linha_atual++;
				}
				if (coluna_atual == 3 && linha_atual == 3)
					break;
				regiao_y_folha = linha_atual * sprite_altura;
				regiao_x_folha = coluna_atual * sprite_largura;
			}
			for (i = 10; i > 0; i--)
				al_draw_scaled_bitmap(layers[i], 0, 200, LARGURA_TELA, 593, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
			al_draw_scaled_bitmap(folha, regiao_x_folha, regiao_y_folha, sprite_largura, sprite_altura, (LARGURA_TELA / 40) + desloc, (30 * ALTURA_TELA / 40) - altura, 90, 70, 0);
			al_flip_display();
		}
	}
}
void anima_ataque(ALLEGRO_EVENT* evento, int conta_ataque) {
	coluna_atual = 0;
	linha_atual = 6+conta_ataque;
	while (1) {
		al_wait_for_event(fila_eventos, evento);
		if (evento->type == ALLEGRO_EVENT_TIMER) {
			cont_frames++;
			if (cont_frames >= 3) {
				cont_frames = 0;
				coluna_atual++;
				if (coluna_atual >= 7)
					coluna_atual = 0;
				if (coluna_atual == 5 || (linha_atual == 7 && coluna_atual == 4))
					break;
				regiao_y_folha = linha_atual * sprite_altura;
				regiao_x_folha = coluna_atual * sprite_largura;
			}
			for (i = 10; i > 0; i--)
				al_draw_scaled_bitmap(layers[i], 0, 200, LARGURA_TELA, 593, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
			al_draw_scaled_bitmap(folha, regiao_x_folha, regiao_y_folha, sprite_largura, sprite_altura, (LARGURA_TELA / 400) + desloc, 30 * ALTURA_TELA / 40, 90, 70, 0);
			al_flip_display();
		}
	}
}