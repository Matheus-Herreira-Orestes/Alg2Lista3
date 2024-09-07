/*
De acordo com o exercício anterior grave em um arquivo binário (a) todas as movimentações
que produziram saldo negativo, (b) tentativas de remover uma conta que não existe.
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
Movimentacao mov_negativo[MAX_MOVIMENTACOES];
Conta remocoes_invalidas[MAX_CONTAS];

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

void gravar_mov_negativo(const char* arquivo, Movimentacao* mov_negativo, int tamanho) {
    FILE* fp = fopen(arquivo, "wb");
    fwrite(mov_negativo, sizeof(Movimentacao), tamanho, fp);
    fclose(fp);
}

void gravar_remocoes_invalidas(const char* arquivo, Conta* remocoes_invalidas, int tamanho) {
    FILE* fp = fopen(arquivo, "wb");
    fwrite(remocoes_invalidas, sizeof(Conta), tamanho, fp);
    fclose(fp);
}

void atualizar_saldo(Conta* contas, int tamanho_contas, Movimentacao* movimentacoes, int tamanho_mov, Movimentacao* mov_negativo, int* tam_negativo) {
    *tam_negativo = 0;
    for (int i = 0; i < tamanho_mov; i++) {
        int indice = buscar_conta(contas, tamanho_contas, movimentacoes[i].numero_conta);
        if (indice != -1) {
            if (movimentacoes[i].tipo_operacao == 'C') {
                contas[indice].saldo += movimentacoes[i].valor;
            } else if (movimentacoes[i].tipo_operacao == 'D') {
                contas[indice].saldo -= movimentacoes[i].valor;
                if (contas[indice].saldo < 0) {
                    mov_negativo[*tam_negativo] = movimentacoes[i];
                    (*tam_negativo)++;
                }
            }
        }
    }
}

void salvar_contas(const char* arquivo, Conta* contas, int tamanho) {
    FILE* fp = fopen(arquivo, "wb");
    fwrite(contas, sizeof(Conta), tamanho, fp);
    fclose(fp);
}

int remover_contas(Conta* contas, int tamanho, const char* arquivo_removidas, Conta* remocoes_invalidas, int* tam_invalidas) {
    FILE* fp = fopen(arquivo_removidas, "rb");
    if (!fp) return tamanho;

    Conta removidas[MAX_CONTAS];
    int tam_removidas = 0;
    *tam_invalidas = 0;
    
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
        } else {
            remocoes_invalidas[*tam_invalidas] = removidas[i];
            (*tam_invalidas)++;
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

    int tam_negativo;
    atualizar_saldo(contas_atualizadas, tamanho_atualizado, movimentacoes, tamanho_movimentacoes, mov_negativo, &tam_negativo);
    gravar_mov_negativo("mov_negativo.bin", mov_negativo, tam_negativo);

    int tam_invalidas;
    tamanho_atualizado = remover_contas(contas_atualizadas, tamanho_atualizado, "contas_removidas.bin", remocoes_invalidas, &tam_invalidas);
    gravar_remocoes_invalidas("remocoes_invalidas.bin", remocoes_invalidas, tam_invalidas);

    salvar_contas("contas_atualizadas.bin", contas_atualizadas, tamanho_atualizado);

    return 0;
}
