#include "ordenacao.h"

void insertion_sort(int vetor[], size_t quantidade)
{
    for (size_t i = 1; i < quantidade; ++i) {
        int chave = vetor[i];
        size_t j = i;

        while (j > 0 && vetor[j - 1] > chave) {
            vetor[j] = vetor[j - 1];
            --j;
        }
        vetor[j] = chave;
    }
}
