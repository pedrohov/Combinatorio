#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "tests.h"

int main(int argc, char const *argv[])
{
  /*ponteiro para os arquivos de entrada*/
  // FILE *datasetTrainning = fopen(argv[1],"r");
  // FILE *datasetComparison = fopen(argv[2],"r");

  MATRIX A = (MATRIX) MATaloca(1,2);
  MATRIX B = (MATRIX) MATaloca(2,1);

  test_GenerateRandomValues(A,2,20);
  test_GenerateRandomValues(B,50,200);

  MATRIX result = (MATRIX) MATprodutoMatricial(A,B);

  test_WriteMatrixIn_R_format(A,"Amatriz.r");
  test_WriteMatrixIn_R_format(B,"Bmatriz.r");

  printf("%d\n",MATprodutoEscalar(A,B));

  /*liberacao dos arquivos de entrada*/
  // fclose(datasetTrainning);
  // fclose(datasetComparison);

  return 0;
}
