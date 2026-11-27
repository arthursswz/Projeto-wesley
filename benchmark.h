#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stddef.h>

#define QUANTIDADE_TESTES 10

typedef struct {
    size_t quantidade;
    double tempo_insertion;
    double tempo_heap;
    int insertion_valido;
    int heap_valido;
} ResultadoBenchmark;

/* Executa os dez tamanhos a partir dos prefixos do mesmo vetor original. */
int executar_benchmark(const int dados[], size_t quantidade,
                       ResultadoBenchmark resultados[QUANTIDADE_TESTES]);
void apresentar_resultados(
    const ResultadoBenchmark resultados[QUANTIDADE_TESTES]);
int salvar_resultados_csv(
    const char *caminho,
    const ResultadoBenchmark resultados[QUANTIDADE_TESTES]);

#endif
