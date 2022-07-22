/* Problema na função ganhou: ela verifica para todos os discos, mas, pela ordem, se uma "componente conexo" de discos da mesma cor não é vencedor, nenhum é, então não precisamos verificar em todos, apenas um. */

#include <stdio.h>
#include <string.h>
#include "quatroemlinha.h"

/* Funções úteis num nível abaixo para a execução do jogo  e verificadores */
/* ----------------------------------------------------------------------- */

int verifica_seq_horizontal(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador) { /* Retorna o bool se a cor ganhou */
	if (j == NUM_COL) return contador ; /* Impedimos de acessar uma coluna que não existe */
	/* se o disco da direita é da mesma cor, a seq cresce em 1 */
	if (tab[i][j+1] == jogador) {
		return verifica_seq_horizontal(tab, i, j+1, jogador, contador+1); /* caminhamos um para direita */
	}
	/* se o disco da direita é diferente, a seq para de crescer e retornamos seu tamanho */
	return contador;
}

int verifica_seq_vertical(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador)
{
	if (i == NUM_LIN - 1) return contador;

	if (tab[i + 1][j] == jogador)
		return verifica_seq_vertical(tab, i + 1, j, jogador, contador + 1);

	return contador;
}

int verifica_seq_diagonal_direita(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador)
{
	if (i == (NUM_LIN - 1) || j == (NUM_COL - 1)) return contador;
	
	if (tab[i+1][j+1] == jogador)
	{
		return verifica_seq_diagonal_direita(tab, i+1, j+1, jogador, contador+1);
	
	}
	return contador;
}

int verifica_seq_diagonal_esquerda(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador)
{
	if (i == (NUM_LIN -1) || j == 0) return contador;

	if (tab[i+1][j-1] == jogador)
	{
		return verifica_seq_diagonal_esquerda(tab, i+1, j-1, jogador, contador+1);
	}

	return contador;
}

bool ganhou(char tab[NUM_LIN][NUM_COL], char jogador) 
{ /* Retorna o bool se a cor ganhou */
/* TODO: Implementar destaque na tela quando ganhou retorna TRUE */
	int i, j;
	int discos_em_seq;

	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			if (tab[i][j] == jogador) {
				discos_em_seq = verifica_seq_horizontal(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;

				discos_em_seq = verifica_seq_vertical(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;
				
				discos_em_seq = verifica_seq_diagonal_direita(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;

				discos_em_seq = verifica_seq_diagonal_esquerda(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;
			}
		}
	}
	return 0;
}

int jogada_eh_legal(char tab[NUM_LIN][NUM_COL], char jogador, int i, int j) {
	/* Retorna 1 se a jogada é legal */
	/* 	       0 se a jogada é ilegal */

	/* Testamos se as coordenadas pertencem ao tabuleiro */
	if (i < 0 || i >= NUM_LIN || j < 0 || j >= NUM_COL)
		return 0;

	/* Se a coordenada já possui um disco, a jogada é ilegal */
	if (tab[i][j] != 'x') 
		return 0;

	/* Se passou nos teste, é legal */
	return 1;
}



int empatou(char tab[NUM_LIN][NUM_COL]) {
	/* Retorna 1 se todas as casas estão ocupadas */
	/*		   0 se há pelo menos uma casa livre */
	int i, j;

	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			if (tab[i][j] == 'x') return 0;
		}
	}

	return 1;
}

int _jogar_PvP(char tab[NUM_LIN][NUM_COL], char jogador, int modo) {
	int num_jogada = 0; /* Não é usada pra nada mesmo, por enquanto */

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
}

int _jogar_PvC(char tab[NUM_LIN][NUM_COL], char jogador, int modo, int dificuldade) {
	int num_jogada = 0; /* Não é usada pra nada mesmo, por enquanto */

	/* Player é o vermelho! */
	do {
		if ( jogador == 'v' ) {
			if ( !jogada_player(tab, jogador) ) { /* a jogada é feita */
				continue; /* Se a jogada é ilega, repetimos */
			}
		}
		else {
			switch (dificuldade) {
				/* Fácil */
				case 1:
					if ( !jogada_aleatoria(tab, jogador) ) { /* a jogada é feita */
						continue; /* Se a jogada é ilega, repetimos */
					} break;

				/* Médio */
				case 2:
					if ( !jogada_razoavel(tab, jogador) ) { /* a jogada é feita */
						continue; /* Se a jogada é ilega, repetimos */
					} break;

				/* Difícil */
				/*case 3:
					if ( !jogada_inteligente(tab, jogador) ) { 
						continue; 
					} break; */
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

int _jogar_CvC(char tab[NUM_LIN][NUM_COL], char jogador, int modo, int dificuldade) {
	int num_jogada = 0; /* Não é usada pra nada mesmo, por enquanto */

	do {
		switch (dificuldade) {
			/* Fácil */
			case 1:
				if ( !jogada_aleatoria(tab, jogador) ) { /* a jogada é feita */
					continue; /* Se a jogada é ilega, repetimos */
				} break;

			/* Médio */
			case 2:
				if ( !jogada_razoavel(tab, jogador) ) { /* a jogada é feita */
					continue; /* Se a jogada é ilega, repetimos */
				} break;

			/* Difícil */
			/*case 3:
				if ( !jogada_inteligente(tab, jogador) ) { 
					continue; 
				} break; */
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