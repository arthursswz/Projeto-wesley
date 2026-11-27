# Comparação entre Insertion Sort e Heap Sort

Projeto acadêmico em C que lê uma base fixa de inteiros e compara dois
algoritmos de ordenação usando os mesmos prefixos de dados.

## Organização e comunicação

- `main.c`: apresenta o menu, carrega a base e coordena a execução.
- `dados.c` / `dados.h`: lê e confere exatamente 100.000 inteiros de
  `dados/numeros.txt`.
- `insertion_sort.c`, `heap_sort.c` / `ordenacao.h`: implementam os algoritmos;
  ambos recebem o vetor e seu tamanho.
- `benchmark.c` / `benchmark.h`: cria cópias dos prefixos, mede somente as
  chamadas de ordenação com `clock()`, valida ordem e preservação de valores,
  mostra a tabela e grava o CSV.
- `resultados/`: destino do arquivo `benchmark.csv`, quando solicitado.

O menu inicia a leitura da base apenas quando o benchmark é escolhido. Para
cada tamanho de 10.000 até 100.000, em passos de 10.000, o benchmark copia o
prefixo original para dois vetores e passa uma cópia a cada algoritmo. Depois
da medição, cada resultado precisa estar em ordem crescente e conter os mesmos
valores do prefixo de entrada.

## Compilação e execução

Na raiz do projeto:

```sh
gcc -std=c11 -Wall -Wextra -O2 main.c dados.c insertion_sort.c heap_sort.c benchmark.c -o ordenacao
./ordenacao
```

Escolha `1` para executar os dez tamanhos. O Insertion Sort tem complexidade
quadrática no caso médio e pode demorar bastante nos maiores vetores. Ao final,
é possível salvar os tempos medidos em `resultados/benchmark.csv`.
