#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "quatroemlinha.h"


void waitFor (unsigned int secs) {
	/* Fonte: https://stackoverflow.com/questions/3930363/implement-time-delay-in-c */
    unsigned int retTime = time(0) + secs;   /* Get finishing time. */
    while (time(0) < retTime);               /* Loop until it arrives. */
}

int jogada_aleatoria(char tab[NUM_LIN][NUM_COL], char jogador) {
	srand(time(NULL));
	waitFor(1);
	return inserir_disco(tab, rand() % NUM_COL, jogador);
}

int jogada_player(char tab[NUM_LIN][NUM_COL], char jogador) {
	int coluna;

	printf("Jogador %c, deseja jogar seu disco em qual coluna? > ", jogador);
	scanf("%d", &coluna);

	return inserir_disco(tab, coluna, jogador);
}
