/*
Declare dois arquivos usando o mesmo registro, com os campos TELEFONE, CIDADE e
TEMPO DE LIGAÇÃO. Faça um programa cadastre registros nestes arquivos. O programa
deve também listar os telefones das cidades em comuns dos dois arquivos.
*/


#include <stdio.h>
#include <string.h>


struct TELEFONE{
    long numero_telefone;
    char cidade[15];
    float tempo;
};


typedef struct TELEFONE Telefone;

int main() {
    FILE *telefoneA, *telefoneB;
    Telefone telefone;

    
    telefoneA = fopen("telefoneA.bin","wb");
    telefoneB = fopen("telefoneB.bin","wb");

    if(telefoneA == NULL || telefoneB == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    int continuarA = 0;
    
    do{
        printf("Informe o numero de telefone: \n");
        scanf("%ld",&telefone.numero_telefone);
        getchar();

        printf("Informe a cidade: \n");
        fgets(telefone.cidade,sizeof(telefone.cidade),stdin);
        telefone.cidade[strcspn(telefone.cidade, "\n")] = '\0';

        printf("Informe o tempo da ligacao: \n");
        scanf("%f",&telefone.tempo);
        getchar();

        fwrite(&telefone,sizeof(telefone),1,telefoneA);

        printf("Deseja continuar? (1=sim / 0=nao) : \n");
        scanf("%d",&continuarA);

    }while(continuarA == 1);

    int continuarB = 0;

    do{
        printf("Informe o numero de telefone: \n");
        scanf("%ld",&telefone.numero_telefone);
        getchar();

        printf("Informe a cidade: \n");
        fgets(telefone.cidade,sizeof(telefone.cidade),stdin);
        telefone.cidade[strcspn(telefone.cidade, "\n")] = '\0';

        printf("Informe o tempo da ligacao: \n");
        scanf("%f",&telefone.tempo);
        getchar();

        fwrite(&telefone,sizeof(telefone),1,telefoneB);

        printf("Deseja continuar? (1=sim / 0=nao) : \n");
        scanf("%d",&continuarB);

    }while(continuarB == 1);

    fclose(telefoneA);
    fclose(telefoneB);

    telefoneA = fopen("telefoneA.bin","rb");
    telefoneB = fopen("telefoneB.bin","rb");

    if(telefoneA == NULL || telefoneB == NULL){
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    Telefone registrosA[100];
    int countA = 0;
    while (fread(&registrosA[countA], sizeof(Telefone), 1, telefoneA) == 1) {
        countA++;
    }

    Telefone registrosB[100];
    int countB = 0;
    while (fread(&registrosB[countB], sizeof(Telefone), 1, telefoneB) == 1) {
        countB++;
    }

    for (int i = 0; i < countA; i++) {
        for (int j = 0; j < countB; j++) {
            if (strcmp(registrosA[i].cidade, registrosB[j].cidade) == 0) {
                printf("Cidade comum: %s\n", registrosA[i].cidade);
                printf("Telefone: %ld\n", registrosA[i].numero_telefone);
                printf("Tempo: %.2f\n", registrosA[i].tempo);
            }
        }
    }

    fclose(telefoneA);
    fclose(telefoneB);
    


    
    return 0;
}