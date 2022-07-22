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

int inserir_disco(char tab[NUM_LIN][NUM_COL], int coluna, char jogador) {
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
		printf("A jogada do jogador %c na coluna %i (coordenadas %d, %d) é ilegal! Jogue novamente.\n", jogador, coluna, i, coluna);
		return 0;
	}
}


int jogar(char tab[NUM_LIN][NUM_COL], char jogador_que_comeca, int modo) {
	/* Retorna o numero de jogadas */
	/* 		-1 se houve erro */
	int num_jogada = 0; /* Não é usada pra nada mesmo, por enquanto */

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
		case 1: 
			do {
				if ( !jogada_player(tab, jogador) ) { /* a jogada é feita */
					continue; /* Se a jogada é ilega, repetimos */
				}

				cls(); /* Limpamos a tela */
				printtab(tab);

				if ( ganhou(tab, jogador) ) {
					printf("Vitória do jogador %c! Parabéns!\n", jogador);
					return num_jogada;
				}

				if ( empatou(tab) ) {
					printf("Empate!! Fim de jogo!\n");
					return num_jogada;
				}

				alterna_jogador(&jogador); num_jogada++;
			} FOREVER;

		/* Player vs Computador */
		case 2:
			/* Player é o vermelho! */
			do {
				if ( jogador == 'v' ) {
					if ( !jogada_player(tab, jogador) ) { /* a jogada é feita */
						continue; /* Se a jogada é ilega, repetimos */
					}
				}
				else {
					if ( !jogada_aleatoria(tab, jogador) ) { /* a jogada é feita */
						continue; /* Se a jogada é ilega, repetimos */
					}
				}

				cls(); /* Limpamos a tela */
				printtab(tab);

				if ( ganhou(tab, jogador) ) {
					printf("Vitória do jogador %c! Parabéns!\n", jogador);
					return num_jogada;
				}

				if ( empatou(tab) ) {
					printf("Empate!! Fim de jogo!\n");
					return num_jogada;
				}

				alterna_jogador(&jogador); num_jogada++;
			} FOREVER;
	}
	return 0;
}
