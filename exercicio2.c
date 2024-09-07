/*
Escreva um programa em C que leia os números inteiros do arquivo “dados.bin” (criado no
exercício anterior) e os exiba no console.
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

    arquivo = fopen("dados.bin","rb");
    
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    while (fread(&numeros[0],sizeof(Numeros),1,arquivo) == 1)
    {
        printf("Numero: %d\n",numeros[0].numero);
    }
    
    
    return 0;
}