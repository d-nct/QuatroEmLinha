/* Problema na função ganhou: ela verifica para todos os discos, mas, pela ordem, se uma "componente conexo" de discos da mesma cor não é vencedor, nenhum é, então não precisamos verificar em todos, apenas um. */

#include <stdio.h>
#include <string.h>

#define FOREVER while(1)

#define RESET    "\x1b[0m"

/* Letra colorida */
/* #define VERMELHO "\x1b[31m" "O" RESET */
/* #define AMARELO  "\x1b[33m" "O" RESET */

/* Background colorido */
#define VERMELHO "\x1b[41m" " " RESET
#define AMARELO  "\x1b[43m" " " RESET

#define NUM_CR_LIN 29 +1

#define NUM_LIN 6
#define NUM_COL 7

/* Protótipos */
/* ---------- */
void printtab(char tab[NUM_LIN][NUM_COL]);


void preenche_tab(char tab[NUM_LIN][NUM_COL], char elemento);
void limpa_tab(char tab[NUM_LIN][NUM_COL]);

int verifica_seq_horizontal(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador); /* Retorna o tamanho da sequencia horizontal do jogador a partir das coordenadas i,j */
int ganhou(char tab[NUM_LIN][NUM_COL], char jogador); /* Retorna o bool se a cor ganhou */

int inserir_disco(char tab[NUM_LIN][NUM_COL], int coluna, char jogador);
int jogada_eh_legal(char tab[NUM_LIN][NUM_COL], char jogador, int i, int j);

int jogar(char tab[NUM_LIN][NUM_COL], char jogador_que_comeca);

/* Declaração das Funções */
/* ---------------------- */
int main(void) {
	int i, j;
	char tab[NUM_LIN][NUM_COL];

	/* inicializando */
	limpa_tab(tab);

	/* brincando */
	/* tab[5][5] = 'v'; */
	/* tab[4][5] = 'v'; */
	/* tab[3][5] = 'v'; */
	/* tab[2][5] = 'a'; */
	/* tab[5][6] = 'a'; */
	/* tab[4][6] = 'v'; */
	/* tab[5][3] = 'a'; */

	/* printtab(tab); */

	/* if (ganhou(tab, 'v')) printf("Vermelho ganhou!!!\n"); */

	/* inserir_disco(tab, 5, 'v'); */
	/* inserir_disco(tab, 5, 'v'); */
	/* inserir_disco(tab, 5, 'v'); */

	/* printtab(tab); */

	jogar(tab, 'v');
    return 0;
}


void printtab(char tab[NUM_LIN][NUM_COL]) {
	int i, j;

	const char legenda[] = "  0   1   2   3   4   5   6  \n\n";
	const char sep[]     = "+---+---+---+---+---+---+---+\n";
	
	/* Construimos a parte de cima */
	printf(legenda);
	
	/* E o resto, de acordo com o tab */
	for (i = 0; i < NUM_LIN; i++) {
		/* linha com valores */
		for (j = 0; j < NUM_COL; j++) {
			switch (tab[i][j]) {
				case 'v':
					printf("| " VERMELHO " "); break;
				case 'a':
					printf("| " AMARELO " "); break;
				default:
					printf("|   ");
			}
		}
		printf("|\n");

		/* separador */
		printf(sep);
	}
	return;
}


void cls(void) {
	printf("\033[2J\033[1;1H");
}

int verifica_seq_horizontal(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador) { /* Retorna o bool se a cor ganhou */
	if (j == NUM_COL) return contador ; /* Impedimos de acessar uma coluna que não existe */
	/* se o disco da direita é da mesma cor, a seq cresce em 1 */
	if (tab[i][j+1] == jogador) {
		return verifica_seq_horizontal(tab, i, j+1, jogador, contador+1); /* caminhamos um para direita */
	}
	/* se o disco da direita é diferente, a seq para de crescer e retornamos seu tamanho */
	return contador;
}

int ganhou(char tab[NUM_LIN][NUM_COL], char jogador) { /* Retorna o bool se a cor ganhou */
	int i, j;
	int discos_em_seq;

	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			if (tab[i][j] == jogador) {
				discos_em_seq = verifica_seq_horizontal(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;

				/*
				discos_em_seq = verifica_seq_vertical(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;
				
				discos_em_seq = verifica_seq_diagonal(tab, i, j, jogador, 1);
				if (discos_em_seq >= 4) return 1;
				*/
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

int inserir_disco(char tab[NUM_LIN][NUM_COL], int coluna, char jogador) {
	/* Retorna 1 se a jogada ocorreu com sucesso */
	/* 	       0 se a jogada não ocorreu (ilegal) */
	int i;

	/* A coluna já temos; a linha iteramos de baixo para cima até ter um espaço vazio */
	for (i = NUM_LIN; i > 0; i--) {
		if (tab[i][coluna] == 'x') break;
	}

	/* Testamos se a jogada é legal */
	if (jogada_eh_legal(tab, jogador, i, coluna)) {
		tab[i][coluna] = jogador;
		return 1;
	}
	else {
		printf("A jogada do jogador %c na coluna %i (coordenadas %d, %d) é ilegal! Jogue novamente.\n", jogador, coluna, i, coluna);
		return 0;
	}
}

void preenche_tab(char tab[NUM_LIN][NUM_COL], char elemento) {
	/* Preenche todas as casas de tab com o elemento */
	int i, j;
	for (i = 0; i < NUM_LIN; i++) {
		for (j = 0; j < NUM_COL; j++) {
			tab[i][j] = elemento;
		}
	}
}

void limpa_tab(char tab[NUM_LIN][NUM_COL]) {
	preenche_tab(tab, 'x');
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

void alterna_jogador(char *jogador) {
	if (*jogador == 'v') {
		*jogador = 'a';
		return;
	}
	
	*jogador = 'v';
}

int jogada(char tab[NUM_LIN][NUM_COL], char jogador) {
	int coluna;

	printf("Jogador %c, deseja jogar seu disco em qual coluna? > ", jogador);
	scanf("%d", &coluna);

	return inserir_disco(tab, coluna, jogador);
}

int jogar(char tab[NUM_LIN][NUM_COL], char jogador_que_comeca) {
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

	printtab(tab);
	do {
		if ( !jogada(tab, jogador) ) { /* a jogada é feita */
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
