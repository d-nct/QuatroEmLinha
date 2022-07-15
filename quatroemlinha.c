/* Essa implementação vai dar problema por causa da alocação estática: */
/*   Teremos um byte para o  O  do jogador, mas pra imprimir, precisamos de muito */ 
/*   mais que isso. */
/* Solução: Guardar apenas back end do tabuleiro numa matriz 6 x 7, sem as */ 
/*   linhas, divisorias etc */
/*   Assim, na hora de imprimir linha a linha, simplesmente colocamos as cores sem */
/*   medo de colocar mais bytes do que deviamos numa string. */

#include <stdio.h>
#include <string.h>

#define RESET    "\x1b[0m"

/* Letra colorida */
/* #define VERMELHO "\x1b[31m" "O" RESET */
/* #define AMARELO  "\x1b[33m" "O" RESET */

/* Background colorido */
#define VERMELHO "\x1b[41m" " " RESET
#define AMARELO  "\x1b[43m" " " RESET

#define NUM_CR_LIN 29 +1

#define NUM_LIN 6
#define NUM_COL 7

void printtab(char tab[NUM_LIN][NUM_COL]);

int main(void) {
	int i, j;
	char tab[NUM_LIN][NUM_COL];

	/* inicializando */
	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			tab[i][j] = 'x';
		}
	}

	/* brincando */
	tab[5][5] = 'v';
	tab[4][5] = 'v';
	tab[3][5] = 'v';
	tab[2][5] = 'a';
	tab[5][6] = 'a';
	tab[4][6] = 'v';
	tab[5][3] = 'a';

	printtab(tab);


    return 0;
}


void printtab(char tab[NUM_LIN][NUM_COL]) {
	int i, j;

	const char legenda[] = "  0   1   2   3   4   5   6  \n\n";
	const char sep[]     = "+---+---+---+---+---+---+---+\n";
	
	/* Construimos a parte de cima */
	printf(legenda);
	
	/* E o resto, de acordo com o tab */
	for (i = 0; i < NUM_LIN; i++) {
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
		printf(sep);
	}
	return;
}
