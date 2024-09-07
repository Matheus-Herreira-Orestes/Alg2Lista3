/*
Dado o arquivo “alunos.dat” com registros com os campos NOME, NUMERO, CURSO, P1,
P2, MT e FREQUÊNCIA, faça um programa que cadastre, consulte, altere, exclua registros e

liste o número, o nome, a média final, a freqüência e a condição dos alunos (aprovado ou re-
provado). O cálculo da média final é dada por MF = 0,8*MP+0,2*MT, onde MP é a média

aritmética de P1 e P2, e o aluno é aprovado se MF4,95 e FREQÜÊNCIA70% e, reprovado,
caso contrário.
*/

#include <stdio.h>
#include <string.h>

struct ALUNO {
    char nome[50];
    int numero;
    char curso[50];
    float P1;
    float P2;
    float MT;
    float frequencia;
};

typedef struct ALUNO Aluno;

void cadastrarAluno(FILE *file);
void consultarAluno(FILE *file);
void alterarAluno(FILE *file);
void excluirAluno(FILE *file);
void listarAlunos(FILE *file);

int main() {
    FILE *file;
    int opcao;

    file = fopen("alunos.dat", "rb+");
    if (file == NULL) {
        file = fopen("alunos.dat", "wb+");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 1;
        }
    }

    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Consultar aluno\n");
        printf("3 - Alterar aluno\n");
        printf("4 - Excluir aluno\n");
        printf("5 - Listar alunos\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarAluno(file);
                break;
            case 2:
                consultarAluno(file);
                break;
            case 3:
                alterarAluno(file);
                break;
            case 4:
                excluirAluno(file);
                break;
            case 5:
                listarAlunos(file);
                break;
            case 6:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 6);

    fclose(file);
    return 0;
}

void cadastrarAluno(FILE *file) {
    Aluno aluno;

    printf("Informe o nome do aluno: ");
    getchar();
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

    printf("Informe o numero do aluno: ");
    scanf("%d", &aluno.numero);

    printf("Informe o curso: ");
    getchar();
    fgets(aluno.curso, sizeof(aluno.curso), stdin);
    aluno.curso[strcspn(aluno.curso, "\n")] = '\0';

    printf("Informe a nota P1: ");
    scanf("%f", &aluno.P1);
    printf("Informe a nota P2: ");
    scanf("%f", &aluno.P2);
    printf("Informe a nota MT: ");
    scanf("%f", &aluno.MT);
    printf("Informe a frequencia: ");
    scanf("%f", &aluno.frequencia);

    fseek(file, 0, SEEK_END);
    fwrite(&aluno, sizeof(Aluno), 1, file);

    printf("Aluno cadastrado com sucesso!\n");
}

void consultarAluno(FILE *file) {
    Aluno aluno;
    int numero, encontrado = 0;

    printf("Informe o numero do aluno: ");
    scanf("%d", &numero);

    rewind(file);
    while (fread(&aluno, sizeof(Aluno), 1, file) == 1) {
        if (aluno.numero == numero) {
            printf("\nAluno encontrado:\n");
            printf("Nome: %s\n", aluno.nome);
            printf("Curso: %s\n", aluno.curso);
            printf("P1: %.2f, P2: %.2f, MT: %.2f, Frequencia: %.2f%%\n", aluno.P1, aluno.P2, aluno.MT, aluno.frequencia);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno nao encontrado.\n");
    }
}

void alterarAluno(FILE *file) {
    Aluno aluno;
    int numero, encontrado = 0;

    printf("Informe o numero do aluno a ser alterado: ");
    scanf("%d", &numero);

    rewind(file);
    while (fread(&aluno, sizeof(Aluno), 1, file) == 1) {
        if (aluno.numero == numero) {
            encontrado = 1;
            printf("Informe os novos dados do aluno:\n");

            printf("Nome atual: %s\n", aluno.nome);
            printf("Informe o novo nome: ");
            getchar();
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

            printf("Curso atual: %s\n", aluno.curso);
            printf("Informe o novo curso: ");
            fgets(aluno.curso, sizeof(aluno.curso), stdin);
            aluno.curso[strcspn(aluno.curso, "\n")] = '\0';

            printf("Nota P1 atual: %.2f\n", aluno.P1);
            printf("Informe a nova nota P1: ");
            scanf("%f", &aluno.P1);

            printf("Nota P2 atual: %.2f\n", aluno.P2);
            printf("Informe a nova nota P2: ");
            scanf("%f", &aluno.P2);

            printf("Nota MT atual: %.2f\n", aluno.MT);
            printf("Informe a nova nota MT: ");
            scanf("%f", &aluno.MT);

            printf("Frequencia atual: %.2f%%\n", aluno.frequencia);
            printf("Informe a nova frequencia: ");
            scanf("%f", &aluno.frequencia);

            fseek(file, -sizeof(Aluno), SEEK_CUR);
            fwrite(&aluno, sizeof(Aluno), 1, file);
            printf("Aluno alterado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno nao encontrado.\n");
    }
}

void excluirAluno(FILE *file) {
    FILE *tempFile;
    Aluno aluno;
    int numero, encontrado = 0;

    printf("Informe o numero do aluno a ser excluido: ");
    scanf("%d", &numero);

    tempFile = fopen("temp.dat", "wb+");
    if (tempFile == NULL) {
        printf("Erro ao criar o arquivo temporario.\n");
        return;
    }

    rewind(file);
    while (fread(&aluno, sizeof(Aluno), 1, file) == 1) {
        if (aluno.numero == numero) {
            printf("Aluno excluido: %s\n", aluno.nome);
            encontrado = 1;
        } else {
            fwrite(&aluno, sizeof(Aluno), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("alunos.dat");
    rename("temp.dat", "alunos.dat");

    file = fopen("alunos.dat", "rb+");

    if (!encontrado) {
        printf("Aluno nao encontrado.\n");
    }
}

void listarAlunos(FILE *file) {
    Aluno aluno;
    float MP, MF;
    int condicao;

    rewind(file);
    printf("\nLista de alunos:\n");
    while (fread(&aluno, sizeof(Aluno), 1, file) == 1) {
        MP = (aluno.P1 + aluno.P2) / 2;
        MF = 0.8 * MP + 0.2 * aluno.MT;

        printf("\nNumero: %d\n", aluno.numero);
        printf("Nome: %s\n", aluno.nome);
        printf("Media Final: %.2f\n", MF);
        printf("Frequencia: %.2f%%\n", aluno.frequencia);

        if (MF >= 4.95 && aluno.frequencia >= 70) {
            printf("Condicao: Aprovado\n");
        } else {
            printf("Condicao: Reprovado\n");
        }
    }
}
