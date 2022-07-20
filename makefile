CC=gcc
DEPS=quatroemlinha.h
CFLAGS=-Wall -ansi -pedantic
OUT=QuatroEmLinha

# $(OUT): quatroemlinha.c
# 	$(CC) -o $(OUT) quatroemlinha.c $(CFLAGS) 
#
all: _execucao.o execucao.o interface.o tabuleiro.o
	$(CC) -o $(OUT) main.c _execucao.o execucao.o interface.o tabuleiro.o $(CFLAGS) 

_execucao.o: 
	$(CC) -c _execucao.c $(CFLAGS)

execucao.o:
	$(CC) -c execucao.c $(CFLAGS)

interface.o: 
	$(CC) -c interface.c $(CFLAGS)

tabuleiro.o:
	$(CC) -c tabuleiro.c $(CFLAGS)
