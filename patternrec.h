#ifndef PATTERN_RECOGNITION_H_INCLUDED
#define PATTERN_RECOGNITION_H_INCLUDED

#include "matrix.h"

// Pattern Recognition:
Matrix  prParseDataset (const char* local, int *k);            // Obtem a matriz do dataset em 'local' e o vetor media de cada classe.
Matrix  prVetMediaClasse (Matrix mat, int classe);             // Retorna uma matriz m(n, 1) com a media da classe para cada variavel.     
Matrix* prVetoresMedia (Matrix mat, int nClasses);             // Retorna um vetor de matriz com o vetor media de cada classe.
double  prMaxLikelihood (Matrix covInv, Matrix classe1, Matrix classe2, double* entrada);   // Determina o maximum likelihood ratio teste r ij, (i = classe1, j = classe2).
int     prClasseProvavel (Matrix covInv, Matrix *medias, double* tupla, int nClasses);      // Determina a classe mais provavel para a tupla.
void 	prImprimeResultados (Matrix treinamento, Matrix verificacao, Matrix covariancia, Matrix* medias, int k, int hits, const char* input, const char* output);

#endif // PATTERN_RECOGNITION_H_INCLUDED