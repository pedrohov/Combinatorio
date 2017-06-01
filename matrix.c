#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

MATRIX MATaloca(int lin, int col)
{
    int i, j;
    float  **linhas=(float**)malloc(sizeof(float*)*lin);
    MATRIX aux=(MATRIX)malloc(sizeof(struct Tmatrix));
    aux->col=col;
    aux->lin=lin;
    aux->p=linhas;
    for(i=0; i<lin; i++)
    {
        float *colunas=(float*)malloc(sizeof(float)*col);
        linhas[i]=colunas;
    }
    for(i=0; i<lin; i++)
    {
        for(j=0; j<col; j++)
        {
            aux->p[i][j]=0;
        }
    }
    return aux;
}

void MATdesaloca(MATRIX mat)
{
    int i;
    for(i=0; i<mat->lin; i++)
    {
        free(mat->p[i]);
    }
    free(mat->p);
    free(mat);
    return;
}

void MATimprime(MATRIX mat)
{
    int i,j;
    for(i=0;i<mat->lin;i++)
    {
        for(j=0;j<mat->col;j++)
        {
            if(mat->p[i][j]==-0)
                mat->p[i][j]=fabs(mat->p[i][j]);
            printf("%.2f\t", mat->p[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

MATRIX MATcopia(MATRIX mat)
{
    MATRIX aux=MATaloca(mat->lin, mat->col);
    int i, j;
    aux->lin=mat->lin;
    aux->col=mat->col;
    for(i=0; i<mat->lin; i++)
        for(j=0; j<mat->col; j++)
            aux->p[i][j]=mat->p[i][j];
    return aux;
}

void MATput(MATRIX mat, int lin, int col, float valor)
{
    mat->p[lin][col]=valor;
    return;
}

float MATget(MATRIX mat, int lin, int col)
{
    float aux;
    aux=mat->p[lin][col];
    return aux;
}

void MATsalva(MATRIX mat, char nomeArquivo[])
{
    int i, j;
    FILE *psaida=fopen(nomeArquivo,"w");
    if(psaida==NULL)
    {
        printf("BUG: MATsalva! (Espaço em disco insuficiente.)\n");
        return;
    }
    fprintf(psaida, "%d\t%d\n", mat->lin, mat->col);
    for(i=0; i<mat->lin; i++)
    {
        for(j=0; j<mat->col; j++)
            fprintf(psaida,"%f\t", mat->p[i][j]);
        fprintf(psaida, "\n");
    }
    fclose(psaida);
    return;
}

MATRIX MATcarrega(char nomeArquivo[])
{
    int i, j;
    FILE *parq;
    parq=fopen(nomeArquivo,"r");
    if(parq==NULL)
        return NULL;

    // Determinar quantidade de números;
        fscanf(parq, "%d", &i);
        fscanf(parq, "%d", &j);

    // Cria matriz:
        MATRIX aux;
        aux=MATaloca(i, j);
        for(i=0; i<aux->lin; i++)
            for(j=0; j<aux->col; j++)
            {
                float valor;
                fscanf(parq, "%f", &valor);
                aux->p[i][j]=valor;
            }
        return aux;
}

MATRIX MATidentidade (int n)
{
    MATRIX aux=MATaloca(n,n);
    int i;
    for(i=0; i<n; i++)
        aux->p[i][i]=1;
    return aux;
}


MATRIX MATtransposta(MATRIX mat)
{
    MATRIX aux;
    int i,j;
    aux=MATaloca(mat->col,mat->lin);
    for(i=0;i<aux->lin;i++)
        for(j=0;j<aux->col;j++)
        {
            aux->p[i][j]=mat->p[j][i];
        }
    return aux;
}


MATRIX MAToposta (MATRIX mat)
{
    MATRIX aux=MATcopia(mat);
    int i, j;
    for(i=0; i<mat->lin; i++)
        for(j=0; j<mat->col; j++)
        {
            if(aux->p[i][j]!=0)
                aux->p[i][j]=-aux->p[i][j];
        }
    return aux;
}

int MATigual (MATRIX mat1, MATRIX mat2)
{
    if(mat1->lin!=mat2->lin || mat1->col!=mat2->col)
        return 0;
    int i, j;
    for(i=0; i<mat1->lin; i++)
        for(j=0; j<mat2->col; j++)
        {
            if(mat1->p[i][j]!=mat2->p[i][j])
                return 0;
        }
    return 1;
}

MATRIX MATsoma (MATRIX mat1, MATRIX mat2)
{
    if(mat1->lin!=mat2->lin || mat1->col!=mat2->col)
        return NULL;
    int i, j;
    MATRIX aux=MATaloca(mat1->lin, mat1->col);
    for(i=0; i<mat1->lin; i++)
        for(j=0; j<mat1->col; j++)
        {
            aux->p[i][j]=mat1->p[i][j]+mat2->p[i][j];
        }
    return aux;
}

MATRIX MATsubtrai (MATRIX mat1, MATRIX mat2)
{
    if(mat1->lin!=mat2->lin || mat1->col!=mat2->col)
        return NULL;
    int i, j;
    MATRIX aux=MATaloca(mat1->lin, mat1->col);
    for(i=0; i<mat1->lin; i++)
        for(j=0; j<mat1->col; j++)
        {
            aux->p[i][j]=mat1->p[i][j]-mat2->p[i][j];
        }
    return aux;
}

MATRIX MATmultiplica (MATRIX mat1, MATRIX mat2)
{
    if(mat1->col!=mat2->lin)
        return NULL;
    MATRIX aux=MATaloca(mat1->lin, mat2->col);
    int i=0, j, k=0, l=0;
    do
    {
        do
        {
            for(j=0; j<mat1->col; j++)
            {
                aux->p[k][l]=(mat1->p[i][j]*mat2->p[j][l])+aux->p[k][l];
            }
            l++;
        } while(l<mat2->col);
        l=0;
        i++;
        k++;
    } while(i<mat1->lin);
    return aux;
}

void MATtrocaLinhas (MATRIX mat, int lin1, int lin2)
{
    float *p;
    p=mat->p[lin1];
    mat->p[lin1]=mat->p[lin2];
    mat->p[lin2]=p;
    return;
}

void MATmultLinhaEscalar (MATRIX mat, int lin, float escalar)
{
    int i;
    for(i=0; i<mat->col; i++)
    {
        if(mat->p[lin][i]!=0)
        {
            mat->p[lin][i]=mat->p[lin][i]*escalar;
        }
    }
    return;
}

void MATtransformaLinha (MATRIX mat , int linAlvo, int lin, float escalar)
{
    int i;
    for(i=0; i<mat->col; i++)
        mat->p[linAlvo][i]=mat->p[linAlvo][i]-(mat->p[lin][i]*escalar);
    return;
}

int MATlocalizaPivo (MATRIX mat , int lin, int col)
{
    int i,j=lin-1;
    float aux=0;
    for(i=col; i<mat->lin; i++)
    {
        if((fabs(mat->p[i][col])>=aux) && i!=lin)
        {
            aux=fabs(mat->p[i][col]);
            j=i;
        }
    }
    return j;
}

float MATdeterminante (MATRIX mat)
{
    if(mat->lin!=mat->col)
        return 0;
    MATRIX aux;
    float det;
    aux=MATcopia(mat);
    det=MATtriangulacao(aux);
    MATdesaloca(aux);
    return det;
}

float MATtriangulacao (MATRIX mat)
{
    /*if(mat->lin!=mat->col)
        return 0;*/

    int i, j=0, k=0;
    float det=1;

    for(j=0; j<mat->col; j++)
    {
        for(i=j+1; i<mat->lin; i++)
        {
            if(mat->p[i][j]!=0)
            {
                if(mat->p[j][j]==0)
                {
                    MATtrocaLinhas(mat, i, j);
                    det=det*(-1);
                }
                else
                {
                    k=MATlocalizaPivo(mat, i, j);
                    MATtransformaLinha(mat, i, k, (float)mat->p[i][j]/mat->p[k][j]);
                    mat->p[i][j]=0;
                }
            }
        }
    }
    for(i=0; i<mat->lin; i++)
        det=det*(mat->p[i][i]);
    return det;
}