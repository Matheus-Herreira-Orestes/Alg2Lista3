/*
Crie uma estrutura chamada ‘Pessoa’ com os campos nome (string), idade (inteiro) e altura
(float). Escreva um programa que crie um arquivo binário chamado “pessoas.bin” e grave as
informações de 4 pessoas neste arquivo.
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
    FILE *texto;

    Pessoa pessoas[4];


    arquivo = fopen("pessoas.bin","wb");
    texto = fopen("pessoas.txt","w");

    for (int i = 0; i < 4; i++)
    {

        printf("\nNome : ");
        fgets(pessoas[i].nome, sizeof(pessoas[i].nome), stdin);

        size_t len = strlen(pessoas[i].nome);
        if (len > 0 && pessoas[i].nome[len - 1] == '\n') {
            pessoas[i].nome[len - 1] = '\0';
        }

        printf("\nIdade : ");
        scanf("%d",&pessoas[i].idade);
        getchar();

        printf("\nAltura : ");
        scanf("%f",&pessoas[i].altura);
        getchar();

    }

    for (int i = 0; i < 4; i++)
    {
        fprintf(texto, "Nome: %s\n", pessoas[i].nome);
        fprintf(texto, "Idade: %d\n", pessoas[i].idade);
        fprintf(texto, "Altura: %.2f\n\n", pessoas[i].altura);
    }
    

    fwrite(pessoas,sizeof(Pessoa),4,arquivo);
    
    fclose(arquivo);
    
    return 0;
}