#include "classes.h"
#include "macros.h"
#include "tipos.h"


void fisica_bomba(struct Inimigo* Goblin, struct Carinha* Principal) {
	if (Goblin->prj.existe) {
		int a = 1;

		if (Goblin->direita == 0)
			a = -1;

		if (Goblin->prj.estado == 0) {
			Goblin->prj.dx -= a * Goblin->prj.veloc;
			Goblin->prj.dy = Goblin->prj.yi + 0.0025 * ((double)Goblin->prj.dx - Goblin->prj.xi) * ((double)Goblin->prj.dx - Goblin->prj.raiz) - (double)(a * 25.0);
		}
		Goblin->prj.caixa.x0 = Goblin->prj.dx + Goblin->prj.img.largura / 2 - 20;
		Goblin->prj.caixa.x1 = Goblin->prj.dx + Goblin->prj.img.largura / 2 + 20;
		Goblin->prj.caixa.y0 = Goblin->prj.dy + Goblin->prj.img.altura / 2 - 20;
		Goblin->prj.caixa.y1 = Goblin->prj.dy + Goblin->prj.img.altura / 2 + 20;
	}
	else
		Goblin->prj.raiz = Principal->cx - 50;
}
