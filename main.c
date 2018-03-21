#include <sys/resource.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "funcoes.h"
#define TAM_MATX 6

int main(int argc, char **argv)
{
	struct rusage r_usage;
	struct timeval comeco, fim;
	gettimeofday(&comeco, NULL);
	//código a ser testado

	readFile(argv[1], argv[2]);
	getrusage(RUSAGE_SELF,&r_usage);

	gettimeofday(&fim, NULL);
	getrusage(RUSAGE_SELF,&r_usage);
	//tempo em ms para execução do cód
	double t = (fim.tv_usec - comeco.tv_usec) / 100000.0;

	printf("\n%.7f segundos\n", t);
	printf("\nMemoria usada = %ld\n",r_usage.ru_maxrss);
	return 0;
}
