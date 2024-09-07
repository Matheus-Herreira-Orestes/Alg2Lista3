/*
Escreva um programa que remova o segundo registro de ‘Pessoa’ do arquivo
“pessoas.bin”. O programa deve reescrever o arquivo sem o registro removido.
*/

#include <stdio.h>
#include <string.h>

struct PESSOA
{
    char nome[20];
    int idade;
    float altura;
};

    typedef struct PESSOA Pessoa;

int main() {
    FILE *arquivo, *temp;
    Pessoa pessoa;
    int posicao = 2;

    arquivo = fopen("pessoas.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo original.\n");
        return 1;
    }

    temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return 1;
    }

    int contador = 1;
    while (fread(&pessoa, sizeof(Pessoa), 1, arquivo) == 1) {
        if (contador != posicao) {
            fwrite(&pessoa, sizeof(Pessoa), 1, temp);
        }
        contador++;
    }

    fclose(arquivo);
    fclose(temp);

    remove("pessoas.bin");
    rename("temp.bin", "pessoas.bin");

    printf("O segundo registro foi removido com sucesso.\n");

    return 0;
}