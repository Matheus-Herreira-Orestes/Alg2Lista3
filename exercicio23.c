/*
Faça um programa que liste um arquivo seqüencial denominado DADOS que possui registros
com os campos de NOME, ENDEREÇO, CEP e TELEFONE.
*/

#include <stdio.h>
#include <string.h>

struct DADOS {
    char nome[50];
    char endereco[50];
    char CEP[15];
    char telefone[15];
};

typedef struct DADOS Dados;

int main() {
    FILE *arquivo;

    Dados registros[] = {
        {"Matheus Silva", "Rua A, 123", "12345-678", "1234-5678"},
        {"Ana Oliveira", "Av. B, 456", "98765-432", "9876-5432"},
        {"Lucas Pereira", "Rua C, 789", "56789-123", "3456-7890"}
    };

    arquivo = fopen("dados.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo dados.bin para escrita!\n");
        return 1;
    }

    fwrite(registros, sizeof(Dados), 3, arquivo);

    fclose(arquivo);

    printf("Registros adicionados com sucesso ao arquivo dados.bin!\n");

    return 0;
}
