#include <stdio.h>
#include <string.h>
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
		if (verbose) 
			printf("A jogada do jogador %c na coluna %i (coordenadas %d, %d) é ilegal! Jogue novamente.\n", jogador, coluna, i, coluna);
		return 0;
	}
}


int jogar(char tab[NUM_LIN][NUM_COL], char jogador_que_comeca, int modo, int dificuldade) {
	/* Retorna o numero de jogadas */
	/* 		-1 se houve erro */

	char jogador;

	/* Definindo os jogadores: */
	if (jogador_que_comeca == 'v' || jogador_que_comeca == 'a') {
		jogador = jogador_que_comeca;
	}
	else {
		printf("O jogador %c não existe! Erro.\n", jogador_que_comeca);
		return -1;
	}

	/* Jogamos de fato */
	printtab(tab);
	switch (modo) {
		/* Player vs Player */
		case 1: return _jogar_PvP(tab, jogador, modo);

		/* Player vs Computador */
		case 2: _jogar_PvC(tab, jogador, modo, dificuldade);

		/* Computador vs Computador */
		case 3: _jogar_CvC(tab, jogador, modo, dificuldade);

	}
	return 0;
}
