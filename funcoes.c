/*
3Az = 1
2Az = 2
1Az = 3

2Vm = 4
1Vm = 5

3Am = 6
1Am = 7

2Vd = 8
3Vd = 9
*/
#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#define TAM_MATX 6

void validaPos()
{
	FILE *arq;
	arq = fopen("matriztemp.txt", "r");
	char ver;

	for (i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			fscanf(arq, "%c", &ver);
			//if()
		}
	}
	fclose(arq);
}

char typeToChar(char type)
{
	switch (type)
	{
		case '1AM' :
			return 1; 
		break;
	}
}

void criaMatriz()
{
	int i, j;
	FILE *arq;

	arq = fopen("matriztemp.txt", "r");
	for (i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			fprintf(arq, "0 ");
		}
		fprintf(arq, "\n");
	}
	fclose(arq);
}

void attMatriz(int lin, int col, char type)
{
	FILE *arq;
	int i, j;
	char tipo;

	for (i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			fscanf(arq, "%c", &tipo);
			if (strcmp(type, "0") == 0)
			{
				fprintf(arq, "%c ", type);
			}else
			{
				fprintf(arq, "%c ", tipo);
			}
		}
		fprintf(arq, "\n");
	}
}

void readFile()
{
	FILE *arq;
	int pos[4], tam, i, j, aux;
	char c, type[3];

	if((arq = fopen("configuracoes.txt", "r")) == NULL) printf("ERRO\n");
	else
	{
		char buffer[] = "configuracao", key[13];
		//fscanf(arq, "%s", key);

		while(fgets(key, sizeof(key), arq) != NULL)
		{
			if(strncmp(key, buffer, 12) == 0)
				continue;
			else
			{
				//recebendo os dados do arquivo
				for(i = 1; i < 5; i++)
				{
					fscanf(arq, "%d", &pos[i-1]);
				}
				fscanf(arq, "%s", type);
				
				/*
				verificando a orientação da bomba, o tipo e convertendo para char o type recebido
				atualizando a matriz a ser verificada
				*/
				
				c = typeToChar(type);
				if(pos[0] == pos[2]) //horizontal
				{
					aux = pos[1];
					while(aux <= pos[3])
					{
						attMatriz(pos[0], aux, c);
						aux++;
					}
				}else //vertical
				{
					aux = pos[0];
					while(aux <= pos[2])
					{
						attMatriz(aux, pos[1], c);
						aux++;
					}
				}
			}
		}
	}
	fclose(arq);
}