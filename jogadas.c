#include "quatroemlinha.h"

int jogada_razoavel(char tab[NUM_LIN][NUM_COL], char jogador) {
	int jogada_ganhadora, jogada_perdedora;
	char outro = jogador; alterna_jogador(&outro);
	
	/* Se possível, ganhamos o jogo */
	jogada_ganhadora = coluna_de_jogada_ganhadora(tab, jogador);
	if (jogada_ganhadora != FORA_DO_TAB) {
		#ifdef DEBUG
		printf("Entramos em Jogada Ganhadora\n");
		#endif

		return inserir_disco(tab, jogada_ganhadora, jogador, SILENT);
	}

	/* Se não, evitamos perder */
	jogada_perdedora = coluna_de_jogada_ganhadora(tab, outro);
	if (jogada_perdedora != FORA_DO_TAB) {
		#ifdef DEBUG
		printf("Entramos em Jogada Perdedora\n");
		#endif

		return inserir_disco(tab, jogada_perdedora, jogador, SILENT);
	}

	/* Se não pudermos ganhar E não estivermos em perigo, escolhemos uma coluna aleatória */
	#ifdef DEBUG
	printf("Jogada Aleatoria\n");
	#endif
	return jogada_aleatoria(tab, jogador);
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
	return FORA_DO_TAB;
}

int jogada_aleatoria(char tab[NUM_LIN][NUM_COL], char jogador) {
	return inserir_disco(tab, rand() % NUM_COL, jogador, SILENT);
}

int jogada_player(char tab[NUM_LIN][NUM_COL], char jogador) {
	int coluna;
	char *txt_jogador;

	txt_jogador = jogador_to_txt(jogador);
	printf("Jogador %s, deseja jogar seu disco em qual coluna?", txt_jogador);
	coluna = get_int(0, NUM_COL - 1, " > ");
	free(txt_jogador);

	return inserir_disco(tab, coluna, jogador, VERBOSE);
}
