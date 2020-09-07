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
	//Virou função de inicialização 
	struct Carinha Principal;
	struct Carinha Goblin;
	struct Projetil Bomba;


	inicia_goblin(&Goblin,7*LARGURA_TELA/10 ,(28 * ALTURA_TELA / 40));
	inicializa_cara(&Principal);
	carrega_projetil_goblin(&Bomba, &Goblin);
	
	bool sair = false;
	int conta_ataque = 0;
	int acao_goblin=0;
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

	reseta_acoes(&Principal, 20, 30,Principal.direita);
	reseta_acoes(&Goblin, 20, 30,Goblin.direita);

	while (!sair) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN && !Principal.block){
				switch (evento.keyboard.keycode) {
				case ALLEGRO_KEY_D:
					reseta_acoes(&Principal,20,CORRENDO_PRINCIPAL, Principal.direita);
					Principal.direita = 0;
					Principal.acao_atual = CORRENDO_PRINCIPAL;
					Principal.acao_espera = CORRENDO_PRINCIPAL;
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_A:
					reseta_acoes(&Principal, 20, CORRENDO_PRINCIPAL, Principal.direita);
					Principal.direita = ALLEGRO_FLIP_HORIZONTAL;
					Principal.acao_atual = CORRENDO_PRINCIPAL;
					Principal.acao_espera = CORRENDO_PRINCIPAL;
					conta_ataque = 0;
					break;
				case ALLEGRO_KEY_LSHIFT:
					reseta_acoes(&Principal, 20, CORRENDO_PRINCIPAL, Principal.direita);
					Principal.acao_atual = DESLIZA_PRINCIPAL;
					Principal.block = true;
					break;
				case ALLEGRO_KEY_S:
					break;
				case ALLEGRO_KEY_J:
					reseta_acoes(&Principal, 20,	ATAQUE1_PRINCIPAL, Principal.direita);
					if (conta_ataque == 2) {
						Principal.acao_atual = ATAQUE3_PRINCIPAL;
						conta_ataque=0;
					}
					else if (conta_ataque == 1) {
						Principal.acao_atual = ATAQUE2_PRINCIPAL;
						conta_ataque ++;
					}
					else {
						Principal.acao_atual = ATAQUE1_PRINCIPAL;
						conta_ataque ++;
					}
					Principal.block = true;
					break;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
				switch (evento.keyboard.keycode) {
				case ALLEGRO_KEY_D:
					Principal.acao_espera = 0;
					if (Principal.acao_atual == CORRENDO_PRINCIPAL && Principal.direita == 0)
						Principal.acao_atual = RESPIRA_PRINCIPAL;
					reseta_acao(&Principal.ac[CORRENDO_PRINCIPAL]);
					break;
				case ALLEGRO_KEY_A:
					Principal.acao_espera = 0;
					if (Principal.acao_atual == CORRENDO_PRINCIPAL && Principal.direita == ALLEGRO_FLIP_HORIZONTAL)
						Principal.acao_atual = RESPIRA_PRINCIPAL;
					reseta_acao(&Principal.ac[CORRENDO_PRINCIPAL]);
					break;
				case ALLEGRO_KEY_W:
					//reseta_acao(Principal.ac[CORRENDO_PRINCIPAL]);
					break;
				case ALLEGRO_KEY_S:
					//reseta_acao(Principal.ac[CORRENDO_PRINCIPAL]);
					break;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_TIMER){
				if (Principal.acao_atual == CORRENDO_PRINCIPAL || Principal.acao_atual == DESLIZA_PRINCIPAL) {
					if(Principal.direita == 0)
						Principal.dx += Principal.veloc;
					else
						Principal.dx -= Principal.veloc;
				}

				if (!Goblin.block) {
					if (Goblin.dx < Principal.dx - 50)
						Goblin.direita = 0;
					else Goblin.direita = ALLEGRO_FLIP_HORIZONTAL;

					if (Goblin.cx + 74 > Principal.cx && Principal.cx > Goblin.cx - 74) {
						Goblin.acao_atual = GOBLIN_BATENDO;
						Goblin.block = true;
					}
					else if (Goblin.cx + 200 > Principal.cx && Principal.cx > Goblin.cx - 200)
						Goblin.acao_atual = CORRENDO_GOBLIN;
					else if (Goblin.cx + 400 > Principal.cx && Principal.cx > Goblin.cx - 400 && !Bomba.existe) {
						Goblin.acao_atual = TACA_BOMBAGOBLIN;
						Goblin.block = true;
					}

					else
						Goblin.acao_atual = PARADO_GOBLIN;
					if (Goblin.acao_atual == CORRENDO_GOBLIN) {
						if (Goblin.direita == 0)
							Goblin.dx += Goblin.veloc;
						else Goblin.dx -= Goblin.veloc;
					}
				}

				for (int i = 10; i > 0; i--)
					al_draw_scaled_bitmap(layers[i], 0, 230, LARGURA_TELA, 533, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);

				anima_personagem(&Goblin, Goblin.acao_atual);
				anima_personagem(&Principal, Principal.acao_atual);
				if (Goblin.acao_atual == TACA_BOMBAGOBLIN && Goblin.ac[TACA_BOMBAGOBLIN].col_atual == Goblin.ac[TACA_BOMBAGOBLIN].finalX)
					Bomba.existe = true;
				if (Bomba.existe) {
					int a = 1;
					int x1;
					if (Goblin.direita == 0)
						a = -1;
					if (Bomba.frame_atual == 0 && Bomba.col_atual == 0) {
						Bomba.xi = Goblin.cx-Bomba.img.largura/2 -a*40;
						Bomba.yi = Goblin.cy-Bomba.img.largura / 2-10;
						x1 = Principal.cx - 50;
					}
					Bomba.dx = Bomba.xi -a*Bomba.veloc * (Bomba.frame_atual + Bomba.col_atual*Bomba.num_frames);
					//Bomba.dy = Bomba.yi;
					Bomba.dy =Bomba.yi + 0.0025*(Bomba.dx - Bomba.xi)*(Bomba.dx - x1);
					anima_projetil(&Bomba);
				}
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
	if (!al_install_keyboard()) {
		return false;
	}
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!janela)
		return false;
	al_set_window_title(janela, "Ainda não sei o nome amém");
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