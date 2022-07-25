/* Problema na função ganhou: ela verifica para todos os discos, mas, pela ordem, se uma "componente conexo" de discos da mesma cor não é vencedor, nenhum é, então não precisamos verificar em todos, apenas um. */
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
	if (tab[i][j] != VAZIO) 
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
			if (tab[i][j] == VAZIO) return 0;
		}
	}

	return 1;
}

int _jogar_PvP(char tab[NUM_LIN][NUM_COL], char jogador) {
	int num_jogada = 0; /* Não é usada pra nada mesmo, por enquanto */
	char *txt_jogador;  /* Ponteiro temporário apenas para poder desalocar memória depois */

	cls(); /* Limpamos a tela */
	printtab(tab); /* Imprimimos o tabuleiro */

	do {
		if ( !jogada_player(tab, jogador) ) { /* a jogada é feita */
			continue; /* Se a jogada é ilega, repetimos */
		}

		cls(); /* Limpamos a tela */
		printtab(tab);

		if ( ganhou(tab, jogador) ) {
			txt_jogador = jogador_to_txt(jogador);
			printf("Vitória do jogador %s! Parabéns!\n", txt_jogador);
			free(txt_jogador);

			return num_jogada;
		}

		if ( empatou(tab) ) {
			printf("Empate!! Fim de jogo!\n");
			return num_jogada;
		}

		alterna_jogador(&jogador); num_jogada++;
	} FOREVER;
}

int _jogar_PvC(char tab[NUM_LIN][NUM_COL], char jogador, int dificuldade, bool cerumano_inicia) {
	int num_jogada = 0; /* Não é usada pra nada mesmo, por enquanto */
	char *txt_jogador;  /* Ponteiro temporário apenas para poder desalocar memória depois */

	/* Se o jogador é o cerúmico, fazemos uma jogada extra antes de tudo */
	if (cerumano_inicia)
	{
		cls(); /* Limpamos a tela */
		printtab(tab);
		while (!jogada_player(tab, jogador));
			/* a jogada é feita */
			/* Se a jogada é ilega, repetimos */
	}

	do
	{
		/* Jogada do Computador */
		alterna_jogador(&jogador); num_jogada++;
		cls(); /* Limpamos a tela */
		printtab(tab);
		switch (dificuldade)
		{
		case 1: /* Médio */
			if (!jogada_aleatoria(tab, jogador)) continue; /* Se a jogada é ilegal, repetimos */
			break;

		case 2: /* Difícil */
			if (!jogada_razoavel(tab, jogador)) continue; /* Se a jogada é ilegal, repetimos */
			break;
		}

		/* Verificacoes */
		if ( ganhou(tab, jogador) ) {
			cls();
			printtab(tab);
			txt_jogador = jogador_to_txt(jogador);
			printf("Vitória do jogador %s! Parabéns!\n", txt_jogador);
			free(txt_jogador);

			return num_jogada;
		}

		if ( empatou(tab) ) {
			printf("Empate!! Fim de jogo!\n");
			return num_jogada;
		}
		
		/* Jogada do Cerumano */
		alterna_jogador(&jogador); num_jogada++;
		cls(); /* Limpamos a tela */
		printtab(tab);
		waitFor(1); /* Mostramos a jogada do Computador por 1 segundo */	

		while (!jogada_player(tab, jogador)); /* a jogada é feita */
											/* Se a jogada é ilega, repetimos */

		/* Verificacoes */
		if ( ganhou(tab, jogador) ) {
			cls();
			printtab(tab);
			txt_jogador = jogador_to_txt(jogador);
			printf("Vitória do jogador %s! Parabéns!\n", txt_jogador);
			free(txt_jogador);

			return num_jogada;
		}

		if ( empatou(tab) ) {
			printf("Empate!! Fim de jogo!\n");

			return num_jogada;
		}
	} FOREVER;
}

int _jogar_CvC(char tab[NUM_LIN][NUM_COL], char jogador, int dificuldade) {
	char *txt_jogador;  /* Ponteiro temporário apenas para poder desalocar memória depois */
	int num_jogada = 0; /* Não é usada pra nada mesmo, por enquanto */
	
	do {
		/* Fazemos a jogada */
		switch (dificuldade) {
			/* Médio */
			case 1:
				if ( !jogada_aleatoria(tab, jogador) ) { /* a jogada é feita */
					continue; /* Se a jogada é ilega, repetimos */
				} break;

			/* Difícil */
			case 2:
				if ( !jogada_razoavel(tab, jogador) ) { /* a jogada é feita */
					continue; /* Se a jogada é ilega, repetimos */
				} break;
		}

		cls(); /* Limpamos a tela */
		printtab(tab);
		waitFor(1); /* Mostramos a jogada do Computador por 1 segundo */	

		if ( ganhou(tab, jogador) ) {
			txt_jogador = jogador_to_txt(jogador);
			printf("Vitória do jogador %s! Parabéns!\n", txt_jogador );
			free(txt_jogador);

			return num_jogada;
		}

		if ( empatou(tab) ) {
			printf("Empate!! Fim de jogo!\n");
			return num_jogada;
		}

		alterna_jogador(&jogador); num_jogada++;
	} FOREVER;
}

void waitFor (unsigned int segundos) {
    unsigned int tempo_alvo = time(0) + segundos;   /* tempo_alvo =  1 de janeiro de 1970 + qt. de segundos */
    while (time(0) < tempo_alvo);               	/* loop partindo de 1 de janeiro de 1970 até o tempo alvo */
}