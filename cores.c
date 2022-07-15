#include <stdio.h>

#define VERMELHO "\x1b[31m"
#define AMARELO  "\x1b[43m"
#define RESET    "\x1b[0m"

#define VERDE    "\x1b[32m"
#define AZUL     "\x1b[34m"

int main () 
{
    printf(VERMELHO     "Texto em vermelho"     RESET "\n");
    printf(VERDE   "Texto em verde"   RESET "\n");
    printf(AZUL    "Texto em azul"    RESET "\n");

    return 0;
}
