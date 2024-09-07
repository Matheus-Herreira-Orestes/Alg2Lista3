/*
Faça um programa gerenciar uma agenda de contatos. Para cada contato armazene o nome,

o telefone e o aniversário (dia e mês). O programa deve permitir (1) inserir contato, (2) remo-
ver contato, (3) pesquisar um contato pelo nome, (4) listar todos os contatos, (5) listar os con-
tatos cujo nome inicia com uma dada letra, (6) imprimir os aniversariantes do mês. Sempre

que o programa for encerrado, os contatos devem ser armazenados em um arquivo binário.
Quando o programa iniciar, os contatos devem ser inicializados com os dados contidos neste
arquivo binário.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    char telefone[15];
    int dia_aniversario;
    int mes_aniversario;
} Contato;

void carregar_dados(Contato contatos[], int *tamanho) {
    FILE *arquivo = fopen("agenda.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado. Iniciando nova agenda.\n");
        *tamanho = 0;
        return;
    }
    *tamanho = fread(contatos, sizeof(Contato), MAX_CONTATOS, arquivo);
    fclose(arquivo);
}

void salvar_dados(Contato contatos[], int tamanho) {
    FILE *arquivo = fopen("agenda.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }
    fwrite(contatos, sizeof(Contato), tamanho, arquivo);
    fclose(arquivo);
    printf("Dados salvos com sucesso.\n");
}

void inserir_contato(Contato contatos[], int *tamanho) {
    if (*tamanho >= MAX_CONTATOS) {
        printf("Agenda cheia. Não é possível adicionar mais contatos.\n");
        return;
    }

    Contato novo_contato;
    printf("Digite o nome: ");
    getchar();
    fgets(novo_contato.nome, MAX_NOME, stdin);
    novo_contato.nome[strcspn(novo_contato.nome, "\n")] = '\0';
    printf("Digite o telefone: ");
    fgets(novo_contato.telefone, 15, stdin);
    novo_contato.telefone[strcspn(novo_contato.telefone, "\n")] = '\0';
    printf("Digite o dia de aniversário: ");
    scanf("%d", &novo_contato.dia_aniversario);
    printf("Digite o mês de aniversário: ");
    scanf("%d", &novo_contato.mes_aniversario);

    contatos[*tamanho] = novo_contato;
    (*tamanho)++;
    printf("Contato adicionado com sucesso.\n");
}

void remover_contato(Contato contatos[], int *tamanho) {
    char nome[MAX_NOME];
    printf("Digite o nome do contato a ser removido: ");
    getchar(); 
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *tamanho; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) {
            for (int j = i; j < *tamanho - 1; j++) {
                contatos[j] = contatos[j + 1];
            }
            (*tamanho)--;
            printf("Contato removido com sucesso.\n");
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

void pesquisar_contato(Contato contatos[], int tamanho) {
    char nome[MAX_NOME];
    printf("Digite o nome do contato para pesquisar: ");
    getchar();
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0'; 

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) {
            printf("Nome: %s\n", contatos[i].nome);
            printf("Telefone: %s\n", contatos[i].telefone);
            printf("Aniversário: %d/%d\n", contatos[i].dia_aniversario, contatos[i].mes_aniversario);
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

void listar_contatos(Contato contatos[], int tamanho) {
    printf("\nLista de todos os contatos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s\n", contatos[i].nome);
        printf("Telefone: %s\n", contatos[i].telefone);
        printf("Aniversário: %d/%d\n\n", contatos[i].dia_aniversario, contatos[i].mes_aniversario);
    }
}

void listar_contatos_por_letra(Contato contatos[], int tamanho) {
    char letra;
    printf("Digite a letra inicial dos contatos: ");
    getchar();  // Limpar buffer
    scanf("%c", &letra);

    printf("\nContatos que começam com a letra '%c':\n", letra);
    for (int i = 0; i < tamanho; i++) {
        if (contatos[i].nome[0] == letra) {
            printf("Nome: %s\n", contatos[i].nome);
            printf("Telefone: %s\n", contatos[i].telefone);
            printf("Aniversário: %d/%d\n\n", contatos[i].dia_aniversario, contatos[i].mes_aniversario);
        }
    }
}

void listar_aniversariantes_do_mes(Contato contatos[], int tamanho) {
    int mes;
    printf("Digite o mês para listar aniversariantes: ");
    scanf("%d", &mes);

    printf("\nAniversariantes do mês %d:\n", mes);
    for (int i = 0; i < tamanho; i++) {
        if (contatos[i].mes_aniversario == mes) {
            printf("Nome: %s\n", contatos[i].nome);
            printf("Telefone: %s\n", contatos[i].telefone);
            printf("Aniversário: %d/%d\n\n", contatos[i].dia_aniversario, contatos[i].mes_aniversario);
        }
    }
}

int main() {
    Contato contatos[MAX_CONTATOS];
    int tamanho = 0;
    int opcao;

    carregar_dados(contatos, &tamanho);

    while (1) {
        printf("\nMenu principal:\n");
        printf("1. Inserir contato\n");
        printf("2. Remover contato\n");
        printf("3. Pesquisar contato pelo nome\n");
        printf("4. Listar todos os contatos\n");
        printf("5. Listar contatos por letra inicial\n");
        printf("6. Listar aniversariantes do mes\n");
        printf("7. Sair e salvar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserir_contato(contatos, &tamanho);
                break;
            case 2:
                remover_contato(contatos, &tamanho);
                break;
            case 3:
                pesquisar_contato(contatos, tamanho);
                break;
            case 4:
                listar_contatos(contatos, tamanho);
                break;
            case 5:
                listar_contatos_por_letra(contatos, tamanho);
                break;
            case 6:
                listar_aniversariantes_do_mes(contatos, tamanho);
                break;
            case 7:
                salvar_dados(contatos, tamanho);
                printf("Encerrando o programa.\n");
                exit(0);
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
