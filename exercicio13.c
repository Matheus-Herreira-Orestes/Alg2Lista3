/*
Declare um arquivo com registros que contém os seguintes campos: NÚMERO DA CONTA,
NOME DO CLIENTE, SALDO e DATA DA ÚLTIMA OPERAÇÃO. Faça um programa que ca-
dastre e consulte os registros deste arquivo.
*/

#include <stdio.h>
#include <string.h>

struct DATA{
    int dia;
    int mes;
    int ano;
};

struct CONTA{
    long numero;
    char nome[15];
    float saldo;
    struct DATA data;
};


typedef struct CONTA Conta;

int main() {
    FILE *arquivo;
    Conta conta;
    
    arquivo = fopen("contas.bin","wb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    int continuar = 1;

    do{
        printf("Informe o numero da conta: \n");
        scanf("%ld",&conta.numero);
        getchar();

        printf("Informe o nome do titular: \n");
        fgets(conta.nome,sizeof(conta.nome),stdin);
        getchar();

        printf("Informe o saldo da conta: \n");
        scanf("%f",&conta.saldo);
        getchar();

        printf("Informe a data: (dia mes ano)\n");
        scanf("%d %d %d",&conta.data.dia, &conta.data.mes,&conta.data.ano);
        getchar();

        fwrite(&conta,sizeof(Conta),1,arquivo);

        printf("Deseja continuar? (1=sim / 0=nao) : \n");
        scanf("%d",&continuar);

    }while(continuar == 1);

    fclose(arquivo);

    arquivo = fopen("contas.bin","rb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    while(fread(&conta,sizeof(conta),1,arquivo) == 1){
        printf("Numero da conta: %ld\n",conta.numero);
        printf("Nome do titular: %s\n",conta.nome);
        printf("Saldo da conta: %f\n",conta.saldo);
        printf("Data: %d/%d/%d\n\n",conta.data.dia,conta.data.mes,conta.data.ano);
    }

    fclose(arquivo);

    
    return 0;
}