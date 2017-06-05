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

  	Matrix data = (Matrix) matParseDataset(argv[1]);
  	matImprime(data);
  	matLibera(data);

  /*liberacao dos arquivos de entrada*/
  // fclose(datasetTrainning);
  // fclose(datasetComparison);

  return 0;
}
