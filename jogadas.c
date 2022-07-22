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

int jogada_razoavel(char tab[NUM_LIN][NUM_COL], char jogador) {
	int ret;

	int jogada_ganhadora, jogada_perdedora;
	char outro = jogador; alterna_jogador(&outro);
	
	/* Se possível, ganhamos o jogo */
	jogada_ganhadora = coluna_de_jogada_ganhadora(tab, jogador);
	if (jogada_ganhadora != -1) {
		#ifdef DEBUG
		printf("Entramos em Jogada Ganhadora\n");
		#endif
		ret = inserir_disco(tab, jogada_ganhadora, jogador, SILENT);
		return ret;
	}

	/* Se não, evitamos perder */
	jogada_perdedora = coluna_de_jogada_ganhadora(tab, outro);
	if (jogada_perdedora != -1) {
		#ifdef DEBUG
		printf("Entramos em Jogada Perdedora\n");
		#endif
		ret = inserir_disco(tab, jogada_perdedora, jogador, SILENT);
		return ret;
	}

	/* Se não pudermos ganhar E não estivermos em perigo, escolhemos uma coluna aleatória */
	#ifdef DEBUG
	printf("Jogada Aleatoria\n");
	#endif
	ret = jogada_aleatoria(tab, jogador);
	return ret;
}

void copia_tab(char tab[NUM_LIN][NUM_COL], char tab_copia[NUM_LIN][NUM_COL]) {
	int i, j;
	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			tab_copia[i][j] = tab[i][j];
		}
	}
}

int coluna_de_jogada_ganhadora(char tab[NUM_LIN][NUM_COL], char jogador)
{
	int j;
	char tab2[NUM_LIN][NUM_COL]; /* tabuleiro copia */
	
	copia_tab(tab, tab2);

	/* verifica horizontal */
	for (j = 0; j < NUM_COL; j++) {
		inserir_disco(tab2, j, jogador, SILENT);
		if (ganhou(tab2, jogador)) {
			return j;
		}
		copia_tab(tab, tab2);
	}
	return -1;
}

int jogada_aleatoria(char tab[NUM_LIN][NUM_COL], char jogador) {
	#ifdef DEBUG
	int x, i;
	#endif
	srand(time(NULL));
	waitFor(1);
	#ifdef DEBUG
	for (i = 0; i < 7; i++) {
		x = rand() % NUM_COL;
		printf("rand = %i\n", x);
	}
	#endif
	return inserir_disco(tab, rand() % NUM_COL, jogador, SILENT);
}

int jogada_player(char tab[NUM_LIN][NUM_COL], char jogador) {
	int coluna;

	printf("Jogador %c, deseja jogar seu disco em qual coluna? > ", jogador);
	scanf("%d", &coluna);

	return inserir_disco(tab, coluna, jogador, VERBOSE);
}
