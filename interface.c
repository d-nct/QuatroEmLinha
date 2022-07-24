#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void cls(void) {
	printf("\033[2J\033[1;1H");
}

char* jogador_to_txt (char jogador) {
	char *texto;

	texto = malloc( 8 * sizeof(char) );
	if (texto == NULL) {ERRO_ALOCACAO}

	jogador == 'v' ? strcpy(texto, vermelho("vermelho") ) : strcpy(texto, amarelo("amarelo") );

	return texto;
}

void print_menu(void)
	{
		cls();
		print_banner();
		puts("MENU");
		puts("----\n");

		/* Obtemos as informações necessárias para começar */
		puts("(1) Player     vs Player");
		puts("(2) Player     vs Computador");
		puts("(3) Computador vs Computador");
		puts("(4) Regras do Jogo");
		puts("(0) Sair");
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

void regras_do_jogo(void)
{
	cls();
	print_banner();
	
	printf("\n");
	puts("******************************************************");
	puts("**************** REGRAS DO JOGO **********************");
	puts("******************************************************");
	printf("\n");

	puts(" 1- Permitido apenas 2 jogadores: Amarelo & Vermelho;");
	puts(" 2- O jogador amarelo sempre começa;");
	puts(" 3- Ao todo são 21 fichas por jogador;");
	puts(" 4- Cada jogador tem direito a uma jogada por turno;");
	puts(" 5- O turno funciona da seguinte forma;");
	puts(" 5.1- O jogador escolhe uma das sete colunas para inserir sua ficha;");
	puts(" 5.2- O jogador posiciona sua ficha no topo da coluna escolhida e a deixa cair.\n    Portanto, a ficha preencherá sempre o espaço mais inferior disponível;");
	puts(" 6- Cada turno resulta na inserção de 1, e somente 1, ficha no tabuleiro;");
	puts(" 7- Não é possível alterar a ficha depois de inserida;");
	puts(" 8- Ganha aquele que formar primeiro uma sequência consecutiva de 4 fichas de mesma cor em qualquer direção.");
}