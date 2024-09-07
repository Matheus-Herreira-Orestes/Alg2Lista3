/*
Implemente um controle simples de mercadorias em uma despensa doméstica. Sobre cada

produto podem ser armazenado um código numérico, descrição e quantidade atual. O pro-
grama deve ter opções para entrada e retirada de produtos, bem como um relatório geral e

um de produtos não disponíveis. Armazene os dados em arquivo binário.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_DESC 50

typedef struct {
    int codigo;
    char descricao[MAX_DESC];
    int quantidade;
} Produto;

void carregar_dados(Produto produtos[], int *tamanho) {
    FILE *arquivo = fopen("despensa.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo nao encontrado. Iniciando uma nova lista de produtos.\n");
        *tamanho = 0;
        return;
    }
    *tamanho = fread(produtos, sizeof(Produto), MAX_PRODUTOS, arquivo);
    fclose(arquivo);
}

void salvar_dados(Produto produtos[], int tamanho) {
    FILE *arquivo = fopen("despensa.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }
    fwrite(produtos, sizeof(Produto), tamanho, arquivo);
    fclose(arquivo);
    printf("Dados salvos com sucesso.\n");
}

void entrada_produto(Produto produtos[], int *tamanho) {
    if (*tamanho >= MAX_PRODUTOS) {
        printf("Despensa cheia. Nao e possivel adicionar mais produtos.\n");
        return;
    }

    Produto novo_produto;
    printf("Digite o codigo do produto: ");
    scanf("%d", &novo_produto.codigo);
    getchar();  
    printf("Digite a descricao do produto: ");
    fgets(novo_produto.descricao, MAX_DESC, stdin);
    novo_produto.descricao[strcspn(novo_produto.descricao, "\n")] = '\0';  
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novo_produto.quantidade);

    produtos[*tamanho] = novo_produto;
    (*tamanho)++;
    printf("Produto adicionado com sucesso.\n");
}

void retirar_produto(Produto produtos[], int tamanho) {
    int codigo, quantidade;
    printf("Digite o codigo do produto para retirar: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Digite a quantidade a ser retirada: ");
            scanf("%d", &quantidade);
            if (quantidade > produtos[i].quantidade) {
                printf("Quantidade insuficiente no estoque.\n");
            } else {
                produtos[i].quantidade -= quantidade;
                printf("Produto retirado com sucesso.\n");
            }
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void relatorio_geral(Produto produtos[], int tamanho) {
    printf("\nRelatorio geral de produtos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Codigo: %d\n", produtos[i].codigo);
        printf("Descricao: %s\n", produtos[i].descricao);
        printf("Quantidade: %d\n\n", produtos[i].quantidade);
    }
}

void relatorio_produtos_nao_disponiveis(Produto produtos[], int tamanho) {
    printf("\nProdutos nao disponiveis (quantidade zero):\n");
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].quantidade == 0) {
            printf("Codigo: %d\n", produtos[i].codigo);
            printf("Descricao: %s\n\n", produtos[i].descricao);
        }
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int tamanho = 0;
    int opcao;

    carregar_dados(produtos, &tamanho);

    while (1) {
        printf("\nMenu principal:\n");
        printf("1. Entrada de produto\n");
        printf("2. Retirada de produto\n");
        printf("3. Relatorio geral\n");
        printf("4. Relatorio de produtos nao disponiveis\n");
        printf("5. Sair e salvar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                entrada_produto(produtos, &tamanho);
                break;
            case 2:
                retirar_produto(produtos, tamanho);
                break;
            case 3:
                relatorio_geral(produtos, tamanho);
                break;
            case 4:
                relatorio_produtos_nao_disponiveis(produtos, tamanho);
                break;
            case 5:
                salvar_dados(produtos, tamanho);
                printf("Encerrando o programa.\n");
                exit(0);
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
