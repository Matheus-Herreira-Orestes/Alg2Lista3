/*
Elabore um programa que copie o arquivo seqüencial denominado FONTE para um arquivo
seqüencial chamado FONTENOVA. Em ambos os arquivos os registros têm os seguintes
campos: CHAVE, INFORMAÇÃO e DATA.
*/

#include <stdio.h>
#include <string.h>

struct DATA
{
    int dia;
    int mes;
    int ano;
};

struct FONTE{
    int id;
    char info[15];
    float saldo;
    struct DATA data;
};



typedef struct FONTE Fonte;

int main() {
    FILE *arquivo,*copia;

     Fonte dados[] = {
        {1, "Matheus", 12.0, {10, 10, 2025}},
        {2, "Pietra", 24.0, {12, 11, 2025}},
        {3, "Lucas", 42.0, {5, 3, 2024}},
    };
    
    arquivo = fopen("fonte.bin","wb");
    if(arquivo == NULL ){
        printf("Erro ao abrir arquivo!");
        return 1;
    }
    fwrite(dados,sizeof(Fonte),3,arquivo);

    fclose(arquivo);

    arquivo = fopen("fonte.bin","rb");
    copia = fopen("fontenova.bin","wb");

     if (arquivo == NULL || copia == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return 1;
    }

    Fonte dado;

    while(fread(&dado,sizeof(Fonte),1,arquivo)==1){
        fwrite(&dado,sizeof(Fonte),1,copia);
    }

    fclose(arquivo);
    fclose(copia);

    return 0;
}