/*
Suponha que você tenha dois arquivos binários, “turmaA.bin” e “turmaB.bin”, cada um
contendo registros de ‘Aluno’. Escreva um programa que combine os registros desses dois
arquivos em um novo arquivo binário chamado “turma_completa.bin”.
*/

#include <stdio.h>
#include <string.h>

struct ALUNOS{
    char nome[15];
    int idade;
    float nota;
};

typedef struct ALUNOS Alunos;

int main() {
    FILE *arquivoA, *arquivoB,*turma_completa;
    Alunos alunosA[3];
    Alunos alunosB[3];

    Alunos alunoA;
    Alunos alunoB;
    
    arquivoA = fopen("turmaA.bin","wb");
    arquivoB = fopen("turmaB.bin","wb");

    if(arquivoA == NULL || arquivoB == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Nome %d da sala A : \n", i);
        fgets(alunosA[i].nome,sizeof(alunosA[i].nome),stdin);

        printf("Idade do aluno %d da sala A : \n", i);
        scanf("%d",&alunosA[i].idade);
        getchar(); 

        printf("Nota do aluno %d da sala A : \n", i);
        scanf("%f",&alunosA[i].nota);
        getchar();

        fwrite(&alunosA[i],sizeof(Alunos),1,arquivoA);
    }

    for (int j = 0; j < 3; j++)
    {
        printf("Nome %d da sala b : \n", j);
        fgets(alunosB[j].nome,sizeof(alunosB[j].nome),stdin);

        printf("Idade do aluno %d da sala B : \n", j);
        scanf("%d",&alunosB[j].idade);
        getchar();

        printf("Nota do aluno %d da sala B : \n", j);
        scanf("%f",&alunosB[j].nota);
        getchar();

        fwrite(&alunosB[j],sizeof(Alunos),1,arquivoB);
    }
    
    
    fclose(arquivoA);
    fclose(arquivoB);

    arquivoA = fopen("turmaA.bin","rb");
    arquivoB = fopen("turmaB.bin","rb");
    turma_completa = fopen("turma_completa.bin","wb");

    if(arquivoA == NULL || arquivoB == NULL || turma_completa == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    while (fread(&alunoA,sizeof(Alunos),1,arquivoA) == 1)
    {
        fwrite(&alunoA,sizeof(Alunos),1,turma_completa);
    }

    while (fread(&alunoB,sizeof(Alunos),1,arquivoB) == 1)
    {
        fwrite(&alunoB,sizeof(Alunos),1,turma_completa);
    }

    fclose(arquivoA);
    fclose(arquivoB);
    fclose(turma_completa);

    printf("A fusão das turmas A e B foi realizada com sucesso no arquivo 'turma_completa.bin'.\n");

    
    return 0;
}