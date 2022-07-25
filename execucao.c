#include "quatroemlinha.h"

/* Declaração das funções úteis para efetivamente jogar o jogo */
/* ----------------------------------------------------------- */

void alterna_jogador(char *jogador) {
	if (*jogador == 'v') {
		*jogador = 'a';
		return;
	}
	
	*jogador = 'v';
}

int inserir_disco(char tab[NUM_LIN][NUM_COL], int coluna, char jogador, bool verbose) {
	/* Retorna 1 se a jogada ocorreu com sucesso */
	/* 	       0 se a jogada não ocorreu (ilegal) */
	char *txt_jogador;  /* Ponteiro temporário apenas para poder desalocar memória depois */
	int i;

	/* A coluna já temos; a linha iteramos de baixo para cima até ter um espaço vazio */
	for (i = NUM_LIN; i > 0; i--) {
		if (tab[i][coluna] == 'x') break;
	}

	/* Testamos se a jogada é legal */
	/* não seria mais fácil simplesmente verificar se i é diferente de 0 aqui? */
	if (jogada_eh_legal(tab, jogador, i, coluna)) {
		tab[i][coluna] = jogador;
		return 1;
	}
	else {
		if (verbose) {
			txt_jogador = jogador_to_txt(jogador);
			printf("A jogada do jogador %s na coluna %i (coordenadas %d, %d) é ilegal! Jogue novamente.\n", txt_jogador, coluna, i, coluna);
			free(txt_jogador);
		}
		return 0;
	}
}