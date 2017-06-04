#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

/* Tipo:*/
typedef struct Tmatrix *Matrix;


/* Sub-rotinas:*/
/* Cria uma matriz m[lin][col].*/
Matrix 	matCria (int lin, int col);
/* Retorna uma copia profunda da matriz 'mat'.*/
Matrix 	matCopia (Matrix mat);
/* Retorna a matriz oposta de 'mat'.*/
Matrix 	matOposta (Matrix mat);
/* Retorna a soma das matrizes ou NULL (impossivel somar).*/
Matrix 	matSoma (Matrix mat1, Matrix mat2);
/* Retorna a subtracao de 'mat1' - 'mat2' ou NULL (impossivel subtrair).*/
Matrix 	matSubtrai (Matrix mat1, Matrix mat2);
/* Retorna o produto matricial de 'mat1' (x) 'mat2' ou NULL (impossivel multiplicar).*/
Matrix 	matProdutoMatricial (Matrix mat1, Matrix mat2);
/* Modifica a matriz 'upper' em sua triangular superior. Retorna a triangular inferior.*/
Matrix 	matDecomposicaoLU(Matrix upper);
/* Realiza a decomposicao LU com pivoteamento.*/
Matrix 	matDecomposicaoPivotLU(Matrix upper, double *b, int n);
/* Retorna uma matriz (1 x n) com a solucao do sistema (mat, b).*/
Matrix 	matSolucaoPivotLU(Matrix mat, double *b, int n);
/* Retorna uma matriz (1 x n) com a solucao do sistema (lower, b)*/
/* (Usado por SolucaoPivotLU).*/
Matrix 	matSubstSucessiva(Matrix lower, double *b, int n);
/* Retorna a solucao de upper(n, n) por y(1, n) (Usado por SolucaoPivotLU).*/
Matrix 	matSubstRetroativa(Matrix upper, Matrix y);
/* Retorna a matriz inversa de 'mat' ou NULL (impossivel calcular).*/
Matrix  matInversa(Matrix mat);
/* Retorna o determinante de uma matriz quadrada.*/
double 	matDeterminante (Matrix mat);
/* Realiza a triangulacao superior da matriz por Eliminacao de Gauss,*/
/* retorna seu determinante.*/
double 	matSuperior (Matrix mat);
/* Realiza a triangulacao por Eliminacao de Gauss com pivoteamento,*/
/* retorna seu determinante.*/
double 	matSuperiorPivot (Matrix mat);
/* Retorna o valor na posicao m(lin, col).*/
double 	matPega (Matrix mat, int lin, int col);
/* Retorna o produto escalar entre*/
/* mat1(m, 1) x mat2(1, n) ou -1 (impossivel multiplicar).*/
double	matProdutoEscalar (Matrix mat1, Matrix mat2);
/* Retorna 1 se as matrizes forem iguais ou 0 se diferentes.*/
int 	matIgual (Matrix mat1, Matrix mat2);
/* Procura pelo maior elemento igual ou abaixo da linha 'lin' na coluna 'col'.*/
int 	matLocalizaPivo (Matrix mat , int lin, int col);
/* Libera a memoria utilizada pela matriz 'mat'.*/
void	matLibera (Matrix mat);
/* Imprime a matriz no console.*/
void 	matImprime (Matrix mat);
/* Altera o valor da posicao mat[lin][col].*/
void 	matColoca (Matrix mat, int lin, int col, double valor);
/* Salva a matriz em um arquivo.*/
void 	matSalva (Matrix mat, char nomeArquivo[]);
/* Troca as linhas 'lin1' e 'lin2' da matriz 'mat'.*/
void 	matTrocaLinhas (Matrix mat, int lin1, int lin2);
/* Multiplica a matriz 'mat' por um numero real.*/
void	matMultiplicaEscalar(Matrix mat, double escalar);
/* Multiplica a linha 'lin' por um numero real.*/
void 	matMultiplicaLinhaEscalar (Matrix mat, int lin, double escalar);
/* Faz [linAlvo - (lin * escalar)] para todos os elementos da linha
 *(auxilia LU).*/
void 	matTransformaLinha (Matrix mat , int linAlvo, int lin, double escalar);

#endif // MATRIX_H_INCLUDED
