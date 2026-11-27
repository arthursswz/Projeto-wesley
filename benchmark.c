#include "benchmark.h"

#include "ordenacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int esta_ordenado(const int vetor[], size_t quantidade)
{
    for (size_t i = 1; i < quantidade; ++i)
        if (vetor[i - 1] > vetor[i])
            return 0;
    return 1;
}

/* Confere também que cada ordenação preservou os valores do prefixo. */
static int mesmos_elementos(const int original[], const int ordenado[],
                            size_t quantidade)
{
    int *copia_original = malloc(quantidade * sizeof(*copia_original));
    int *copia_ordenada = malloc(quantidade * sizeof(*copia_ordenada));
    int iguais = 1;

    if (copia_original == NULL || copia_ordenada == NULL) {
        free(copia_original);
        free(copia_ordenada);
        return 0;
    }
    memcpy(copia_original, original, quantidade * sizeof(*original));
    memcpy(copia_ordenada, ordenado, quantidade * sizeof(*ordenado));
    heap_sort(copia_original, quantidade);
    heap_sort(copia_ordenada, quantidade);
    if (memcmp(copia_original, copia_ordenada,
               quantidade * sizeof(*copia_original)) != 0)
        iguais = 0;

    free(copia_original);
    free(copia_ordenada);
    return iguais;
}

int executar_benchmark(const int dados[], size_t quantidade,
                       ResultadoBenchmark resultados[QUANTIDADE_TESTES])
{
    if (dados == NULL || resultados == NULL || quantidade < 100000) {
        fprintf(stderr, "Erro: o benchmark requer pelo menos 100.000 dados.\n");
        return 0;
    }

    for (size_t teste = 0; teste < QUANTIDADE_TESTES; ++teste) {
        size_t n = (teste + 1) * 10000;
        int *vetor_insertion = malloc(n * sizeof(*vetor_insertion));
        int *vetor_heap = malloc(n * sizeof(*vetor_heap));
        clock_t inicio, fim;

        if (vetor_insertion == NULL || vetor_heap == NULL) {
            fprintf(stderr, "Erro: memória insuficiente no teste de %zu elementos.\n", n);
            free(vetor_insertion);
            free(vetor_heap);
            return 0;
        }

        /* As cópias idênticas são preparadas fora das medições. */
        memcpy(vetor_insertion, dados, n * sizeof(*dados));
        memcpy(vetor_heap, dados, n * sizeof(*dados));

        inicio = clock();
        insertion_sort(vetor_insertion, n);
        fim = clock();
        resultados[teste].tempo_insertion = (double)(fim - inicio) / CLOCKS_PER_SEC;

        inicio = clock();
        heap_sort(vetor_heap, n);
        fim = clock();
        resultados[teste].tempo_heap = (double)(fim - inicio) / CLOCKS_PER_SEC;

        resultados[teste].quantidade = n;
        resultados[teste].insertion_valido =
            esta_ordenado(vetor_insertion, n) &&
            mesmos_elementos(dados, vetor_insertion, n);
        resultados[teste].heap_valido =
            esta_ordenado(vetor_heap, n) && mesmos_elementos(dados, vetor_heap, n);

        if (!resultados[teste].insertion_valido)
            fprintf(stderr, "Falha na validação do Insertion Sort (%zu elementos).\n", n);
        if (!resultados[teste].heap_valido)
            fprintf(stderr, "Falha na validação do Heap Sort (%zu elementos).\n", n);

        free(vetor_insertion);
        free(vetor_heap);
    }
    return 1;
}

void apresentar_resultados(const ResultadoBenchmark resultados[QUANTIDADE_TESTES])
{
    printf("\n%-12s %-23s %-18s\n", "Elementos", "Insertion Sort (s)", "Heap Sort (s)");
    printf("----------------------------------------------------------\n");
    for (size_t i = 0; i < QUANTIDADE_TESTES; ++i) {
        printf("%-12zu %-23.6f %-18.6f%s%s\n",
               resultados[i].quantidade,
               resultados[i].tempo_insertion,
               resultados[i].tempo_heap,
               resultados[i].insertion_valido ? "" : " [INVÁLIDO]",
               resultados[i].heap_valido ? "" : " [INVÁLIDO]");
    }
}

int salvar_resultados_csv(
    const char *caminho,
    const ResultadoBenchmark resultados[QUANTIDADE_TESTES])
{
    FILE *arquivo = fopen(caminho, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: não foi possível criar '%s'.\n", caminho);
        return 0;
    }

    fprintf(arquivo, "elementos,insertion_sort_s,heap_sort_s,insertion_valido,heap_valido\n");
    for (size_t i = 0; i < QUANTIDADE_TESTES; ++i) {
        fprintf(arquivo, "%zu,%.9f,%.9f,%s,%s\n",
                resultados[i].quantidade,
                resultados[i].tempo_insertion,
                resultados[i].tempo_heap,
                resultados[i].insertion_valido ? "sim" : "nao",
                resultados[i].heap_valido ? "sim" : "nao");
    }
    if (fclose(arquivo) != 0) {
        fprintf(stderr, "Erro ao finalizar o arquivo CSV '%s'.\n", caminho);
        return 0;
    }
    return 1;
}
