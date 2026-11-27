#ifndef DADOS_H
#define DADOS_H

#include <stddef.h>

#define QUANTIDADE_DADOS 100000

/* Lê exatamente a quantidade indicada. Retorna NULL em caso de erro. */
int *ler_dados(const char *caminho, size_t quantidade);

#endif
