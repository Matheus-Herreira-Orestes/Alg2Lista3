/*
O arquivo “bolsa.dat” contém registros das operações de um cliente na Bolsa de Valores. Ca-
da operação de compra ou venda que um cliente realiza na bolsa gera um registro com o

NÚMERO do cliente, o CÓDIGO da operação (V para Venda e C para Compra), a DESCRI-
ÇÃO do título comercializado, a QUANTIDADE de títulos comercializados e o VALOR UNI-
TÁRIO de cada título. Estes registros estão seqüencialmente organizados no arquivo BOLSA

de tal modo que todos os registros de um mesmo cliente estão juntos. Escreva um programa
para gerar o arquivo seqüencial RESULTADO, onde para cada cliente apareça um registro da
forma: NÚMERO DO CLIENTE, SALDO APURADO e TIPO DE SALDO. O TIPO DE SALDO
será igual a C (de Credor) se o valor comprado for maior que o vendido. Caso contrário, o
saldo será D (de Devedor).
*/

#include <stdio.h>
#include <string.h>

struct OPERACAO {
    int numeroCliente;
    char codigoOperacao;
    char descricaoTitulo[50];
    int quantidade;          
    float valorUnitario;     
};

typedef struct OPERACAO Operacao;

int main() {
    FILE *arquivoBolsa;

    Operacao operacoes[] = {
        {1, 'C', "Acoes Empresa X", 100, 10.0},
        {1, 'V', "Acoes Empresa X", 50, 12.0},
        {2, 'C', "Acoes Empresa Y", 200, 15.0},
        {2, 'V', "Acoes Empresa Y", 200, 20.0},
        {3, 'C', "Acoes Empresa Z", 300, 8.0}, 
        {3, 'V', "Acoes Empresa Z", 150, 9.0},
        {4, 'C', "Debentures Empresa A", 50, 25.0},
        {4, 'V', "Debentures Empresa A", 50, 27.5},
        {5, 'C', "Acoes Empresa B", 500, 5.0}, 
        {5, 'V', "Acoes Empresa B", 100, 6.0}, 
    };

    arquivoBolsa = fopen("bolsa.dat", "wb");
    if (arquivoBolsa == NULL) {
        printf("Erro ao criar o arquivo bolsa.dat!\n");
        return 1;
    }

    fwrite(operacoes, sizeof(Operacao), 10, arquivoBolsa);

    fclose(arquivoBolsa);

    printf("Arquivo bolsa.dat criado com sucesso!\n");

    return 0;
}
