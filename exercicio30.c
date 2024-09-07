/*
Elabore um programa que leia dois arquivos binários (“salbruto.bin” e “desc.bin”) contendo,

respectivamente, os salários brutos e os descontos de até 100 funcionários. Para cada regis-
tro, deve-se calcular o salário líquido (salário bruto – descontos) e gravá-lo no arquivo texto

“salliq.txt”.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_FUNCIONARIOS 100

void criar_arquivo_salarios() {
    FILE *fp;
    float salarios_brutos[MAX_FUNCIONARIOS];
    int i, num_funcionarios;

    printf("Digite o numero de funcionarios (max %d): ", MAX_FUNCIONARIOS);
    scanf("%d", &num_funcionarios);

    fp = fopen("salbruto.bin", "wb");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de salarios brutos.\n");
        exit(1);
    }

    for (i = 0; i < num_funcionarios; i++) {
        printf("Salario bruto do funcionario %d: ", i + 1);
        scanf("%f", &salarios_brutos[i]);
    }

    fwrite(salarios_brutos, sizeof(float), num_funcionarios, fp);
    fclose(fp);
    printf("Arquivo 'salbruto.bin' criado com sucesso.\n");
}

void criar_arquivo_descontos() {
    FILE *fp;
    float descontos[MAX_FUNCIONARIOS];
    int i, num_funcionarios;

    printf("Digite o numero de funcionarios (max %d): ", MAX_FUNCIONARIOS);
    scanf("%d", &num_funcionarios);

    fp = fopen("desc.bin", "wb");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de descontos.\n");
        exit(1);
    }

    for (i = 0; i < num_funcionarios; i++) {
        printf("Desconto do funcionario %d: ", i + 1);
        scanf("%f", &descontos[i]);
    }

    fwrite(descontos, sizeof(float), num_funcionarios, fp);
    fclose(fp);
    printf("Arquivo 'desc.bin' criado com sucesso.\n");
}

void calcular_salario_liquido() {
    FILE *fp_salbruto, *fp_desc, *fp_salliq;
    float salarios_brutos[MAX_FUNCIONARIOS], descontos[MAX_FUNCIONARIOS], salario_liquido;
    int i, num_funcionarios;

    fp_salbruto = fopen("salbruto.bin", "rb");
    fp_desc = fopen("desc.bin", "rb");

    if (fp_salbruto == NULL || fp_desc == NULL) {
        printf("Erro ao abrir os arquivos binarios.\n");
        exit(1);
    }

    num_funcionarios = fread(salarios_brutos, sizeof(float), MAX_FUNCIONARIOS, fp_salbruto);
    fread(descontos, sizeof(float), num_funcionarios, fp_desc);

    fclose(fp_salbruto);
    fclose(fp_desc);

    fp_salliq = fopen("salliq.txt", "w");
    if (fp_salliq == NULL) {
        printf("Erro ao criar o arquivo de salarios liquidos.\n");
        exit(1);
    }

    for (i = 0; i < num_funcionarios; i++) {
        salario_liquido = salarios_brutos[i] - descontos[i];
        fprintf(fp_salliq, "Funcionario %d - Salario liquido: %.2f\n", i + 1, salario_liquido);
    }

    fclose(fp_salliq);
    printf("Arquivo 'salliq.txt' criado com sucesso.\n");
}

int main() {
    int opcao;

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1. Criar arquivo de salarios brutos\n");
        printf("2. Criar arquivo de descontos\n");
        printf("3. Calcular salario liquido\n");
        printf("4. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar_arquivo_salarios();
                break;
            case 2:
                criar_arquivo_descontos();
                break;
            case 3:
                calcular_salario_liquido();
                break;
            case 4:
                exit(0);
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
