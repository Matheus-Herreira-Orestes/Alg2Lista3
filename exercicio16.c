/*
Escreva um programa para criar, listar e remover os dados de uma agenda armazenados em

um arquivo sequencial, sendo que os dados serão lidos a partir do teclado. O registro de en-
trada do arquivo possui os seguintes campos: NOME, RUA, NÚMERO, TELEFONE, CIDADE

e ESTADO.
*/

#include <stdio.h>
#include <string.h>

struct AGENDA {
    char nome[15];
    char rua[15];
    int numero;
    int telefone;
    char cidade[15];
    char estado[3];
};

typedef struct AGENDA Agenda;

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void listarContatos(FILE *arquivo) {
    Agenda dados;
    rewind(arquivo);  
    printf("\nListando contatos:\n");
    while (fread(&dados, sizeof(Agenda), 1, arquivo) > 0) {
        printf("\nNome: %s\nRua: %s\nNumero: %d\nTelefone: %d\nCidade: %s\nEstado: %s\n",
               dados.nome, dados.rua, dados.numero, dados.telefone, dados.cidade, dados.estado);
    }
}

void removerContato(FILE *arquivo, const char *nomeParaRemover) {
    FILE *temp = fopen("temp.bin", "wb");
    Agenda dados;
    rewind(arquivo); 
    
    int encontrado = 0;

    while (fread(&dados, sizeof(Agenda), 1, arquivo) > 0) {
        if (strcmp(dados.nome, nomeParaRemover) != 0) {
            fwrite(&dados, sizeof(Agenda), 1, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("agenda.bin");
    rename("temp.bin", "agenda.bin");

    if (encontrado) {
        printf("Contato removido com sucesso.\n");
    } else {
        printf("Contato nao encontrado.\n");
    }
}

int main() {
    FILE *arquivo;
    Agenda dados;
    
    arquivo = fopen("agenda.bin", "ab+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar contato\n");
        printf("2. Listar contatos\n");
        printf("3. Remover contato\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Informe o nome: ");
                fgets(dados.nome, sizeof(dados.nome), stdin);
                remove_newline(dados.nome);

                printf("Informe a rua: ");
                fgets(dados.rua, sizeof(dados.rua), stdin);
                remove_newline(dados.rua);

                printf("Informe o numero: ");
                scanf("%d", &dados.numero);
                getchar();

                printf("Informe o telefone: ");
                scanf("%d", &dados.telefone);
                getchar();

                printf("Informe a cidade: ");
                fgets(dados.cidade, sizeof(dados.cidade), stdin);
                remove_newline(dados.cidade);

                printf("Informe o estado (sigla de 2 letras): ");
                fgets(dados.estado, sizeof(dados.estado), stdin);
                remove_newline(dados.estado);

                fwrite(&dados, sizeof(Agenda), 1, arquivo);
                printf("Contato adicionado com sucesso!\n");
                break;

            case 2:
                listarContatos(arquivo);
                break;

            case 3: {
                char nomeParaRemover[15];
                printf("Informe o nome do contato a ser removido: ");
                fgets(nomeParaRemover, sizeof(nomeParaRemover), stdin);
                remove_newline(nomeParaRemover);
                removerContato(arquivo, nomeParaRemover);

                arquivo = fopen("agenda.bin", "ab+");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo!\n");
                    return 1;
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    fclose(arquivo);
    return 0;
}
