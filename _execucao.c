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
	if (i == NUM_LIN) return contador;

	if (tab[i + 1][j] == jogador)
		return verifica_seq_vertical(tab, i + 1, j, jogador, contador + 1);

	return contador;
}

int verifica_seq_diagonal_direita(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador)
{
	if (i == NUM_LIN || j == NUM_COL) return contador;
	
	if (tab[i+1][j+1] == jogador)
	{
		return verifica_seq_diagonal_direita(tab, i+1, j+1, jogador, contador+1);
	
	}
	return contador;
}

int verifica_seq_diagonal_esquerda(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador)
{
	if (i == NUM_LIN || j == 0) return contador;

	if (tab[i+1][j-1] == jogador)
	{
		return verifica_seq_diagonal_esquerda(tab, i+1, j-1, jogador, contador+1);
	}

	return contador;
}

bool ganhou(char tab[NUM_LIN][NUM_COL], char jogador) 
{ /* Retorna o bool se a cor ganhou */
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
