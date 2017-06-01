#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

// Estrutura:
struct Tmatrix{
	int lin;
	int col;
	float **p;
} matrix;

// Tipo:
typedef struct Tmatrix *MATRIX;

// Sub-rotinas:
MATRIX MATaloca (int lin, int col);
MATRIX MATcopia (MATRIX mat);
MATRIX MATcarrega (char nomeArquivo[]);
MATRIX MATidentidade (int n);
MATRIX MATtransposta (MATRIX mat);
MATRIX MAToposta (MATRIX mat);
MATRIX MATsoma (MATRIX mat1, MATRIX mat2); // Retorna soma das matrizes ou NULL (n possivel).
MATRIX MATsubtrai (MATRIX mat1, MATRIX mat2); // Retorna subtração das matrizes ou NULL.
MATRIX MATmultiplica (MATRIX mat1, MATRIX mat2); // Retorna multiplicação das matrizes ou NULL.
float MATget (MATRIX mat, int lin, int col); // Retorna valor.
float MATdeterminante (MATRIX mat); // Retorna determinante se a matriz for quadrada.
float MATtriangulacao (MATRIX mat); // Triangula a matriz e retorna seu determinante.
int MATigual (MATRIX mat1, MATRIX mat2); // 1 -> iguais. 0 -> diferentes.
int MATlocalizaPivo (MATRIX mat , int lin, int col);
void MATdesaloca (MATRIX mat);
void MATimprime (MATRIX mat);
void MATput (MATRIX mat, int lin, int col, float valor);
void MATsalva (MATRIX mat, char nomeArquivo[]);
void MATtrocaLinhas (MATRIX mat, int lin1, int lin2);
void MATmultLinhaEscalar (MATRIX mat, int lin, float escalar);
void MATtransformaLinha (MATRIX mat , int linAlvo, int lin, float escalar);

#endif // MATRIX_H_INCLUDED