#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

struct kitBoom{
	int type, nSerie;
};
typedef struct kitBoom bomb;

void freeMatriz(bomb **);

int verComp(int *, char *);

int validoPos(bomb **);

int typeToInt(char *);

bomb **criaMatriz();

void zeraMatriz(bomb **);

void attMatriz(int , int , bomb , bomb **);

void readFileAux(char *, int *, int *);

void readFile(char *, char *);

#endif

/*
gcc -c funcoes.c && gcc -c main.c && gcc funcoes.o main.o -o teste
*/
