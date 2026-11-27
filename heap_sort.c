#include "ordenacao.h"

/* Restaura a propriedade de max-heap na subárvore cuja raiz é indice. */
static void descer(int vetor[], size_t tamanho, size_t indice)
{
    while (indice < tamanho / 2) {
        size_t maior = indice;
        size_t esquerda = 2 * indice + 1;
        size_t direita = esquerda + 1;

        if (esquerda < tamanho && vetor[esquerda] > vetor[maior])
            maior = esquerda;
        if (direita < tamanho && vetor[direita] > vetor[maior])
            maior = direita;
        if (maior == indice)
            return;

        int temporario = vetor[indice];
        vetor[indice] = vetor[maior];
        vetor[maior] = temporario;
        indice = maior;
    }
}

void heap_sort(int vetor[], size_t quantidade)
{
    if (quantidade < 2)
        return;

    /* Constrói o max-heap de baixo para cima. */
    for (size_t inicio = quantidade / 2; inicio > 0; --inicio)
        descer(vetor, quantidade, inicio - 1);

    /* Move o maior elemento para o fim e reduz o heap ativo. */
    for (size_t fim = quantidade; fim > 1; --fim) {
        int temporario = vetor[0];
        vetor[0] = vetor[fim - 1];
        vetor[fim - 1] = temporario;
        descer(vetor, fim - 1, 0);
    }
}
