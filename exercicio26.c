/*
Escreva um programa para emitir a pré-matrícula de cada um dos alunos de um determinado
curso. Os dados estão dispostos em arquivos, conforme a estrutura abaixo.

O programa deve ler o número do semestre e, escrever o nome do curso, o número da matrí-
cula, nome do aluno, e a lista de disciplinas que o aluno poderá cursar. Verifique se existe

pré-requisito para a disciplina, caso exista, verifique se o aluno cursou o pré-requisito. As dis-
ciplinas a serem cursadas não poderão ser listadas se os seus respectivos pré-requisitos não

estiverem no arquivo de disciplinas cursadas.
*/

#include <stdio.h>
#include <string.h>

struct ALUNO {
    int matricula;
    char nome[50];
};

struct DISCIPLINA {
    int codigo;
    char nome[50];
    int preRequisito;
};

struct CURSADA {
    int matricula;
    int codigoDisciplina;
};

struct CURSO {
    int semestre;
    char nomeCurso[50];
    int codigoDisciplina;
};

typedef struct ALUNO Aluno;
typedef struct DISCIPLINA Disciplina;
typedef struct CURSADA Cursada;
typedef struct CURSO Curso;

int alunoCursou(int matricula, int codigoDisciplina, FILE *cursadasFile) {
    Cursada cursada;
    rewind(cursadasFile);

    while (fread(&cursada, sizeof(Cursada), 1, cursadasFile) == 1) {
        if (cursada.matricula == matricula && cursada.codigoDisciplina == codigoDisciplina) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *alunosFile, *disciplinasFile, *cursadasFile, *cursoFile;
    int semestre, i;

    alunosFile = fopen("alunos.dat", "rb");
    disciplinasFile = fopen("disciplinas.dat", "rb");
    cursadasFile = fopen("cursadas.dat", "rb");
    cursoFile = fopen("curso.dat", "rb");

    if (alunosFile == NULL || disciplinasFile == NULL || cursadasFile == NULL || cursoFile == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return 1;
    }

    printf("Informe o numero do semestre: ");
    scanf("%d", &semestre);

    Curso curso;
    Disciplina disciplina;

    printf("\nPre-matricula para o semestre %d\n", semestre);

    Aluno aluno;
    while (fread(&aluno, sizeof(Aluno), 1, alunosFile) == 1) {
        printf("\nAluno: %s (Matricula: %d)\n", aluno.nome, aluno.matricula);
        printf("Disciplinas a cursar:\n");

        rewind(cursoFile);

        while (fread(&curso, sizeof(Curso), 1, cursoFile) == 1) {
            if (curso.semestre == semestre) {
                rewind(disciplinasFile);
                while (fread(&disciplina, sizeof(Disciplina), 1, disciplinasFile) == 1) {
                    if (disciplina.codigo == curso.codigoDisciplina) {
                        if (disciplina.preRequisito == 0 || alunoCursou(aluno.matricula, disciplina.preRequisito, cursadasFile)) {
                            printf("- %s\n", disciplina.nome);
                        }
                    }
                }
            }
        }
    }

    fclose(alunosFile);
    fclose(disciplinasFile);
    fclose(cursadasFile);
    fclose(cursoFile);

    return 0;
}
