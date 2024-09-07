/*
Faça um programa que copie um arquivo binário de inteiros (denominado numeros.bin) para
um outro arquivo binário de inteiros (denominado pares.bin) de tal forma que apenas os nú-
meros pares sejam copiados.
*/

#include <stdio.h>
#include <string.h>



int main() {
    FILE *arquivo,*copia;
    int inteiro;

    int inteiros[] = {
        {1},{2},{521},{55},{155},{200},{550}
    };
    
    arquivo = fopen("numeros.bin","wb");
    if(arquivo == NULL ){
        printf("Erro ao abrir arquivo!");
        return 1;
    }
    fwrite(inteiros,sizeof(int),7,arquivo);

    fclose(arquivo);

    arquivo = fopen("numeros.bin","rb");
    copia = fopen("pares.bin","wb");

    if(arquivo == NULL || copia == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    while(fread(&inteiro,sizeof(int),1,arquivo) == 1){
        if(inteiro % 2 == 0){
            fwrite(&inteiro,sizeof(int),1,copia);
        }
    }

    fclose(arquivo);
    fclose(copia);

    
    return 0;
}