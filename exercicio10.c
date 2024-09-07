/*
Defina uma estrutura chamada ‘Aluno’ com os seguintes campos: nome (string), idade (intei-
ro), nota (float). Escreva um programa que crie um arquivo binário chamado “alunos.bin” e

grave os dados de 5 alunos neste arquivo, fornecidos pelo usuário.
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
    FILE *arquivo;
    Alunos aluno[5];
    
    arquivo = fopen("alunos.bin","wb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("Informe o nome do aluno: \n");
        fgets(aluno[i].nome,sizeof(aluno[i].nome),stdin);
        getchar();

        printf("Informe a idade do aluno: \n");
        scanf("%d",&aluno[i].idade);
        getchar();

        printf("Informe a nota do aluno: \n\n");
        scanf("%f",&aluno[i].nota);
        getchar();

        fwrite(&aluno[i],sizeof(Alunos),1,arquivo);


    }

    return 0;
}