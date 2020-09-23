#include "classes.h"
#include "macros.h"
//#define DESENHA //hitbox

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
	struct Carinha Principal;
	struct Carinha Goblin;
	struct Projetil Bomba;
	struct Hitbox Chao;


	inicia_goblin(&Goblin,7 * LARGURA_TELA / 10,(28 * ALTURA_TELA / 40));
	inicializa_cara(&Principal);
	carrega_projetil_goblin(&Bomba, &Goblin);

	int tamanho = sizeof(&Principal);

	Chao.x0 = 0;
	Chao.y0 = (32 * ALTURA_TELA / 40) + Principal.imagem_personagem.altura;
	Chao.x1 = LARGURA_TELA;
	Chao.y1 = ALTURA_TELA;

	bool sair = false;
	int conta_ataque = 0;
	int conta_pulo = 0;
	float x1;

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
	Principal.acao_atual = RESPIRA_PRINCIPAL;
	while (!sair) {
		while (!al_event_queue_is_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_KEY_DOWN && Principal.acao_atual != APANHA_PRINCIPAL)
				le_teclado_baixo(&Principal, &Chao,evento.keyboard.keycode);
			else if (evento.type == ALLEGRO_EVENT_KEY_UP)
				le_teclado_alto(&Principal, evento.keyboard.keycode);

			else if (evento.type == ALLEGRO_EVENT_TIMER){
				Principal.caixa.x0 = Principal.cx - 25;
				Principal.caixa.x1 = Principal.cx + 20;
				Principal.caixa.y0 = Principal.cy - 30;
				Principal.caixa.y1 = Principal.cy + 35;

				if (Principal.acao_atual == CORRENDO_PRINCIPAL || Principal.acao_atual == DESLIZA_PRINCIPAL) {
					if (Principal.direita == 0)
						Principal.dx += Principal.veloc;
					else
						Principal.dx -= Principal.veloc;
				}
				else if ((Principal.acao_atual == ATAQUE1_PRINCIPAL || Principal.acao_atual == ATAQUE2_PRINCIPAL || Principal.acao_atual == ATAQUE3_PRINCIPAL) && dist(Principal.cx, Principal.cy,Goblin.cx,Goblin.cy) < 50) {
					Goblin.acao_atual = APANHA_GOBLIN;
					Goblin.block = true;
				}
				else if (Principal.acao_atual == PULO1_PRINCIPAL || Principal.acao_atual == PULO2_PRINCIPAL) {
					if (Principal.acao_atual == PULO1_PRINCIPAL && Principal.ac[PULO1_PRINCIPAL].col_atual == 3) 
						Principal.dy -= 2*Principal.altura_pulo;
					else if(Principal.acao_atual == PULO2_PRINCIPAL)
						Principal.dy -= Principal.altura_pulo;
					if (Principal.acao_espera == CORRENDO_PRINCIPAL) {
						if (Principal.direita == 0)
							Principal.dx += Principal.veloc;
						else
							Principal.dx -= Principal.veloc;
					}
				}


				if (!colisao(&Principal.caixa, &Chao) && (Principal.acao_atual != PULO1_PRINCIPAL && Principal.acao_atual != PULO2_PRINCIPAL)) {
					Principal.dy+=2;
					Principal.acao_atual = CAIR_PRINCIPAL;
					if (Principal.acao_espera == CORRENDO_PRINCIPAL) {
						if (Principal.direita == 0)
							Principal.dx += Principal.veloc;
						else
							Principal.dx -= Principal.veloc;
					}
					Principal.block = true;
				}
				
				comportamento_goblin(&Goblin, &Principal, &Bomba);

				for (int i = 10; i > 0; i--)
					al_draw_scaled_bitmap(layers[i], 0, 230, LARGURA_TELA, 533, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);

				
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

					if (colisao(&Bomba.caixa, &Chao))
						Bomba.estado = 1;
					else if (colisao(&Bomba.caixa, &Principal.caixa)&& Principal.apanha) {
						Bomba.estado = 1;
						Principal.acao_atual = APANHA_PRINCIPAL;
						Principal.block = true;
					}
					anima_projetil(&Bomba);
				}
				else {
					
					 x1 = Principal.cx -50 ;
				}
				#ifdef DESENHA //Hitboxes
				desenha_hitbox(&Chao);
				desenha_hitbox(&Bomba.caixa);
				desenha_hitbox(&Principal.caixa);
				desenha_hitbox(&Goblin.caixa);
				al_draw_circle(Principal.cx, Principal.cy, 50,al_map_rgb(255,255,255),1);
				al_draw_circle(Goblin.cx, Goblin.cy, 50,al_map_rgb(255,255,255),1);
				#endif // Desenha Hitboxes

				anima_personagem(&Goblin, Goblin.acao_atual);
				anima_personagem(&Principal, Principal.acao_atual);
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
	al_set_window_title(janela, "Ainda n�o sei o nome am�m");
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