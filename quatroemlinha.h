#include<stdlib.h>

#define FOREVER while(1)

#define LETRA

#define RESET    "\x1b[0m"

/* Letra colorida */
#ifdef LETRA
#define VERMELHO      "\x1b[31m" "O" RESET
#define vermelho(TXT) "\x1b[31m" TXT RESET

#define AMARELO       "\x1b[33m" "O" RESET
#define amarelo(TXT)  "\x1b[33m" TXT RESET
#endif

/* Background colorido */
#ifdef FUNDO
#define VERMELHO      "\x1b[41m" " " RESET
#define vermelho(TXT) "\x1b[41m" TXT RESET

#define AMARELO       "\x1b[43m" "O" RESET
#define amarelo(TXT)  "\x1b[43m" TXT RESET
#endif

#define NUM_CR_LIN 29 +1

#define NUM_LIN 6
#define NUM_COL 7

#define ERRO_LEITURA printf("Ocorreu um erro de leitura. Tente novamente!\n"); exit(1);

/* Tipos */
typedef int bool;

/* Protótipos */
/* ---------- */
void printtab(char tab[NUM_LIN][NUM_COL]);
void print_banner(void);
void cls(void);


void preenche_tab(char tab[NUM_LIN][NUM_COL], char elemento);
void limpa_tab(char tab[NUM_LIN][NUM_COL]);

int verifica_seq_horizontal(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador); /* Retorna o tamanho da sequencia horizontal do jogador a partir das coordenadas i,j */
int verifica_seq_vertical(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador);
int verifica_seq_diagonal_direita(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador);
int verifica_seq_diagonal_esquerda(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador);
int ganhou(char tab[NUM_LIN][NUM_COL], char jogador); /* Retorna o bool se a cor ganhou */
int empatou(char tab[NUM_LIN][NUM_COL]);

int inserir_disco(char tab[NUM_LIN][NUM_COL], int coluna, char jogador);
int jogada_eh_legal(char tab[NUM_LIN][NUM_COL], char jogador, int i, int j);

int jogada_aleatoria(char tab[NUM_LIN][NUM_COL], char jogador);
int jogada_player(char tab[NUM_LIN][NUM_COL], char jogador);
int jogar(char tab[NUM_LIN][NUM_COL], char jogador_que_comeca, int modo);
