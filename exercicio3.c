/*
Escreva um programa que abra o arquivo “dados.bin” (exercícios anteriores) e permita ao
usuário atualizar o terceiro número inteiro com um novo valor fornecido por ele. Após a atuali-
zação, o programa deve salvar as alterações no arquivo.
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

    int novo_numero;

    arquivo = fopen("dados.bin","rb+");
    
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    fread(numeros,sizeof(Numeros),5,arquivo);


    printf("Informe um novo numero: \n");
    scanf("%d",&novo_numero);

    numeros[2].numero = novo_numero;

    fseek(arquivo, 0, SEEK_SET);

    fwrite(numeros,sizeof(Numeros),5,arquivo);
    
    return 0;
}