CC=gcc
DEPS=quatroemlinha.h
CFLAGS=-Wall -ansi -pedantic
OUT=QuatroEmLinha

# Compilando
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

# Limpeza
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(OUT)
