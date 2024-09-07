/*
Escreva um programa que preencha um vetor com números inteiros digitados pelo usuário
(no máximo 1000 números). Após a digitação, o vetor deverá ser ordenado e, em seguida,

pesquisado inúmeras vezes. A cada pesquisa deverá ser retornado a posição (ordem de en-
trada) do número ou uma mensagem explicativa quando ele não for encontrado. Tanto a en-
trada quanto a pesquisa serão finalizadas se o usuário digitar -999.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMEROS 1000

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int buscar_posicao_original(int valor, int vetor[], int original[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) {
            for (int j = 0; j < tamanho; j++) {
                if (original[j] == valor) {
                    return j;
                }
            }
        }
    }
    return -1;
}

int main() {
    int vetor[MAX_NUMEROS];
    int vetor_original[MAX_NUMEROS];
    int num, tamanho = 0;
    
    printf("Digite numeros inteiros (digite -999 para parar):\n");
    
    while (1) {
        scanf("%d", &num);
        if (num == -999) {
            break;
        }
        if (tamanho < MAX_NUMEROS) {
            vetor[tamanho] = num;
            vetor_original[tamanho] = num;
            tamanho++;
        } else {
            printf("Numero maximo de entradas atingido.\n");
            break;
        }
    }

    qsort(vetor, tamanho, sizeof(int), comparar);
    printf("Vetor ordenado.\n");

    while (1) {
        printf("Digite o numero a ser pesquisado (digite -999 para sair): ");
        scanf("%d", &num);

        if (num == -999) {
            break;
        }

        int posicao = buscar_posicao_original(num, vetor, vetor_original, tamanho);
        
        if (posicao != -1) {
            printf("Numero %d foi encontrado na posicao de entrada %d.\n", num, posicao + 1);
        } else {
            printf("Numero %d nao foi encontrado.\n", num);
        }
    }

    return 0;
}
