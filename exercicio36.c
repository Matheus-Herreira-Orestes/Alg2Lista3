/*
Escreva um programa para atualizar contas bancarias. O programa deve abrir quatro arquivos

binários: (a) contas dos clientes no dia anterior, (b) movimentações no dia (débitos e crédi-
tos), (c) contas criadas no dia (contendo o saldo inicial) e (d) contas removidas no dia. O sal-
do atual de cada conta deve ser atualizado com base nas movimentações diárias. Um novo

arquivo binário de contas de clientes deve ser criado, contendo o saldo atualizado de cada
cliente (com base nas movimentações diárias) e as novas contas. As contas removidas no dia
não devem aparecer neste novo arquivo. Após criar este arquivo o programa e encerrado. Os
vetores utilizados devem ser alocados dinamicamente. Os dados de cada cliente sao: número
da conta (produzido automaticamente pelo sistema), nome e saldo. Uma movimentação é
composta de número da conta, tipo da operação (crédito ou débito), valor.
*/
#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100
#define MAX_MOVIMENTACOES 200

typedef struct {
    int numero_conta;
    char nome[100];
    float saldo;
} Conta;

typedef struct {
    int numero_conta;
    char tipo_operacao; 
    float valor;
} Movimentacao;

Conta contas_anterior[MAX_CONTAS];
Movimentacao movimentacoes[MAX_MOVIMENTACOES];
Conta novas_contas[MAX_CONTAS];
Conta contas_atualizadas[MAX_CONTAS];

int carregar_contas(const char* arquivo, Conta* contas) {
    FILE* fp = fopen(arquivo, "rb");
    if (!fp) return 0;

    int count = 0;
    while (fread(&contas[count], sizeof(Conta), 1, fp) && count < MAX_CONTAS) {
        count++;
    }
    fclose(fp);
    return count;
}

int carregar_movimentacoes(const char* arquivo, Movimentacao* movimentacoes) {
    FILE* fp = fopen(arquivo, "rb");
    if (!fp) return 0;

    int count = 0;
    while (fread(&movimentacoes[count], sizeof(Movimentacao), 1, fp) && count < MAX_MOVIMENTACOES) {
        count++;
    }
    fclose(fp);
    return count;
}

int buscar_conta(Conta* contas, int tamanho, int numero_conta) {
    for (int i = 0; i < tamanho; i++) {
        if (contas[i].numero_conta == numero_conta) {
            return i;
        }
    }
    return -1;
}

void atualizar_saldo(Conta* contas, int tamanho_contas, Movimentacao* movimentacoes, int tamanho_mov) {
    for (int i = 0; i < tamanho_mov; i++) {
        int indice = buscar_conta(contas, tamanho_contas, movimentacoes[i].numero_conta);
        if (indice != -1) {
            if (movimentacoes[i].tipo_operacao == 'C') {
                contas[indice].saldo += movimentacoes[i].valor;
            } else if (movimentacoes[i].tipo_operacao == 'D') {
                contas[indice].saldo -= movimentacoes[i].valor;
            }
        }
    }
}

void salvar_contas(const char* arquivo, Conta* contas, int tamanho) {
    FILE* fp = fopen(arquivo, "wb");
    fwrite(contas, sizeof(Conta), tamanho, fp);
    fclose(fp);
}

int remover_contas(Conta* contas, int tamanho, const char* arquivo_removidas) {
    FILE* fp = fopen(arquivo_removidas, "rb");
    if (!fp) return tamanho;

    Conta removidas[MAX_CONTAS];
    int tam_removidas = 0;
    while (fread(&removidas[tam_removidas], sizeof(Conta), 1, fp) && tam_removidas < MAX_CONTAS) {
        tam_removidas++;
    }
    fclose(fp);

    for (int i = 0; i < tam_removidas; i++) {
        int indice = buscar_conta(contas, tamanho, removidas[i].numero_conta);
        if (indice != -1) {
            for (int j = indice; j < tamanho - 1; j++) {
                contas[j] = contas[j + 1];
            }
            tamanho--;
        }
    }
    return tamanho;
}

int main() {
    int tamanho_contas_anterior = carregar_contas("contas_anterior.bin", contas_anterior);
    int tamanho_movimentacoes = carregar_movimentacoes("movimentacoes.bin", movimentacoes);
    int tamanho_novas_contas = carregar_contas("novas_contas.bin", novas_contas);

    int tamanho_atualizado = 0;
    memcpy(contas_atualizadas, contas_anterior, tamanho_contas_anterior * sizeof(Conta));
    tamanho_atualizado += tamanho_contas_anterior;
    memcpy(contas_atualizadas + tamanho_contas_anterior, novas_contas, tamanho_novas_contas * sizeof(Conta));
    tamanho_atualizado += tamanho_novas_contas;

    atualizar_saldo(contas_atualizadas, tamanho_atualizado, movimentacoes, tamanho_movimentacoes);

    tamanho_atualizado = remover_contas(contas_atualizadas, tamanho_atualizado, "contas_removidas.bin");

    salvar_contas("contas_atualizadas.bin", contas_atualizadas, tamanho_atualizado);

    return 0;
}
