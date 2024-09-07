/*
Uma instituição de pesquisa recolheu amostras em três regiões a respeito do nível de vida da
população destas regiões. Cada amostra constitui um registro com os seguintes campos:

SEXO, IDADE, SALÁRIO, ESTADO CIVIL, NÚMERO DE DEPENDENTES, VALOR DO PA-
TRIMÔNIO, QUANTIDADE DE CALORIAS ABSORVIDAS POR DIA e GRAU DE INSTRU-
ÇÃO. Em cada região, os dados foram armazenados em um arquivo seqüencial, sendo os re-
gistros colocados em ordem crescente de idade. Escreva um programa que intercale estes

arquivos de modo que o arquivo resultante permaneça ordenado.
*/
#include <stdio.h>
#include <string.h>

struct AMOSTRA {
    int idade;
    char sexo;
    char estadoCivil[15];
    int dependentes;
    float patrimonio;
    float calorias;
    float instrucao;
};

typedef struct AMOSTRA Amostra;

void criarArquivosRegioes() {
    FILE *arq1 = fopen("regiao1.bin", "wb");
    FILE *arq2 = fopen("regiao2.bin", "wb");
    FILE *arq3 = fopen("regiao3.bin", "wb");

    if (!arq1 || !arq2 || !arq3) {
        printf("Erro ao criar arquivos das regioes.\n");
        return;
    }

    Amostra r1[] = {
        {25, 'M', "Solteiro", 0, 50000.0, 2000.0, 12.0},
        {30, 'F', "Casado", 2, 100000.0, 2500.0, 16.0},
        {45, 'M', "Divorciado", 1, 200000.0, 2200.0, 14.0}
    };

    Amostra r2[] = {
        {22, 'F', "Solteiro", 0, 30000.0, 1800.0, 10.0},
        {35, 'M', "Casado", 3, 150000.0, 3000.0, 15.0},
        {55, 'F', "Vivo", 0, 250000.0, 2100.0, 18.0}
    };

    Amostra r3[] = {
        {20, 'M', "Solteiro", 0, 25000.0, 1700.0, 12.0},
        {28, 'F', "Casado", 1, 90000.0, 2400.0, 14.0},
        {50, 'M', "Divorciado", 2, 180000.0, 2600.0, 17.0}
    };

    fwrite(r1, sizeof(Amostra), 3, arq1);
    fwrite(r2, sizeof(Amostra), 3, arq2);
    fwrite(r3, sizeof(Amostra), 3, arq3);

    fclose(arq1);
    fclose(arq2);
    fclose(arq3);

    printf("Arquivos das regioes criados com sucesso!\n");
}

int lerAmostra(FILE *file, Amostra *amostra) {
    return fread(amostra, sizeof(Amostra), 1, file);
}

void intercalarArquivos(const char *regiao1, const char *regiao2, const char *regiao3, const char *saida) {
    FILE *arq1 = fopen(regiao1, "rb");
    FILE *arq2 = fopen(regiao2, "rb");
    FILE *arq3 = fopen(regiao3, "rb");
    FILE *arqSaida = fopen(saida, "wb");

    if (!arq1 || !arq2 || !arq3 || !arqSaida) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    Amostra a1, a2, a3;
    int fim1 = !lerAmostra(arq1, &a1);
    int fim2 = !lerAmostra(arq2, &a2);
    int fim3 = !lerAmostra(arq3, &a3);

    while (!fim1 || !fim2 || !fim3) {
        if (!fim1 && (fim2 || a1.idade <= a2.idade) && (fim3 || a1.idade <= a3.idade)) {
            fwrite(&a1, sizeof(Amostra), 1, arqSaida);
            fim1 = !lerAmostra(arq1, &a1);
        } else if (!fim2 && (fim1 || a2.idade <= a1.idade) && (fim3 || a2.idade <= a3.idade)) {
            fwrite(&a2, sizeof(Amostra), 1, arqSaida);
            fim2 = !lerAmostra(arq2, &a2);
        } else if (!fim3 && (fim1 || a3.idade <= a1.idade) && (fim2 || a3.idade <= a2.idade)) {
            fwrite(&a3, sizeof(Amostra), 1, arqSaida);
            fim3 = !lerAmostra(arq3, &a3);
        }
    }

    fclose(arq1);
    fclose(arq2);
    fclose(arq3);
    fclose(arqSaida);
    
    printf("Arquivos intercalados com sucesso!\n");
}

int main() {
    criarArquivosRegioes();

    const char *regiao1 = "regiao1.bin";
    const char *regiao2 = "regiao2.bin";
    const char *regiao3 = "regiao3.bin";
    const char *saida = "arquivo_intercalado.bin";

    intercalarArquivos(regiao1, regiao2, regiao3, saida);

    return 0;
}
