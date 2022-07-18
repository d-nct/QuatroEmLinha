/* Problema na função ganhou: ela verifica para todos os discos, mas, pela ordem, se uma "componente conexo" de discos da mesma cor não é vencedor, nenhum é, então não precisamos verificar em todos, apenas um. */

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
int ganhou(char tab[NUM_LIN][NUM_COL], char jogador); /* Retorna o bool se a cor ganhou */
int verifica_seq_horizontal(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador); /* Retorna o tamanho da sequencia horizontal do jogador a partir das coordenadas i,j */

int main(void) {
	int i, j;
	char tab[NUM_LIN][NUM_COL];

	/* inicializando */
	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			tab[i][j] = 'v';
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

	if (ganhou(tab, 'v')) printf("Vermelho ganhou!!!\n");


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


void cls(void) {
	printf("\033[2J\033[1;1H");
}

int verifica_seq_horizontal(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador) { /* Retorna o bool se a cor ganhou */
	if (j == NUM_COL) return contador -1; /* Impedimos de acessar uma coluna que não existe */
	/* se o disco da direita é da mesma cor, a seq cresce em 1 */
	if (tab[i][j+1] == jogador) {
		return verifica_seq_horizontal(tab, i, j+1, jogador, contador+1); /* caminhamos um para direita */
	}
	/* se o disco da direita é diferente, a seq para de crescer e retornamoss seu tamanho */
	return contador -1;
}

int ganhou(char tab[NUM_LIN][NUM_COL], char jogador) { /* Retorna o bool se a cor ganhou */
	int i, j;
	int discos_em_seq;

	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			if (tab[i][j] == jogador) {
				discos_em_seq = verifica_seq_horizontal(tab, i, j, jogador, 1);
				/* printf("%d\n", discos_em_seq); */
				if (discos_em_seq >= 4) return 1;

				/*
				discos_em_seq = verifica_seq_vertical(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;
				
				discos_em_seq = verifica_seq_diagonal(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;
				*/
			}
		}
	}
	return 0;
}
