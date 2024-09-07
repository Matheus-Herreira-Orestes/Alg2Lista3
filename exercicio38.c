/*
O IBOP realizou uma pesquisa a nível nacional. Foi entrevistado um certo número de pesso-
as. Cada pessoa respondeu ao seguinte questionário:

Sexo: ( )M ( )F
Idade: ____ anos
Fumante: ( )S ( )N

Considere um arquivo binário de registros (denominado “resposta.bin”) que contém as res-
postas de todas as pessoas entrevistadas. Cada registro armazena a resposta de uma pes-
soa entrevistada através dos seguintes campos: sexo (um caractere, podendo ser ‘M’ ou ‘F’),

idade (valor inteiro), fumante (um caractere, podendo ser ‘S’ ou ‘N’). Faça um programa que
leia este arquivo binário e responda as seguintes perguntas:
• Qual é o percentual de fumantes em relação ao número total de pessoas entrevistadas?
• Qual é o percentual de homens não fumantes abaixo de 40 anos em relação ao número
total de homens entrevistados?
• Qual é o percentual de mulheres fumantes acima de 40 anos em relação ao número total
de mulheres entrevistadas?
*/

#include <stdio.h>

typedef struct {
    char sexo;
    int idade;
    char fumante;
} Resposta;

void calcular_percentuais(const char* arquivo) {
    FILE* fp = fopen(arquivo, "rb");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Resposta resposta;
    int total_pessoas = 0;
    int total_fumantes = 0;
    int total_homens = 0;
    int total_homens_nao_fumantes_abaixo_40 = 0;
    int total_mulheres = 0;
    int total_mulheres_fumantes_acima_40 = 0;

    while (fread(&resposta, sizeof(Resposta), 1, fp)) {
        total_pessoas++;
        
        if (resposta.fumante == 'S') {
            total_fumantes++;
        }

        if (resposta.sexo == 'M') {
            total_homens++;
            if (resposta.fumante == 'N' && resposta.idade < 40) {
                total_homens_nao_fumantes_abaixo_40++;
            }
        } else if (resposta.sexo == 'F') {
            total_mulheres++;
            if (resposta.fumante == 'S' && resposta.idade > 40) {
                total_mulheres_fumantes_acima_40++;
            }
        }
    }

    fclose(fp);

    if (total_pessoas == 0) {
        printf("Nenhuma pessoa entrevistada.\n");
        return;
    }

    float percentual_fumantes = (total_fumantes * 100.0) / total_pessoas;
    float percentual_homens_nao_fumantes_abaixo_40 = (total_homens > 0) ? (total_homens_nao_fumantes_abaixo_40 * 100.0) / total_homens : 0;
    float percentual_mulheres_fumantes_acima_40 = (total_mulheres > 0) ? (total_mulheres_fumantes_acima_40 * 100.0) / total_mulheres : 0;

    printf("Percentual de fumantes: %.2f%%\n", percentual_fumantes);
    printf("Percentual de homens nao fumantes abaixo de 40 anos: %.2f%%\n", percentual_homens_nao_fumantes_abaixo_40);
    printf("Percentual de mulheres fumantes acima de 40 anos: %.2f%%\n", percentual_mulheres_fumantes_acima_40);
}

int main() {
    calcular_percentuais("resposta.bin");
    return 0;
}
