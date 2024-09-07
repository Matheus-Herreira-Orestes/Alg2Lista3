/*
Escreva um programa que leia o arquivo “alunos.bin” e exiba as informações de todos os
alunos.
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
    Alunos aluno;
    
    arquivo = fopen("alunos.bin","rb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    while (fread(&aluno,sizeof(Alunos),1,arquivo) == 1)
    {
        printf("Aluno : %s\n",aluno.nome);
        printf("Idade : %d\n",aluno.idade);
        printf("Nota : %f\n",aluno.nota);
    }
    
    fclose(arquivo);

    return 0;
}