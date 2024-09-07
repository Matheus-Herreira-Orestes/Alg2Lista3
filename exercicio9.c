/*
Escreva um programa que leia um arquivo binário contendo números inteiros e remova todos
os zeros, salvando os números restantes em um novo arquivo binário.
*/

#include <stdio.h>
#include <string.h>

struct INTEIROS {
    int numero;
};

typedef struct INTEIROS Inteiros;

// Função para exibir o conteúdo de sem_zeros.bin
void exibirArquivo(const char *nomeArquivo) {
    FILE *arquivo;
    Inteiros inteiro;

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo '%s' para leitura.\n", nomeArquivo);
        return;
    }

    printf("\nConteúdo de '%s':\n", nomeArquivo);
    while (fread(&inteiro, sizeof(Inteiros), 1, arquivo) == 1) {
        printf("%d\n", inteiro.numero);
    }

    fclose(arquivo);
}

int removerZeros(int numero) {
    char strNum[20], strSemZeros[20];
    int i, j = 0;

    sprintf(strNum, "%d", numero);

    for (i = 0; strNum[i] != '\0'; i++) {
        if (strNum[i] != '0') {
            strSemZeros[j++] = strNum[i];
        }
    }
    strSemZeros[j] = '\0';

    return (j == 0) ? 0 : atoi(strSemZeros);
}

int main() {
    FILE *arquivo, *novo;
    Inteiros inteiro;
    int continuar;

    arquivo = fopen("inteiros.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    do {
        printf("\nInforme um número: ");
        scanf("%d", &inteiro.numero);

        fwrite(&inteiro, sizeof(Inteiros), 1, arquivo);

        printf("Deseja continuar? 0-sim 1-nao: ");
        scanf("%d", &continuar);
    } while (continuar != 1);

    fclose(arquivo);

    arquivo = fopen("inteiros.bin", "rb");
    novo = fopen("sem_zeros.bin", "wb");
    if (arquivo == NULL || novo == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    while (fread(&inteiro, sizeof(Inteiros), 1, arquivo) == 1) {
        inteiro.numero = removerZeros(inteiro.numero);
        if (inteiro.numero != 0) {
            fwrite(&inteiro, sizeof(Inteiros), 1, novo);
        }
    }

    fclose(arquivo);
    fclose(novo);

    printf("Arquivo 'sem_zeros.bin' criado com sucesso, sem dígitos zero nos números.\n");

    exibirArquivo("sem_zeros.bin");

    return 0;
}

