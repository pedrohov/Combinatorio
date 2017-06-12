#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix prParseDataset(const char* local, int *k)
{
    // Abre o arquivo para leitura:
    FILE *arquivo = fopen(local, "r");

    // Caso o arquivo nao for encontrado:
    if(arquivo == NULL)
    {
        printf("Arquivo '%s' nao encontrado.\n", local);
        return NULL;
    }

    Matrix data = NULL;             // Matriz com as tuplas do dataset.
    int linhas = 0, colunas = 0;    // Qtd de linhas e colunas da matriz.

    char controle;                  // Auxilia na leitura do arquivo.
    int criada = 0;                 // Detectar datasets invalidos.
    int lin = 0;                    // Linha atual de insercao.

    // Parsing do dataset:
    while(fscanf(arquivo, "%c", &controle) != EOF)
    {
        // Comentario: Pula a linha:
        if(controle == '#')
        {
            char skip = '0';
            while(skip != '\n')
                fscanf(arquivo, "%c", &skip);
        }
        // Listagem dos valores da tupla:
        else if(controle == 't')
        {
            // Impedir formato invalido:
            if(!criada)
            {
                printf("Formato incorreto.\n");
                fclose(arquivo);
                return NULL;
            }

            // Le V - 1 variaveis e a classe:
            int i;
            double valor;
            for(i = 0; i < colunas; i++)
            {
                fscanf(arquivo, "%lf", &valor);
                matColoca(data, lin, i, valor);
            }
            lin++;
        }
        // Le a quantidade de dados:
        else if(controle == 'N')
            fscanf(arquivo, "%d", &linhas);

        // Le a quantidade de variaveis:
        else if(controle == 'V')
            fscanf(arquivo, "%d", &colunas);

        // Le a quantidade de classes:
        else if(controle == 'K')
        {
            // Impedir formato invalido:
            if((linhas == 0) || (colunas == 0) || criada)
            {
                printf("Formato incorreto.\n");
                fclose(arquivo);
                return NULL;
            }

            // Le o numero de classes:
            int nClasses;
            fscanf(arquivo, "%d", &nClasses);
            *k = nClasses;  // Retorna por referecia a quantidade de classes para 'pattern.c'.

            // Cria a matriz:
            data = matCria(linhas, colunas);
            matSetNcolunas(data, colunas - 1); // Deixa a ultima coluna reservada para as classes.
            criada = 1; // Informa que a matriz foi criada (Impedir formato invalido).
        }
    }

    fclose(arquivo);
    return data;
}

Matrix prVetMediaClasse (Matrix mat, int classe)
{
    // Prerequisitos (Matriz nao nula):
    if(mat == NULL)
        return NULL;

    // Cria uma matriz (n, 1):
    Matrix media = matCria(matNcolunas(mat), 1);

    // Armazena a media de cada variavel nas linhas da matriz:
    int i, j;
    int n = 0;  // Quantidade de tuplas da classe.
    for(i = 0; i < matNlinhas(mat); i++)
    {
        int classeAtual = (int) matPega(mat, i, matNcolunas(mat));

        // Se a tupla corresponde a classe:
        if(classeAtual == classe)
        {
            for(j = 0; j < matNcolunas(mat); j++)
                matColoca(media, j, 0, matPega(media, j, 0) + matPega(mat, i, j));
                
            n++;
        }
    }

    // Divide o somatorio pela quantidade de tuplas:
    for(i = 0; i < matNlinhas(media); i++)
    {
        double valor = matPega(media, i, 0) / n;
        matColoca(media, i, 0, valor);
    }
    
    return media;
}

Matrix* prVetoresMedia (Matrix mat, int nClasses)
{
    // Prerequisitos (Matrize nao nula, numero de classes positivo):
    if((mat == NULL) || nClasses <= 0)
        return NULL;

    // Aloca memoria para todas as classes:
    Matrix *medias = (Matrix*)malloc(sizeof(Matrix) * nClasses);

    // Cria os vetores media para cada classe:
    int i;
    for(i = 0; i < nClasses; i++)
        medias[i] = prVetMediaClasse(mat, i);

    return medias;
}

