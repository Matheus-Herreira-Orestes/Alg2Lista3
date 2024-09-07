/*
Escreva um programa que crie e/ou manipule um arquivo com os seguintes campos: NOME
DO FUNCIONÁRIO, NÚMERO DA FIRMA, SEXO, IDADE, CARGO, SALÁRIO, NÚMERO DE
DEPENDENTES e GRAU DE INSTRUÇÃO. O programa deve permitir a inclusão, a consulta
e a remoção de registros, assim como a alteração dos campos de um determinado registro. O
nome do arquivo deve ser fornecido pelo usuário, e o programa deve permitir reprocessamen-
to.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_CARGO 50
#define MAX_INSTRUCAO 50

typedef struct {
    char nome[MAX_NOME];
    int num_firma;
    char sexo;
    int idade;
    char cargo[MAX_CARGO];
    float salario;
    int num_dependentes;
    char grau_instrucao[MAX_INSTRUCAO];
} Funcionario;

void adicionar_funcionario(FILE *fp) {
    Funcionario f;
    printf("Nome do funcionario: ");
    fgets(f.nome, MAX_NOME, stdin);
    f.nome[strcspn(f.nome, "\n")] = '\0'; 
    printf("Número da firma: ");
    scanf("%d", &f.num_firma);

    printf("Sexo (M/F): ");
    scanf(" %c", &f.sexo);

    printf("Idade: ");
    scanf("%d", &f.idade);

    printf("Cargo: ");
    getchar();
    fgets(f.cargo, MAX_CARGO, stdin);
    f.cargo[strcspn(f.cargo, "\n")] = '\0';

    printf("Salário: ");
    scanf("%f", &f.salario);

    printf("Número de dependentes: ");
    scanf("%d", &f.num_dependentes);

    printf("Grau de instrucao: ");
    getchar();
    fgets(f.grau_instrucao, MAX_INSTRUCAO, stdin);
    f.grau_instrucao[strcspn(f.grau_instrucao, "\n")] = '\0';

    fwrite(&f, sizeof(Funcionario), 1, fp);
    printf("Funcionario adicionado com sucesso!\n");
}

void consultar_funcionarios(FILE *fp) {
    Funcionario f;
    rewind(fp);

    printf("Lista de funcionarios:\n");
    while (fread(&f, sizeof(Funcionario), 1, fp) == 1) {
        printf("\nNome: %s\n", f.nome);
        printf("Numero da firma: %d\n", f.num_firma);
        printf("Sexo: %c\n", f.sexo);
        printf("Idade: %d\n", f.idade);
        printf("Cargo: %s\n", f.cargo);
        printf("Salario: %.2f\n", f.salario);
        printf("Numero de dependentes: %d\n", f.num_dependentes);
        printf("Grau de instrução: %s\n", f.grau_instrucao);
    }
}

void remover_funcionario(FILE *fp, const char *nome_arquivo) {
    FILE *temp_fp;
    Funcionario f;
    char nome[MAX_NOME];
    int encontrado = 0;

    printf("Nome do funcionario a remover: ");
    getchar(); 
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    temp_fp = fopen("temp.bin", "wb");
    rewind(fp);

    while (fread(&f, sizeof(Funcionario), 1, fp) == 1) {
        if (strcmp(f.nome, nome) != 0) {
            fwrite(&f, sizeof(Funcionario), 1, temp_fp);
        } else {
            encontrado = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    remove(nome_arquivo);
    rename("temp.bin", nome_arquivo);

    if (encontrado) {
        printf("Funcionario removido com sucesso!\n");
    } else {
        printf("Funcionario nao encontrado.\n");
    }
}

void alterar_funcionario(FILE *fp, const char *nome_arquivo) {
    FILE *temp_fp;
    Funcionario f;
    char nome[MAX_NOME];
    int encontrado = 0;

    printf("Nome do funcionario a alterar: ");
    getchar();
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    temp_fp = fopen("temp.bin", "wb");
    rewind(fp);

    while (fread(&f, sizeof(Funcionario), 1, fp) == 1) {
        if (strcmp(f.nome, nome) == 0) {
            printf("Alterando informacoes de %s\n", f.nome);
            adicionar_funcionario(temp_fp);
            encontrado = 1;
        } else {
            fwrite(&f, sizeof(Funcionario), 1, temp_fp);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    remove(nome_arquivo);
    rename("temp.bin", nome_arquivo);

    if (encontrado) {
        printf("Funcionario alterado com sucesso!\n");
    } else {
        printf("Funcionario nao encontrado.\n");
    }
}

int main() {
    FILE *fp;
    char nome_arquivo[100];
    int opcao;

    printf("Nome do arquivo: ");
    fgets(nome_arquivo, 100, stdin);
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';

    while (1) {
        fp = fopen(nome_arquivo, "rb+");
        if (fp == NULL) {
            fp = fopen(nome_arquivo, "wb+");
            if (fp == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return 1;
            }
        }

        printf("\nEscolha uma opcao:\n");
        printf("1. Adicionar funcionario\n");
        printf("2. Consultar funcionarios\n");
        printf("3. Remover funcionario\n");
        printf("4. Alterar funcionario\n");
        printf("5. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_funcionario(fp);
                break;
            case 2:
                consultar_funcionarios(fp);
                break;
            case 3:
                remover_funcionario(fp, nome_arquivo);
                break;
            case 4:
                alterar_funcionario(fp, nome_arquivo);
                break;
            case 5:
                fclose(fp);
                exit(0);
            default:
                printf("Opcao invalida.\n");
        }

        fclose(fp);
    }

    return 0;
}
