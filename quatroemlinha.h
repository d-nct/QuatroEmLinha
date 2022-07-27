#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define FOREVER while(1)
#define VERBOSE 1
#define SILENT 0
#define jogador_que_comeca 'a'
#define VAZIO 'x'
#define FORA_DO_TAB -1

/* CORES */
#define LETRA

#define RESET        "\x1b[0m"

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

#define AMARELO       "\x1b[43m" " " RESET
#define amarelo(TXT)  "\x1b[43m" TXT RESET
#endif

#define DESTAQUE(TXT) "\x1b[47m" TXT RESET

/* Números */

#define NUM_CR_LIN 29 +1

#define NUM_LIN 6
#define NUM_COL 7

#define ERRO_LEITURA  printf("Ocorreu um erro de leitura. Tente novamente!\n"); exit(1);
#define ERRO_ALOCACAO printf("Ocorreu um erro ao alocar memória. Tente novamente!\n"); exit(1);

/* Tipos */
typedef int bool;

/* Protótipos */
/* ---------- */

/* interface.c */
void printtab(char tab[NUM_LIN][NUM_COL]);
void print_banner(void);
char *jogador_to_txt (char jogador);
void cls(void);
void print_menu(void);
void regras_do_jogo(void);


/* tabuleiro.c */
void preenche_tab(char tab[NUM_LIN][NUM_COL], char elemento);
void limpa_tab(char tab[NUM_LIN][NUM_COL]);

/* _execucao.c */
void waitFor (unsigned int segundos);
int verifica_seq_horizontal(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador); /* Retorna o tamanho da sequencia horizontal do jogador a partir das coordenadas i,j */
int verifica_seq_vertical(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador);
int verifica_seq_diagonal_direita(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador);
int verifica_seq_diagonal_esquerda(char tab[NUM_LIN][NUM_COL], int i, int j, char jogador, int contador);
int ganhou(char tab[NUM_LIN][NUM_COL], char jogador); /* Retorna o bool se a cor ganhou */
int empatou(char tab[NUM_LIN][NUM_COL]);
int jogada_eh_legal(char tab[NUM_LIN][NUM_COL], char jogador, int i, int j);
int _jogar_CvC(char tab[NUM_LIN][NUM_COL], char jogador, int dificuldade);
int _jogar_PvP(char tab[NUM_LIN][NUM_COL], char jogador);
int _jogar_PvC(char tab[NUM_LIN][NUM_COL], char jogador, int dificuldade, bool cerumano_inicia);

/* execucao.c */
void alterna_jogador(char *jogador);
int inserir_disco(char tab[NUM_LIN][NUM_COL], int coluna, char jogador, bool verbose);

/* jogadas.c */
void copia_tab(char tab[NUM_LIN][NUM_COL], char tab_copia[NUM_LIN][NUM_COL]);
int coluna_de_jogada_ganhadora(char tab[NUM_LIN][NUM_COL], char jogador);
int jogada_aleatoria(char tab[NUM_LIN][NUM_COL], char jogador);
int jogada_razoavel(char tab[NUM_LIN][NUM_COL], char jogador);
int jogada_player(char tab[NUM_LIN][NUM_COL], char jogador);

/* utils.c */
void input_flush();
int get_int(int min, int max, char * prompt);
long get_long(long min, long max, char * prompt);
char *get_string(int length, char * prompt);
char get_char(char * prompt);