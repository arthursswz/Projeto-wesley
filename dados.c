#include "dados.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int *ler_dados(const char *caminho, size_t quantidade)
{
    FILE *arquivo = fopen(caminho, "r");
    int *vetor;

    if (arquivo == NULL) {
        fprintf(stderr, "Erro: não foi possível abrir '%s'.\n", caminho);
        return NULL;
    }

    vetor = malloc(quantidade * sizeof(*vetor));
    if (vetor == NULL) {
        fprintf(stderr, "Erro: não foi possível alocar memória para os dados.\n");
        fclose(arquivo);
        return NULL;
    }

    for (size_t i = 0; i < quantidade; ++i) {
        if (fscanf(arquivo, "%d", &vetor[i]) != 1) {
            fprintf(stderr,
                    "Erro: o arquivo contém menos de %zu inteiros ou dados inválidos (posição %zu).\n",
                    quantidade, i + 1);
            free(vetor);
            fclose(arquivo);
            return NULL;
        }
    }

    /* Depois dos valores, aceita apenas espaços em branco até o fim. */
    {
        int caractere;
        while ((caractere = fgetc(arquivo)) != EOF) {
            if (!isspace((unsigned char)caractere)) {
                fprintf(stderr,
                        "Erro: há conteúdo extra ou inválido após os %zu inteiros.\n",
                        quantidade);
                free(vetor);
                fclose(arquivo);
                return NULL;
            }
        }
        if (ferror(arquivo)) {
            fprintf(stderr, "Erro durante a leitura de '%s'.\n", caminho);
            free(vetor);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return vetor;
}
