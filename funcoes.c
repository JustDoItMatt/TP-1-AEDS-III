/*
3Az = 1
2Az = 2
1Az = 3

3Vm = 4
2Vm = 5
1Vm = 6

3Am = 7
2Am = 8
1Am = 9

3Vd = 10
2Vd = 11
1Vd = 12
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#define TAM_MATX 6

void validaPos(bomb **mtz,int explo)
{
	int i,j;
	for (i=0;i<TAM_MATX;i++){
		for (j=0;j<TAM_MATX;j++){
			if ((matriz[i][j]->type==matriz[i][j+1]->type) && (matriz[i][j]->nserie!=matriz[i][j+1]->nserie)){
				explo++;
			}
			if ((matriz[i][j]->type==matriz[i][j-1]->type) && (matriz[i][j]->nserie!=matriz[i][j+1]->nserie)){
				explo++;
			}
			if ((matriz[i+1][j]->type==matriz[i][j]->type)&&(matriz[i+1][j]->nserie!=matriz[i][j]->nserie)){
				explo++;
			}
			if ((matriz[i-1][j]->type==matriz[i][j]->type)&&(matriz[i-1][j]->nserie!=matriz[i][j]->nserie)){
				explo++;
			}
		}
	}
}
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
	bomb **mtz;

	mtz = (bomb **) malloc (TAM_MATX * sizeof(bomb *));
	for (i = 0; i < TAM_MATX; i++)
	{
		mtz[i] = (bomb *) malloc(TAM_MATX * sizeof(bomb));
	}
}

void attMatriz(int lin, int col, bomb B, bomb **mtz)
{
	int i, j;

	for (i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			if((lin == i && col == j) && mtz[i][j].type == 0)
				mtz[i][j] = B;
		}
	}
}

void readFile()
{
	FILE *arq;
	int pos[4], tam, i, j, aux, serie = 0;
	char charType[3];
	bomb B, **mtz = criaMatriz();
	
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
				fscanf(arq, "%s", charType);
				
				/*
				verificando a orientação da bomba, o tipo e convertendo para int o type recebido
				atualizando a matriz a ser verificada
				*/
				
				B.type = typeToInt(charType);
				B.nSerie = serie;
				if(pos[0] == pos[2]) //horizontal
				{
					aux = pos[1];
					while(aux <= pos[3])
					{
						attMatriz(pos[0], aux, B, mtz);
						aux++;
					}
				}else //vertical
				{
					aux = pos[0];
					while(aux <= pos[2])
					{
						attMatriz(aux, pos[1], B, mtz);
						aux++;
					}
				}
				serie++;
			}
			//testar a validade da configuração

		}
	}
	fclose(arq);
}
