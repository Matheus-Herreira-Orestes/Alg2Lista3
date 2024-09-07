/*
Faça um programa que simule um controle de estoque de uma loja, onde cada produto, re-
presentado por meio de um registro, possui um IDENTIFICADOR INTEIRO, NOME, QUAN-
TIDADE e CUSTO UNITÁRIO. O programa deve permitir a inclusão e remoção de novos pro-
dutos, consulta de produtos por nome, alteração de registros, geração de relatórios (exemplo:

qual vendeu mais, qual tem maior estoque, produtos cujo estoque esteja abaixo de X unida-
des, etc.). Todos os registros devem ser armazenados sequencialmente em um arquivo biná-
rio. O programa deve disponibilizar um menu de opções ao usuário. Exemplo: 1 – Incluir Pro-
duto, 2 – consultar, etc.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct PRODUTO {
    int id;
    char nome[50];
    int qtd;
    float custo;
};

typedef struct PRODUTO Produto;

void adicionarProduto(FILE *arquivo) {
    Produto produto;
    fseek(arquivo, 0, SEEK_END);

    printf("Informe o ID do produto: ");
    scanf("%d", &produto.id);
    getchar();

    printf("Informe o nome do produto: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    printf("Informe a quantidade: ");
    scanf("%d", &produto.qtd);
    getchar();

    printf("Informe o custo unitario: ");
    scanf("%f", &produto.custo);
    getchar();

    fwrite(&produto, sizeof(Produto), 1, arquivo);
    printf("Produto adicionado com sucesso!\n");
}

void consultarProduto(FILE *arquivo) {
    Produto produto;
    char nomeBusca[50];

    printf("Informe o nome do produto a ser consultado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    rewind(arquivo);
    int encontrado = 0;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (strcmp(produto.nome, nomeBusca) == 0) {
            printf("\nProduto encontrado!\n");
            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.qtd);
            printf("Custo Unitario: %.2f\n", produto.custo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado!\n");
    }
}

void removerProduto(FILE *arquivo) {
    Produto produto;
    char nomeRemove[50];
    FILE *temp;

    printf("Informe o nome do produto a ser removido: ");
    fgets(nomeRemove, sizeof(nomeRemove), stdin);
    nomeRemove[strcspn(nomeRemove, "\n")] = '\0';

    temp = fopen("temp.bin", "wb");

    rewind(arquivo);
    int encontrado = 0;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (strcmp(produto.nome, nomeRemove) != 0) {
            fwrite(&produto, sizeof(Produto), 1, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);
    
    remove("produtos.bin");
    rename("temp.bin", "produtos.bin");

    arquivo = fopen("produtos.bin", "ab+");

    if (encontrado) {
        printf("Produto removido com sucesso!\n");
    } else {
        printf("Produto nao encontrado!\n");
    }
}

void editarProduto(FILE *arquivo) {
    Produto produto;
    char nomeEdita[50];
    FILE *temp;

    printf("Informe o nome do produto a ser editado: ");
    fgets(nomeEdita, sizeof(nomeEdita), stdin);
    nomeEdita[strcspn(nomeEdita, "\n")] = '\0';

    temp = fopen("temp.bin", "wb");

    rewind(arquivo);
    int encontrado = 0;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (strcmp(produto.nome, nomeEdita) == 0) {
            printf("Produto encontrado!\n");

            printf("Informe a nova quantidade: ");
            scanf("%d", &produto.qtd);
            getchar();

            printf("Informe o novo custo unitario: ");
            scanf("%f", &produto.custo);
            getchar();

            encontrado = 1;
        }
        fwrite(&produto, sizeof(Produto), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    remove("produtos.bin");
    rename("temp.bin", "produtos.bin");

    arquivo = fopen("produtos.bin", "ab+");

    if (encontrado) {
        printf("Produto editado com sucesso!\n");
    } else {
        printf("Produto nao encontrado!\n");
    }
}

void relatorio(FILE *arquivo) {
    Produto produto;
    Produto maisVendido, maiorEstoque;
    int estoqueMinimo;
    
    printf("\n=== Relatorio de Estoque ===\n");

    rewind(arquivo); 
    int primeiro = 1;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (primeiro) {
            maiorEstoque = produto;
            primeiro = 0;
        } else if (produto.qtd > maiorEstoque.qtd) {
            maiorEstoque = produto;
        }
    }

    printf("Produto com maior estoque: %s (Quantidade: %d)\n", maiorEstoque.nome, maiorEstoque.qtd);

    printf("Informe o limite minimo de estoque: ");
    scanf("%d", &estoqueMinimo);
    getchar();

    rewind(arquivo); 
    printf("\nProdutos com estoque abaixo de %d unidades:\n", estoqueMinimo);
    int encontrou = 0;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (produto.qtd < estoqueMinimo) {
            printf("Nome: %s, Quantidade: %d\n", produto.nome, produto.qtd);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum produto com estoque abaixo de %d unidades.\n", estoqueMinimo);
    }
}

int main() {
    FILE *arquivo;

    arquivo = fopen("produtos.bin", "ab+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar produto\n");
        printf("2. Consultar produto\n");
        printf("3. Remover produto\n");
        printf("4. Editar produto\n");
        printf("5. Relatorio\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarProduto(arquivo);
                break;
            case 2:
                consultarProduto(arquivo);
                break;
            case 3:
                removerProduto(arquivo);
                arquivo = fopen("produtos.bin", "ab+");
                break;
            case 4:
                editarProduto(arquivo);
                arquivo = fopen("produtos.bin", "ab+");
                break;
            case 5:
                relatorio(arquivo);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    fclose(arquivo);
    return 0;
}
