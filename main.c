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
	getrusage(RUSAGE_SELF,&r_usage);
	//código a ser testado

	// Iniciando o programa
	// Os argumentos colocados na função readFile são "configuração" e "composição" do kit
	readFile(argv[1], argv[2]);

	gettimeofday(&fim, NULL);
	getrusage(RUSAGE_SELF,&r_usage);
	//tempo em ms para execução do cód
	double t = (fim.tv_usec - comeco.tv_usec) / 100000.0;

	printf("Tempo de execucao: %.7f s\n", t);
	printf("Memoria usada: %ld kilobytes\n",r_usage.ru_maxrss);
	return 0;
}
