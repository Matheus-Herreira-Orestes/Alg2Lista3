/*
Escreva um programa que verifique se o arquivo “dados.bin” existe. Se o arquivo existir, o
programa deve exibir uma mensagem confirmando sua existência; caso contrário, deve exibir
uma mensagem informando que o arquivo não foi encontrado.
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

    arquivo = fopen("dados.bin","rb");

    if(arquivo == NULL)
    {
        printf("Arquivo nao existe!!");
    }else{
        printf("Arquivo existe!!");
    }
    
    
    return 0;
}