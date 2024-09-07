/*
Dado o arquivo “cadastro.dat” com registros com os nomes NOME, SEXO, COR DE OLHOS,

ALTURA, PESO e DATA DE NASCIMENTO, faça um programa que o separe em dois arqui-
vos: um chamado “homens.dat”, com registros cujo campo SEXO apresente o valor 1 (sexo

masculino), e outro chamado “mulheres.dat”, com registros cujo campo SEXO seja igual a 2.
Os registros dos novos arquivos deverão possuir os seguintes campos: NOME, COR DE
OLHOS, PESO e DATA DE NASCIMENTO. O arquivo CADASTRO.DAT deve ser removido
no final do programa.
*/

#include <stdio.h>
#include <string.h>

struct DATA {
    int dia;
    int mes;
    int ano;
};

struct CADASTRO {
    char nome[50];
    int sexo; 
    char corOlhos[20];
    float altura;
    float peso;
    struct DATA dataNascimento;
};

typedef struct CADASTRO Cadastro;

int main() {
    FILE *arquivoCadastro;
    
    Cadastro pessoas[] = {
        {"João Silva", 1, "Castanhos", 1.80, 75.0, {10, 5, 1990}},
        {"Maria Oliveira", 2, "Verdes", 1.65, 60.0, {20, 7, 1985}},
        {"Carlos Pereira", 1, "Azuis", 1.75, 80.0, {15, 3, 1992}},
        {"Ana Souza", 2, "Pretos", 1.60, 55.0, {25, 9, 1995}}
    };
    
    arquivoCadastro = fopen("cadastro.dat", "wb");
    if (arquivoCadastro == NULL) {
        printf("Erro ao abrir o arquivo cadastro.dat!\n");
        return 1;
    }
    
    fwrite(pessoas, sizeof(Cadastro), 4, arquivoCadastro);
    
    fclose(arquivoCadastro);
    
    printf("Arquivo cadastro.dat criado com sucesso!\n");
    
    return 0;
}
