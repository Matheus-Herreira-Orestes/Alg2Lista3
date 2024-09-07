/*
Escreva um programa que registre tudo que ocorrer com o carro: manutenções, combustível,
lavagens, etc., tudo com o valor gasto e a quilometragem. Além de um relatório geral, inclua
uma consulta sobre custo por quilometro e consumo médio. Armazene os dados em arquivo
binário.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTROS 100

typedef struct {
    char descricao[50];
    float valor;
    int quilometragem;
    float litros_combustivel; 
} Registro;

void registrar_evento(Registro registros[], int *tamanho) {
    if (*tamanho >= MAX_REGISTROS) {
        printf("Numero maximo de registros atingido.\n");
        return;
    }

    printf("Descricao do evento (manutencao, combustivel, lavagem, etc.): ");
    getchar();
    fgets(registros[*tamanho].descricao, 50, stdin);
    registros[*tamanho].descricao[strcspn(registros[*tamanho].descricao, "\n")] = '\0'; 

    printf("Valor gasto: ");
    scanf("%f", &registros[*tamanho].valor);

    printf("Quilometragem do carro: ");
    scanf("%d", &registros[*tamanho].quilometragem);

    printf("Digite a quantidade de litros de combustivel (0 se nao aplicavel): ");
    scanf("%f", &registros[*tamanho].litros_combustivel);

    (*tamanho)++;
}

void salvar_dados(Registro registros[], int tamanho) {
    FILE *arquivo = fopen("carro.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fwrite(registros, sizeof(Registro), tamanho, arquivo);
    fclose(arquivo);
    printf("Dados salvos com sucesso.\n");
}

void carregar_dados(Registro registros[], int *tamanho) {
    FILE *arquivo = fopen("carro.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar os dados.\n");
        return;
    }

    *tamanho = fread(registros, sizeof(Registro), MAX_REGISTROS, arquivo);
    fclose(arquivo);
    printf("Dados carregados com sucesso.\n");
}

void gerar_relatorio(Registro registros[], int tamanho) {
    printf("\nRelatorio geral de eventos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Evento %d:\n", i + 1);
        printf("Descricao: %s\n", registros[i].descricao);
        printf("Valor gasto: %.2f\n", registros[i].valor);
        printf("Quilometragem: %d\n", registros[i].quilometragem);
        if (registros[i].litros_combustivel > 0) {
            printf("Litros de combustivel: %.2f\n", registros[i].litros_combustivel);
        }
        printf("\n");
    }
}

void calcular_custo_por_km(Registro registros[], int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum registro disponivel.\n");
        return;
    }

    float total_gasto = 0;
    int km_inicial = registros[0].quilometragem;
    int km_final = registros[tamanho - 1].quilometragem;

    for (int i = 0; i < tamanho; i++) {
        total_gasto += registros[i].valor;
    }

    int km_percorridos = km_final - km_inicial;
    if (km_percorridos > 0) {
        printf("Custo por quilometro: %.2f\n", total_gasto / km_percorridos);
    } else {
        printf("Quilometragem insuficiente para calculo.\n");
    }
}

void calcular_consumo_medio(Registro registros[], int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum registro disponivel.\n");
        return;
    }

    float total_combustivel = 0;
    int km_inicial = -1, km_final = -1;

    for (int i = 0; i < tamanho; i++) {
        if (registros[i].litros_combustivel > 0) {
            total_combustivel += registros[i].litros_combustivel;
            if (km_inicial == -1) {
                km_inicial = registros[i].quilometragem;
            }
            km_final = registros[i].quilometragem;
        }
    }

    if (total_combustivel > 0 && km_inicial != -1 && km_final != -1) {
        int km_percorridos = km_final - km_inicial;
        if (km_percorridos > 0) {
            printf("Consumo medio: %.2f km/l\n", km_percorridos / total_combustivel);
        } else {
            printf("Quilometragem insuficiente para calculo.\n");
        }
    } else {
        printf("Dados insuficientes para calcular consumo medio.\n");
    }
}

int main() {
    Registro registros[MAX_REGISTROS];
    int tamanho = 0;
    int opcao;

    carregar_dados(registros, &tamanho);

    while (1) {
        printf("\nMenu principal:\n");
        printf("1. Registrar evento\n");
        printf("2. Gerar relatorio geral\n");
        printf("3. Calcular custo por quilometro\n");
        printf("4. Calcular consumo medio\n");
        printf("5. Sair e salvar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrar_evento(registros, &tamanho);
                break;
            case 2:
                gerar_relatorio(registros, tamanho);
                break;
            case 3:
                calcular_custo_por_km(registros, tamanho);
                break;
            case 4:
                calcular_consumo_medio(registros, tamanho);
                break;
            case 5:
                salvar_dados(registros, tamanho);
                exit(0);
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
