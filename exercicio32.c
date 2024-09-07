/*
Elabore um programa para pesquisar alunos matriculados nos cursos de Ciência da Compu-
tação e Sistemas de Informação. As pesquisas devem ser feitas pelo nome ou pelo código de

matrícula, de acordo com a opção escolhida pelo usuário. Para cada uma das opções, o pro-
grama deve abrir o arquivo, carregar um vetor de registros e permitir repetidas pesquisas, até

que o usuário digite um número negativo para matrícula ou “FIM” para o nome (neste caso
deve-se voltar ao menu principal). Em cada pesquisa, devem ser apresentados os dados do

aluno ou, se o registro não for encontrado, uma mensagem explicativa. Para sair do progra-
ma, o usuário deverá escolher a opção “Fim” do menu principal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOME 100

typedef struct {
    int matricula;
    char nome[MAX_NOME];
    char curso[MAX_NOME];
} Aluno;

void carregar_arquivo(Aluno alunos[], int *tamanho, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    *tamanho = 0;
    while (fscanf(arquivo, "%d %[^\n] %[^\n]", &alunos[*tamanho].matricula, alunos[*tamanho].nome, alunos[*tamanho].curso) != EOF) {
        (*tamanho)++;
    }

    fclose(arquivo);
}

void pesquisar_por_matricula(Aluno alunos[], int tamanho) {
    int matricula;

    while (1) {
        printf("Digite a matricula do aluno (numero negativo para sair): ");
        scanf("%d", &matricula);
        
        if (matricula < 0) {
            break;
        }

        int encontrado = 0;
        for (int i = 0; i < tamanho; i++) {
            if (alunos[i].matricula == matricula) {
                printf("Aluno encontrado:\n");
                printf("Matricula: %d\n", alunos[i].matricula);
                printf("Nome: %s\n", alunos[i].nome);
                printf("Curso: %s\n", alunos[i].curso);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Aluno com matricula %d nao encontrado.\n", matricula);
        }
    }
}

void pesquisar_por_nome(Aluno alunos[], int tamanho) {
    char nome[MAX_NOME];

    while (1) {
        printf("Digite o nome do aluno (FIM para sair): ");
        getchar();
        fgets(nome, MAX_NOME, stdin);
        nome[strcspn(nome, "\n")] = 0;

        if (strcmp(nome, "FIM") == 0) {
            break;
        }

        int encontrado = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(alunos[i].nome, nome) == 0) {
                printf("Aluno encontrado:\n");
                printf("Matricula: %d\n", alunos[i].matricula);
                printf("Nome: %s\n", alunos[i].nome);
                printf("Curso: %s\n", alunos[i].curso);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Aluno com nome '%s' nao encontrado.\n", nome);
        }
    }
}

int main() {
    Aluno alunos[MAX_ALUNOS];
    int tamanho = 0;
    int opcao;

    carregar_arquivo(alunos, &tamanho, "alunos.txt");

    while (1) {
        printf("\nMenu principal:\n");
        printf("1. Pesquisar por matricula\n");
        printf("2. Pesquisar por nome\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                pesquisar_por_matricula(alunos, tamanho);
                break;
            case 2:
                pesquisar_por_nome(alunos, tamanho);
                break;
            case 3:
                printf("Encerrando o programa.\n");
                return 0;
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
