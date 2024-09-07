/*
Escreva um programa que leia o arquivo “pessoas.bin” e exiba as informações de todas as
pessoas.
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

int main(){

    FILE *arquivo;

    Pessoa pessoas[4];


    arquivo = fopen("pessoas.bin","rb");


    fread(pessoas,sizeof(Pessoa),4,arquivo);

    for (int i = 0; i < 4; i++)
    {
        printf("Pessoa %d\n", i + 1);
        printf("Nome: %s\n", pessoas[i].nome);
        printf("Idade: %d\n", pessoas[i].idade);
        printf("Altura: %.2f\n\n", pessoas[i].altura);
    } 
    return 0;
}