double prMaxLikelihood(Matrix covInv, Matrix classe1, Matrix classe2, double* entrada)
{
    // Prerequisitos (Matrizes nao nulas):
    if((covInv == NULL) || (classe1 == NULL) || (classe2 == NULL) || (entrada == NULL))
        return -1;

    Matrix parte1;  // Matriz m(1, 1) com o resultado da parte I da eq. 3.
    Matrix parte2;  // Matriz m(1, 1) com o resultado da parte II da eq. 3.

    // Transforma entrada em uma matriz (1, n):
    Matrix tupla = matCria(1, matNlinhas(classe1));
    int i;
    for(i = 0; i < matNlinhas(classe1); i++)
        matColoca(tupla, 0, i, entrada[i]);

    // Parte 1 (x^t . C^-1 . (classe1 - classe2)):
    Matrix diferenca = matSubtrai(classe1, classe2);
    Matrix covDif = matProdutoMatricial(covInv, diferenca);
    parte1 = matProdutoMatricial(tupla, covDif);

    // Parte 2 (0.5 . (classe1 + classe2)^t . C^-1 . (classe1 - classe2)):
    Matrix soma = matSoma(classe1, classe2);
    Matrix somaT = matTransposta(soma);
    matMultiplicaEscalar(somaT, 0.5);
    parte2 = matProdutoMatricial(somaT, covDif);

    // Subtrai o resultado obtido em cada parte (eq. 3):
    double res = matPega(parte1, 0, 0) - matPega(parte2, 0, 0);

    // Libera matrizes:
    matLibera(diferenca);
    matLibera(soma);
    matLibera(somaT);
    matLibera(covDif);
    matLibera(parte1);
    matLibera(parte2);
    matLibera(tupla);

    // Retorna o resultado:
    return res;
}

int prClasseProvavel (Matrix covInv, Matrix *medias, double* tupla, int nClasses)
{
    // Prerequisitos (Matrizes nao nulas, nClasses positivo):
    if((covInv == NULL) || (medias == NULL) || (tupla == NULL) || (nClasses <= 0))
        return -1;

    double maxLH;                   // Armazenar o resultado de max likelihood ratio test.
    double maiorLH = LONG_MIN;      // Armazenar o maior resultado de maxLH. Inicia com o menor valor possivel.
    int maiorClasse;                // Classe referente ao maior LH.

    // Determina o maxLH entre cada combinacao de classe possivel:
    int i, j;
    for(i = 0; i < nClasses; i++)
        for(j = 0; j < nClasses; j++)
            // Nao realiza o teste entre classes iguais:
            if(i != j)
            {
                maxLH = prMaxLikelihood(covInv, medias[i], medias[j], tupla);
                //maxLH = fabs(maxLH);  // Nao e calculado sobre o modulo.

                //printf("r(%d, %d): %lf\n", i, j, maxLH);

                // Se o teste de max LH for maior que o atual maior, substitua-o:
                if(maxLH > maiorLH)
                {
                    maiorLH = maxLH;
                    maiorClasse = i;    // Classe mais provavel.
                }
            }

    return maiorClasse;
}

void prImprimeResultados (Matrix treinamento, Matrix verificacao, Matrix covariancia, Matrix* medias, int k, int hits, const char* input, const char* output)
{
    // Dados dos datasets:
    printf("\nPattern Recognition Application\n======= =========== ===========\n\n");
    printf("Input Dataset: %s (%d inputs in %d columns)\n", input, matNlinhas(treinamento), matNcolunas(treinamento) + 1);
    printf("Input Dataset: %s (%d inputs in %d columns)\n", output, matNlinhas(verificacao), matNcolunas(verificacao) + 1);
    printf("\nNumber of Classes: %d\n", k);

    // Vetores media:
    printf("\nMean Vectors\n==== =======\n\n");
    int i, j;
    for(i = 0; i < k; i++)
    {
        printf("m_%d = [ ", i);
        for(j = 0; j < matNlinhas(medias[i]) - 1; j++)
            printf("%.2lf\t", matPega(medias[i], j, 0));
        printf("%.2lf ]\n\n", matPega(medias[i], j, 0));
    }

    // Matriz covariancia:
    printf("\nCovariance Matrix\n========== ======\n\n");
    matImprime(covariancia);

    // Sumario:
    printf("\nSummary\n=======\n\n");
    printf("# of Hits\t: %d\n", hits);
    printf("# of Misses\t: %d\n", matNlinhas(verificacao) - hits);
    printf("Percent\t\t: %.2f %%\n", (float) hits * 100 / matNlinhas(verificacao));

    return;
}