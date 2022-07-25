CC= gcc
CFLAGS= -Wall -ansi -pedantic
DEPS= quatroemlinha.h
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
OUT= 4el

# Compilando
all: 4el

4el: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(OUT)
