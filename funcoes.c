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

void validaPos(int **mtz)
{
	char ver;
	
	for (i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			//
		}
	}
}

int typeToInt(char type)
{
	switch (type)
	{
		case '3Az' :
			return 1; 
			break;
		case '2Az' : 
			return 2;
			break;
		case '1Az' :
			return 3;
			break;
		case '2Vm' :
			return 4;
			break;
		case '1Vm' :
			return 5;
			break;
		case '3Am' :
			return 6;
			break;
		case '1Am' :
			return 7;
			break;
		case '2Vd' :
			return 8;
			break;
		case '3Vd' :
			return 9;
			break;
	}
}

void criaMatriz()
{
	int i;
	bomb **mtz; 
	mtz = malloc (TAM_MATX * sizeof (bomb *));
	for(i = 0; i <= TAM_MATX; i++)
	{
		mtz[i] = malloc (TAM_MATX * sizeof (bomb));
		mtz[i] = 0;
	}
}

void attMatriz(int lin, int col, int type, int **mtz)
{
	int i, j;

	for (i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			if(mtz[i][j] == 0)
				mtz[i][j] = type;
		}
	}
}

void readFile()
{
	FILE *arq;
	int pos[4], tam, i, j, aux, serie = 0;
	char type[3];
	bomb B;

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
				verificando a orientação da bomba, o tipo e convertendo para int o type recebido
				atualizando a matriz a ser verificada
				*/
				
				B.type = typeToInt(type);
				B.nSerie = serie;
				if(pos[0] == pos[2]) //horizontal
				{
					aux = pos[1];
					while(aux <= pos[3])
					{
						attMatriz(pos[0], aux, B.type);
						aux++;
					}
				}else //vertical
				{
					aux = pos[0];
					while(aux <= pos[2])
					{
						attMatriz(aux, pos[1], B.type);
						aux++;
					}
				}
				serie++;
			}
		}
	}
	fclose(arq);
}
