#include <stdio.h>
#include <string.h>
#include "quatroemlinha.h"

/* Declaração da Main */
/* ------------------ */
int main(void) {
	char tab[NUM_LIN][NUM_COL];

	/* inicializando */
	limpa_tab(tab);

	/* brincando */
	/* tab[5][5] = 'v'; */
	/* tab[4][5] = 'v'; */
	/* tab[3][5] = 'v'; */
	/* tab[2][5] = 'a'; */
	/* tab[5][6] = 'a'; */
	/* tab[4][6] = 'v'; */
	/* tab[5][3] = 'a'; */

	/* printtab(tab); */

	/* if (ganhou(tab, 'v')) printf("Vermelho ganhou!!!\n"); */

	/* inserir_disco(tab, 5, 'v'); */
	/* inserir_disco(tab, 5, 'v'); */
	/* inserir_disco(tab, 5, 'v'); */

	/* printtab(tab); */

	cls();
	jogar(tab, 'v');
    return 0;
}
