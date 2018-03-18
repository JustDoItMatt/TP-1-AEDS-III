#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#define TAM_MATX 6

int validaPos(bomb **m)
{
	int c = 0, boom = 0, i, j;
	
	for (i = 0; i < TAM_MATX; i++){
		for (j = 0; j < TAM_MATX; j++){
			if (m[i][j].nSerie != m[i+1][j].nSerie || m[i][j].nSerie != m[i][j+1].nSerie)
			{
				printf("1 \n");
			}
		}
	}
	printf("%d\n", c);
	if(boom > 0)
		return 0;
	else
		return 1;
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

	printf("Alocado com sucesso\n");
	return m;
}

void showMtz(bomb **m)
{
	int i, j;
	for(i = 0; i < TAM_MATX; i++)
	{
		for (j = 0; j < TAM_MATX; j++)
		{
			printf(" %d ", m[i][j].type);
		}
		printf("\n");
	}
}

void attMatriz(int linha, int coluna, bomb B, bomb **m)
{
	int i, j;
	//printf("l: %d, c: %d\n", linha, coluna);
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

void readFile(char *arquivo)
{
	FILE *arq;
	int pos[4], val, i, j, aux, serie = 0;
	char charType[3], buffer[] = "configuracao", key[13];
	bomb B;
	bomb **m = criaMatriz();
	
	if((arq = fopen(arquivo, "r")) == NULL)
		printf("ERRO\n");
	else
	{
		while(fgets(key, sizeof(key), arq) != NULL)
		{
			if(strncmp(key, buffer,12) == 0)
				continue;
			else
			{
				for (i = 0; i < 4; i++)
				{
					fscanf(arq, "%d", &pos[i]);
					pos[i] -= 1;
				}
				//printf("\n");
				fscanf(arq, "%s", charType);


				B.type = typeToInt(charType);
				B.nSerie = serie;

				/*
				pos[0] e pos[2] = linha
				pos[1] e pos[3] = coluna
				*/
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
		//testar a validade da configuração
		val = validaPos(&*m);
		if(val != 0)
			printf("\n%s nao e valida.", key);
			//imprimir resultado no arquivo
		else
			printf("\n%s  e valida.", key);
	}
}

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
