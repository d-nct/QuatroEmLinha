#include "quatroemlinha.h"

/* Declaração da Main */
/* ------------------ */
int main(void) {
	char tab[NUM_LIN][NUM_COL];
	int modo;
	int dificuldade;
	bool cerumano_inicia, sair;

	/* Menu */

	do {
		print_menu();
		
		modo = get_int(0, 3, "Insira o modo de jogo: ");
		limpa_tab(tab);

		/*começamos o jogo*/
		switch (modo) {
			case 1: /* Player vs Player */
				_jogar_PvP(tab, jogador_que_comeca);
				break;

			case 2: /* Player vs Computador */ 
				puts("Deseja ser o primeiro a jogar?");
				puts("(0) Não");
				puts("(1) Sim \n");
				
				cerumano_inicia = (bool) get_int(0, 1, "Insira a opção: ");
				
				puts("Dificuldades disponíveis para o Computador:");
				puts("(1) Fácil");
				puts("(2) Médio \n");
			    dificuldade = get_int(1, 2, "Insira a dificuldade: ");

				_jogar_PvC(tab, jogador_que_comeca, dificuldade, cerumano_inicia);
				break;
			
			case 3: /* Computador vs Computador */
				puts("\nDificuldades disponíveis para o Computador:");
				puts("(1) Fácil ");
				puts("(2) Médio \n");
				
				dificuldade = get_int(1, 2, "Insira a dificuldade: ");
				_jogar_CvC(tab, jogador_que_comeca, dificuldade);
				break;

			case 0:
				puts("\nDeseja realmente sair?");

				puts("(0) Não");
				puts("(1) Sim \n");

				sair = (bool) get_int(0, 1, "Insira a opção: ");

				if (sair) return 0;
				else continue;

			default: puts("Opção inválida, vamos tentar de novo!\n"); continue;
		}

		printf("\n  Apita o árbitro: \n--- FIM DE JOGO ---\n\n");

		/* Limpamos a tela e rodamos o ciclo mais uma vez */
		puts("Aperte ENTER para voltar ao menu!"); 
		input_flush();
	} FOREVER;

	return 0;
}
