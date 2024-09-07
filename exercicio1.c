/*
Escreva um programa em C que crie um arquivo binário chamado “dados.bin”. O programa
deve pedir ao usuário para inserir 5 números inteiros, que serão gravados no arquivo.
*/

#include <stdio.h>
#include <string.h>

struct NUMEROS
{
    int numero;
};


    typedef struct NUMEROS Numeros;

int main(){

    FILE *arquivo;


    Numeros numeros[5];

    arquivo = fopen("dados.bin","wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("\nNumero: ");
        scanf("%d",&numeros[i].numero);
    }

    fwrite(numeros,sizeof(Numeros),5,arquivo);

    fclose(arquivo);
    
    return 0;
}