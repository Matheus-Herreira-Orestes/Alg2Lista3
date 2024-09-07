/*
Supondo-se que em um sistema computacional bancário exista um arquivo de acesso direto e
que cada registro gravado use como chave o número da conta do cliente, escreva um pro-
grama que, lendo um número da conta de um cliente, escreva o número da conta, o nome e o
saldo deste cliente.
*/
#include <stdio.h>
#include <string.h>

struct BANCO{
    int id;
    int numero;
    char nome[15];
    float saldo;
};

typedef struct BANCO Banco;

int main() {
    FILE *arquivo;

    Banco contas[] = {
        {1,1234,"matheus",1699.24},
        {2,42424,"pietra",4245.24},
        {3,4244,"lucas",6777.24},
        {4,6641,"ana",11112.24},
        {5,4567,"peter",77575.24},
    };
    
    arquivo = fopen("clientes.bin","wb");
    if(arquivo == NULL ){
        printf("Erro ao abrir arquivo!");
        return 1;
    }
    fwrite(contas,sizeof(Banco),5,arquivo);

    fclose(arquivo);

    arquivo = fopen("clientes.bin","rb");
    int continuar = 1;
    Banco cliente;
    int contaBuscar;
    int encontrado;

    do{

        rewind(arquivo);

        printf("Informe o ID da conta: \n");
        scanf("%d",&contaBuscar);

        while(fread(&cliente,sizeof(Banco),1,arquivo)){
            if(cliente.id == contaBuscar){
                printf("Nome: %s \n",cliente.nome);
                printf("Nome: %d \n",cliente.numero);
                printf("Nome: %f \n",cliente.saldo);
                encontrado = 1;
                break;
            }else{
                encontrado = 0;
            }
        }

        if(encontrado == 0){
            printf("conta nao encontrada!\n");
        }

        printf("Deseja continuar? (1-sim/0-nao)");
        scanf("%d",&continuar);


    }while(continuar != 0);


    fclose(arquivo);

    
    return 0;
}