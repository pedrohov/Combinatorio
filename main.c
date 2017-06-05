#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char const *argv[])
{
  /*ponteiro para os arquivos de entrada*/
  // FILE *datasetTrainning = fopen(argv[1],"r");
  // FILE *datasetComparison = fopen(argv[2],"r");

  // Receber parametros da linha de comando:
	if (argc <= 2)
	{
		printf("Especificar o nome dos arquivos que contem o dataset de treinamento e de verificacao.\n");
		return 0;
	}

	// Variavel para armazenar a quantidade de classes:
	int k;

	// Vetor de matrizes: [0] = Matriz do dataset. [1..n] = Vetores media.
	Matrix *data;

	// Obtem a matriz 'data' e os vetores media (matrix(n, 1)):
	data = matParseDataset(argv[1], &k);

	// Mostra a matriz do dataset:
	matImprime(data[0]);

	// Mostra todos os vetores media:
	printf("Vetores media (k = %d):\n", k);
	int i;
	for(i = 1; i <= k; i++)
	{
		printf("Classe %d:\n", i);
		matImprime(data[i]);
	}

	// Libera a matriz data[0] e todos os vetores media:
	for(i = 0; i <= k; i++)
		matLibera(data[i]);

	return 0;

  /*liberacao dos arquivos de entrada*/
  // fclose(datasetTrainning);
  // fclose(datasetComparison);

  return 0;
}
