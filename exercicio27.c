/*
Escreva um programa para gerenciar atendimentos em uma clínica. O menu de opções deve
conter:
1 - Marcar a consulta
2 - Desmarcar a consulta
3 - Escrever mapa de horários para um determinado dia
4 - Escrever o nome e as datas em que um paciente foi consulado
5 - Escrever o nome e o telefone de todos os pacientes cuja última consulta ocorreu há mais
de 6 meses e que tem idade superior a 50 anos
6 - Fim
Os dados de cada cliente estão dispostos em um arquivo, onde cada registro tem a seguinte
estrutura: código do cliente, nome do cliente, idade, endereço, telefone, patologia.
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

struct CLIENTE {
    int codigo;
    char nome[50];
    int idade;
    char endereco[100];
    char telefone[15];
    char patologia[50];
    struct tm ultimaConsulta;
};

typedef struct CLIENTE Cliente;

void marcarConsulta(FILE *file);
void desmarcarConsulta(FILE *file);
void escreverMapaHorarios(FILE *file);
void escreverConsultasPaciente(FILE *file);
void listarPacientesInativos(FILE *file);

int main() {
    FILE *file;
    int opcao;

    file = fopen("clientes.dat", "rb+");
    if (file == NULL) {
        file = fopen("clientes.dat", "wb+");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 1;
        }
    }

    do {
        printf("\nMenu:\n");
        printf("1 - Marcar a consulta\n");
        printf("2 - Desmarcar a consulta\n");
        printf("3 - Escrever mapa de horarios para um determinado dia\n");
        printf("4 - Escrever o nome e as datas em que um paciente foi consultado\n");
        printf("5 - Escrever nome e telefone de pacientes inativos (mais de 6 meses e idade superior a 50 anos)\n");
        printf("6 - Fim\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                marcarConsulta(file);
                break;
            case 2:
                desmarcarConsulta(file);
                break;
            case 3:
                escreverMapaHorarios(file);
                break;
            case 4:
                escreverConsultasPaciente(file);
                break;
            case 5:
                listarPacientesInativos(file);
                break;
            case 6:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 6);

    fclose(file);
    return 0;
}

void marcarConsulta(FILE *file) {
    Cliente cliente;
    int codigo, encontrado = 0;
    struct tm consulta;

    printf("Informe o codigo do cliente: ");
    scanf("%d", &codigo);

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        if (cliente.codigo == codigo) {
            encontrado = 1;
            printf("Informe a data da consulta (dd mm aaaa): ");
            scanf("%d %d %d", &consulta.tm_mday, &consulta.tm_mon, &consulta.tm_year);
            consulta.tm_mon -= 1;
            consulta.tm_year -= 1900;
            cliente.ultimaConsulta = consulta;

            fseek(file, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, file);
            printf("Consulta marcada com sucesso para %02d/%02d/%04d.\n",
                   cliente.ultimaConsulta.tm_mday,
                   cliente.ultimaConsulta.tm_mon + 1,
                   cliente.ultimaConsulta.tm_year + 1900);
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void desmarcarConsulta(FILE *file) {
    Cliente cliente;
    int codigo, encontrado = 0;

    printf("Informe o codigo do cliente: ");
    scanf("%d", &codigo);

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        if (cliente.codigo == codigo) {
            encontrado = 1;
            memset(&cliente.ultimaConsulta, 0, sizeof(struct tm));

            fseek(file, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, file);
            printf("Consulta desmarcada com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void escreverMapaHorarios(FILE *file) {
    Cliente cliente;
    struct tm data;
    int encontrado = 0;

    printf("Informe a data (dd mm aaaa): ");
    scanf("%d %d %d", &data.tm_mday, &data.tm_mon, &data.tm_year);
    data.tm_mon -= 1;
    data.tm_year -= 1900;

    rewind(file);
    printf("Consultas marcadas para %02d/%02d/%04d:\n", data.tm_mday, data.tm_mon + 1, data.tm_year + 1900);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        if (cliente.ultimaConsulta.tm_mday == data.tm_mday &&
            cliente.ultimaConsulta.tm_mon == data.tm_mon &&
            cliente.ultimaConsulta.tm_year == data.tm_year) {
            printf("Cliente: %s, Telefone: %s\n", cliente.nome, cliente.telefone);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhuma consulta marcada para essa data.\n");
    }
}

void escreverConsultasPaciente(FILE *file) {
    Cliente cliente;
    int codigo, encontrado = 0;

    printf("Informe o codigo do cliente: ");
    scanf("%d", &codigo);

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        if (cliente.codigo == codigo) {
            encontrado = 1;
            printf("Nome: %s, Data da ultima consulta: %02d/%02d/%04d\n",
                   cliente.nome,
                   cliente.ultimaConsulta.tm_mday,
                   cliente.ultimaConsulta.tm_mon + 1,
                   cliente.ultimaConsulta.tm_year + 1900);
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void listarPacientesInativos(FILE *file) {
    Cliente cliente;
    time_t t = time(NULL);
    struct tm *dataAtual = localtime(&t);
    int mesesInatividade;

    rewind(file);
    printf("Pacientes inativos (mais de 6 meses e idade superior a 50 anos):\n");
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        if (cliente.idade > 50) {
            mesesInatividade = (dataAtual->tm_year - cliente.ultimaConsulta.tm_year) * 12 + (dataAtual->tm_mon - cliente.ultimaConsulta.tm_mon);
            if (mesesInatividade > 6) {
                printf("Nome: %s, Telefone: %s\n", cliente.nome, cliente.telefone);
            }
        }
    }
}
