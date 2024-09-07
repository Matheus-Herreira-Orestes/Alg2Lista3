/*
A seção de controle de produção de uma fábrica mantém um arquivo de registros de produ-
ção por máquinas. Cada registro contém o número da máquina e o número de peças produ-
zidas em um dia. Supondo que a fábrica possua três máquinas, escreva um programa que
separe o arquivo em três arquivos, um para cada máquina.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_MACHINES 3

typedef struct {
    int num_maquina;
    int pecas_produzidas;
} RegistroProducao;

void separarArquivos(const char* arquivoEntrada) {
    FILE *entrada, *saida[MAX_MACHINES];
    RegistroProducao registro;

    entrada = fopen(arquivoEntrada, "rb");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    for (int i = 0; i < MAX_MACHINES; i++) {
        char nomeArquivo[20];
        sprintf(nomeArquivo, "maquina%d.bin", i + 1);
        saida[i] = fopen(nomeArquivo, "wb");
        if (saida[i] == NULL) {
            printf("Erro ao criar o arquivo para a maquina %d.\n", i + 1);
            exit(1);
        }
    }

    while (fread(&registro, sizeof(RegistroProducao), 1, entrada)) {
        if (registro.num_maquina >= 1 && registro.num_maquina <= MAX_MACHINES) {
            fwrite(&registro, sizeof(RegistroProducao), 1, saida[registro.num_maquina - 1]);
        }
    }

    fclose(entrada);
    for (int i = 0; i < MAX_MACHINES; i++) {
        fclose(saida[i]);
    }

    printf("Registros separados com sucesso!\n");
}

int main() {
    const char* nomeArquivo = "producao.bin";

    separarArquivos(nomeArquivo);

    return 0;
}
