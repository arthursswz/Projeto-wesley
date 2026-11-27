#include "benchmark.h"
#include "dados.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int opcao;
    int *dados;
    ResultadoBenchmark resultados[QUANTIDADE_TESTES];

    printf("=== Comparação de algoritmos de ordenação ===\n");
    printf("1 - Executar benchmark (10.000 a 100.000 elementos)\n");
    printf("0 - Sair\n");
    printf("Opção: ");
    if (scanf("%d", &opcao) != 1 || (opcao != 0 && opcao != 1)) {
        fprintf(stderr, "Opção inválida.\n");
        return EXIT_FAILURE;
    }
    if (opcao == 0)
        return EXIT_SUCCESS;

    dados = ler_dados("dados/numeros.txt", QUANTIDADE_DADOS);
    if (dados == NULL)
        return EXIT_FAILURE;

    if (!executar_benchmark(dados, QUANTIDADE_DADOS, resultados)) {
        free(dados);
        return EXIT_FAILURE;
    }
    apresentar_resultados(resultados);

    printf("\nSalvar resultados em CSV? (1 = sim, 0 = não): ");
    if (scanf("%d", &opcao) == 1 && opcao == 1) {
        if (salvar_resultados_csv("resultados/benchmark.csv", resultados))
            printf("Resultados salvos em resultados/benchmark.csv\n");
        else {
            free(dados);
            return EXIT_FAILURE;
        }
    }

    free(dados);
    return EXIT_SUCCESS;
}
