#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "funcoes.h"
#define TAM_MATX 6

int main(int argc, char **argv)
{
	struct timeval comeco, fim;
	gettimeofday(&comeco, NULL);
	//código a ser testado

	printf("%s\n", argv[1]);

	gettimeofday(&fim, NULL);
	//tempo em ms para execução do cód
	double t = (fim.tv_usec - comeco.tv_usec) / 100000.0;

	printf("\n%.7f segundos\n", t);
	//attMatriz();
	return 0;
}
