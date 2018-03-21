#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#define TAM_MATX 6

//função auxiliar para o qsort da STDLIB.H
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void freeMatriz(bomb **m)
{
	// liberação da memória alocada pela matriz
	int i;
	for(i = 0; i < TAM_MATX; i++)
	{
		free(m[i]);
	}
	free(m);
}

int verComp(int *vetInt, char *nomeArq)
{
	FILE *arq;
	int *vetArq, i = 0, j = 1;
	int qtd, nr, cont = 0;
	char tipo[3];

	printf("TESTE\n");
	if((arq = fopen(nomeArq, "r")) == NULL)
		printf("ERRO\n");
	else
	{
		//escaneando quantas posições devem ser alocadas no vetor
		while(!feof(arq))
		{
			fscanf(arq, "%d %s", &qtd, tipo);
			i += qtd;
		}
		vetArq = (int *)malloc(i * sizeof(int));
		i = 0;
		// alocando as posições no vetor
		while(!feof(arq))
		{
			//recebendo cada elemento da composição, transformando-o em um INT
			//em seguida preenchendo o vetor
			fscanf(arq, "%d %s", &qtd, tipo);
			nr = typeToInt(tipo);
			while(j <= qtd)
			{
				vetArq[i] = nr;
				i++;
			}
			j = 1;
		}
		//comparando os dois vetores
		//veerifica se o tamanho dos dois vetores são diferentes, caso sejam, algum deles possui mais elementos que o outro	
		if(sizeof(vetInt)/sizeof(vetInt[0]) != sizeof(vetArq)/sizeof(vetArq[0]))
			return 1;
		else
		{
			//ordenando os vetores para facilitar a comparação
			qsort(vetArq, sizeof(vetArq), sizeof(int), cmpfunc);
			qsort(vetInt, sizeof(vetInt), sizeof(int), cmpfunc);
			for (i = 0; i < sizeof(vetInt); i++)
			{
				if(vetInt[i] != vetArq[i])
					cont++;
			}
			if (cont > 0)
				return 1;
			else
				return 0;
		}
	}
	fclose(arq);
	free(vetArq);
}

int validoPos(bomb **m)
{
	int c = 0, boom = 0, l=0, i, j, k;
	
	for (i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			if (i == 5)
			{
				for(k = 0; k < TAM_MATX; k++)
				{
					if((m[5][k].nSerie != m[5][k+1].nSerie) && (m[5][k].type == m[5][k+1].type))
						boom++;
				}
				if(boom > 0)
					return 1;
				else
					return 0;
			}
			if ((m[i][j].nSerie != m[i+1][j].nSerie) && (m[i][j].type == m[i+1][j].type))
				boom++;
			if ((m[i][j].nSerie != m[i][j+1].nSerie) && (m[i][j].type == m[i][j+1].type))
				boom++;
		}
	}
	if(boom > 0)
		return 1;
	else
		return 0;
}

int typeToInt(char *type)
{
	if(strcmp(type, "3Az") == 0)
		return 1;
	if(strcmp(type, "2Az") == 0)
		return 2;
	if(strcmp(type, "1Az") == 0)
		return 3;
	if(strcmp(type, "3Vm") == 0)
		return 4;
	if(strcmp(type, "2Vm") == 0)
		return 5;
	if(strcmp(type, "1Vm") == 0)
		return 6;
	if(strcmp(type, "3Am") == 0)
		return 7;
	if(strcmp(type, "2Am") == 0)
		return 8;
	if(strcmp(type, "1Am") == 0)
		return 9;
	if(strcmp(type, "3Vd") == 0)
		return 10;
	if(strcmp(type, "2Vd") == 0)
		return 11;
	if(strcmp(type, "1Vd") == 0)
		return 12;
}

bomb **criaMatriz()
{
	int i, j;

	bomb **m;
	m = (bomb **)malloc(TAM_MATX * sizeof(bomb *));
	for (i = 0; i < TAM_MATX; i++)
	{
		m[i] = (bomb *) malloc(TAM_MATX * sizeof(bomb));
	}
	return m;
}

void zeraMatriz(bomb **m)
{
	int i, j;
	for(i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			m[i][j].type = 0;
		}
	}
}

void attMatriz(int linha, int coluna, bomb B, bomb **m)
{
	int i, j;
	for(i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			if (linha == i && coluna == j && m[i][j].type == 0)
			{
				m[i][j] = B;
			}
		}
	}
}

void readFileAux(char *buffer, int *pos, int *nr)
{
	int i;
	char type[3], c;
	pos[0] = buffer[0] - 49;
	pos[1] = buffer[2] - 49;
	pos[2] = buffer[4] - 49;
	pos[3] = buffer[6] - 49;
	for (i = 8; i < 11; i++)
	{
		c = buffer[i];
		type[i - 8] = c;
	}
	*nr = typeToInt(type);
}

void readFile(char *arquivo, char *arquivo2)
{
	FILE *arq, *arq2;
	char buffer[14], saida[14];
	int tipo, i, aux, qtdConf = 0, serie = 0, pos[4], val, val1, val2, cont = 1;
	int *vet = (int *)malloc(sizeof(int));
	bomb B;
	bomb **m = criaMatriz();

	arq2 = fopen("saidaTP1.txt", "a");
	if(!(arq = fopen(arquivo, "r")))
		printf("ERRO\n");
	else
	{
		while(!feof(arq))
		{
			fgets(buffer, sizeof(buffer), arq);
			if(strncmp(buffer, "configuracao", 12) == 0)
			{
				if (qtdConf != 0)
				{
					// testar validode
					val1 = validoPos(&*m);
					val2 = verComp(vet, arquivo2);
					val = val1 + val2;
					if (val > 0)
						fprintf(arq2,"%s nao-valido\n", saida);
					else
						fprintf(arq2,"%s valido\n", saida);
				}
				zeraMatriz(&*m);
				qtdConf++;
				strcpy(saida, buffer);
			}else
			{
				readFileAux(buffer, pos, &tipo);
				B.type = tipo;
				B.nSerie = serie;

				if(pos[0] == pos[2])
				{
					aux = pos[1];
					while(aux <= pos[3])
					{
						attMatriz(pos[0], aux, B, &*m);
						aux++;
					}
				}else
				{
					aux = pos[0];
					while(aux <= pos[2])
					{
						attMatriz(aux, pos[1], B, &*m);
						aux++;
					}
				}
			}
			serie++;
		}
		val = validoPos(&*m);
		//showMatriz(&*m);
		if (val > 0)
			fprintf(arq2,"%s nao-valido\n", saida);
		else
			fprintf(arq2,"%s valido\n", saida);
	}
	freeMatriz(&*m);
	fclose(arq);
	fclose(arq2);
}
