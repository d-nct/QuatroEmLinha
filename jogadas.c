#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "quatroemlinha.h"

/* Inicializamos a randomness */

int jogada_aleatoria(char tab[NUM_LIN][NUM_COL], char jogador) {
	srand(time(NULL));
	return inserir_disco(tab, rand() % NUM_COL, jogador);
}

int jogada_player(char tab[NUM_LIN][NUM_COL], char jogador) {
	int coluna;

	printf("Jogador %c, deseja jogar seu disco em qual coluna? > ", jogador);
	scanf("%d", &coluna);

	return inserir_disco(tab, coluna, jogador);
}
