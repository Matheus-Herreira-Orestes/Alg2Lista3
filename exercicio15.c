/*
Supondo-se a existência de um arquivo A, com registros em que os campos são NOME e
SALÁRIO, faça um programa que crie um arquivo B, através da cópia dos registros de A.
*/

#include <stdio.h>
#include <string.h>

struct REGISTRO{
    char nome[15];
    float salario;
};

typedef struct REGISTRO Registro;

int main() {
    FILE *arquivoA, *arquivoB;

    Registro funcionario;
    
    arquivoA = fopen("arquivoA.bin","wb");

    if(arquivoA == NULL || arquivoB == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Nome do funcionario : \n");
        fgets(funcionario.nome,sizeof(funcionario.nome),stdin);

        printf("Salario do funcionario : \n");
        scanf("%f",&funcionario.salario);
        getchar();

        fwrite(&funcionario,sizeof(Registro),1,arquivoA);
    }

    
    fclose(arquivoA);

    arquivoA = fopen("arquivoA.bin","rb");
    arquivoB = fopen("arquivoB.bin","wb");

    if(arquivoA == NULL || arquivoB == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    while (fread(&funcionario,sizeof(Registro),1,arquivoA) == 1)
    {
        fwrite(&funcionario,sizeof(Registro),1,arquivoB);
    }

    fclose(arquivoA);
    fclose(arquivoB);

    return 0;
}
