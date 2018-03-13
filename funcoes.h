#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

struct kitBoom{
	int type, nSerie;
};
typedef struct kitBoom bomb;
void validaPos(int **);
int typeToInt(char *);
bomb **criaMatriz();
void attMatriz(int , int , bomb , bomb **);
void readFile();

#endif

/*
gcc -c funcoes.c && gcc -c main.c && gcc funcoes.o main.o -o teste
*/
