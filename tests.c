#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void test_GenerateRandomValues(MATRIX mat, int min, int max)
{
  int i,j;
  int value;

  for (i = 0; i < mat->lin; i++)
  {
    for (j = 0; j < mat->col; j++)
    {

      value = rand()%(max+1);

      if(value < min)
        value = min + value;

      mat->p[i][j] = value;
    }
  }
}

void test_WriteMatrixIn_R_format(MATRIX mat, char *arqName)
{

  int i,j;
  FILE *fileOut;
  fileOut = fopen(arqName,"w");

  if(fileOut!=NULL)
  {
    fprintf(fileOut, "%s<-matrix(c(",arqName);

    for (i = 0; i < mat->lin; i++)
    {
      for (j = 0; j < mat->col; j++)
      {
        if ((mat->lin-1==i)&&(mat->col-1==j));
        else
          fprintf(fileOut,"%f,",mat->p[i][j]);
      }
    }
    fprintf(fileOut, "%f),%i,%i,byrow=TRUE)",mat->p[mat->lin-1][mat->col-1],mat->lin,mat->col);

    fclose(fileOut);
  }

}
