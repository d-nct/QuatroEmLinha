#include <stdio.h>
#include <string.h>
#include "quatroemlinha.h"

/* Declaração das Funções que fazer a ponte Usuário - Processo */
/* ----------------------------------------------------------- */

void print_banner(void) {
	printf(vermelho("                   _  _                                          \n"));
	printf(amarelo ("                  | || |      ___ _ __ ___                       \n"));
	printf(vermelho("                  | || |_    / _ \\ '_ ` _ \\    _______________ \n"));
	printf(amarelo ("                  |__   _|  |  __/ | | | | |  |_______________|  \n"));
	printf(vermelho("                     |_|     \\___|_| |_| |_|                    \n\n\n"));
}

void centralizar(void) {
	printf("                        ");
}

void printtab(char tab[NUM_LIN][NUM_COL]) {
	int i, j;

	const char legenda[] = "  0   1   2   3   4   5   6  \n\n";
	const char sep[]     = "+---+---+---+---+---+---+---+\n";
	
	/* Construimos a parte de cima */
	print_banner();
	centralizar(); printf(legenda);
	
	/* E o resto, de acordo com o tab */
	for (i = 0; i < NUM_LIN; i++) {
		centralizar();
		/* linha com valores */
		for (j = 0; j < NUM_COL; j++) {
			switch (tab[i][j]) {
				case 'v':
					printf("| " VERMELHO " "); break;
				case 'a':
					printf("| " AMARELO " "); break;
				default:
					printf("|   ");
			}
		}
		printf("|\n");

		/* separador */
		centralizar(); printf(sep);
	}
	printf("\n");
	return;
}


void cls(void) {
	printf("\033[2J\033[1;1H");
}
