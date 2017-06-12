#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "patternrec.h"

int main (int argc, char *argv[])
{
    // Receber parametros da linha de comando:
    if (argc <= 2)
    {
        printf("Especificar o nome dos arquivos que contem o dataset de treinamento e de verificacao.\n");
        return 0;
    }

    // Variavel para armazenar a quantidade de classes:
    int k;

    // Obtem a matriz do dataset de treinamento:
    Matrix treinamento = prParseDataset(argv[1], &k);

    // Obtem a matriz do dataset de verificacao:
    Matrix verificacao = prParseDataset(argv[2], &k);

    // Se houver erro durante o parsing:
    if((treinamento == NULL) || (verificacao == NULL))
        return 0;

    // Se treinamento e verificacao forem incompativeis:
    if(matNcolunas(treinamento) != matNcolunas(verificacao))
        return 0;

    // Cria vetores media:
    Matrix *medias = prVetoresMedia(treinamento, k);

    // Obtem a covariancia e sua inversa:
    Matrix cov = matCovariancia(treinamento);
    Matrix covInv = matInversa(cov);

    // Classificacao de cada tupla:
    int i;
    int hits = 0;

    for(i = 0; i < matNlinhas(verificacao); i++)
    {
        // Obtem a classe mais provavel para a tupla atual (verificacao[i]):
        int classProv = prClasseProvavel(covInv, medias, matReferenciaLinha(verificacao, i), k);

        // Compara a classe encontrada com a classe real:
        if(classProv == matPega(verificacao, i, matNcolunas(verificacao)))
            hits++; // Se acertar, incremente o contador.
    }

    // Saida de dados no console:
    prImprimeResultados(treinamento, verificacao, cov, medias, k, hits, argv[1], argv[2]);

    // Libera as matrizes utilizadas:
    matLibera(treinamento);
    matLibera(verificacao);
    matLiberaNmatrizes(medias, k);
    matLibera(cov);
    matLibera(covInv);
	
    return 0;
}