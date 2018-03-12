#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

struct kitBoom{
	int type, nSerie;
};
typedef struct kitBoom bomb;
char typeToChar(char );
void criaMatriz();
void attMatriz(int , int , char );
void readFile();

#endif

/*
gcc -c funcoes.c && gcc -c main.c && gcc funcoes.o main.o -o teste
*/
