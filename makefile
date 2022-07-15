CC=gcc
CFLAGS=-Wall -ansi -pedantic
OUT=QuatroEmLinha


$(OUT): quatroemlinha.c
	$(CC) -o $(OUT) quatroemlinha.c $(CFLAGS) 
