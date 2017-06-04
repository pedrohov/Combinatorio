#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char const *argv[])
{
  /*ponteiro para os arquivos de entrada*/
  FILE *datasetTrainning = fopen(argv[1],"r");
  FILE *datasetComparison = fopen(argv[2],"r");

  /*liberacao dos arquivos de entrada*/
  fclose(datasetTrainning);
  fclose(datasetComparison);

  return 0;
}
