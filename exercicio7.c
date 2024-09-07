/*
Escreva um programa que conte quantas estruturas de ‘Pessoa’ existem no arquivo
“pessoas.bin” e exiba esse número.
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

    int i = 0;

    while (fread(pessoas,sizeof(Pessoa),1,arquivo)==1)
    {
        i++;
    }

    printf("%d Pessoas",i);
    
    return 0;
}