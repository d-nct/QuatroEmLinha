#include <stdio.h>
#include <string.h>
#include "quatroemlinha.h"

void limpa_stdin(void) {
	char c;
	do {c = fgetc(stdin);} while (c != '\n');
}

/* Declaração da Main */
/* ------------------ */
int main(void) {
	char tab[NUM_LIN][NUM_COL];
	int modo;
	char jogador_que_comeca;

	cls();

	/* Menu */
	do {

		print_banner();
		puts("MENU");
		puts("----\n");

		/* Obtemos as informações necessárias para começar */
		puts("(1) Player     vs Player");
		puts("(2) Player     vs Computador");
		puts("(3) Computador vs Computador");
		puts("(0) Sair");

		printf("Em qual modo deseja jogar? \n > ");
		if (!scanf("%d", &modo)) {ERRO_LEITURA} limpa_stdin();
		switch (modo) {
			case 1: case 2: case 3: case 0: break;
			default: puts("Opção inválida, vamos tentar de novo!\n"); continue;
		}

		puts("\n(v) \x1b[41mVermelho" RESET);
		puts("(a) \x1b[43mAmarelo" RESET);
		printf("Qual jogador começa? \n > ");
		if (!scanf("%c", &jogador_que_comeca)) {ERRO_LEITURA} limpa_stdin();
		switch (jogador_que_comeca) {
			case 'V': case 'v': case 'A': case 'a': break;
			default: puts("Opção inválida, vamos tentar de novo!\n"); continue;
		}

		/* Verificamos se o usuário deseja jogar */
		if (modo == 0) return 0;

		/* Começamos o jogo */
		cls();
		limpa_tab(tab);
		jogar(tab, jogador_que_comeca, modo);
		printf("\n  Apita o árbitro: \n--- FIM DE JOGO ---\n\n");

		/* Limpamos a tela e rodamos o ciclo mais uma vez */
		puts("Aperte ENTER para voltar ao menu!"); 
		scanf("%d", &modo);/* TODO: getchar nn tava funfando */
		cls();
	} FOREVER;

	return 0;
}
