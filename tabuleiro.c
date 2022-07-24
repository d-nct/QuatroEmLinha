#include "quatroemlinha.h"

/* Funções para manipular o tabuleiro */
	/* ---------------------------------- */

void preenche_tab(char tab[NUM_LIN][NUM_COL], char elemento) {
	/* Preenche todas as casas de tab com o elemento */
	int i, j;
	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			tab[i][j] = elemento;
		}
	}
}

void limpa_tab(char tab[NUM_LIN][NUM_COL]) {
	preenche_tab(tab, VAZIO);
}