#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "interface.h"
#include "vagas.h"
#include <conio.h>
#include "planos.h"

FILE *fphistorico;

void AbrirHistorico()
{
    fphistorico = fopen ("historico.txt", "ab+");
    if(fphistorico == NULL)
    {
        printf("nao abriu o historico.txt!\n");
        exit(1);
    }
}

void FecharHistorico()
{
    fclose(fphistorico);
}

int PesquisarPlaca(char Placa[], Vaga *P)
{
    FILE *fpler = fopen("historico.txt", "rb");
    if (fpler == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    fseek(fpler, 0, SEEK_SET);
    while(fread(P, sizeof(Vaga), 1, fpler))
    {
        if( strcasecmp(P->Placa, Placa) == 0)
        {
            fclose(fpler);
            return 1;
        }
    }
    fclose(fpler);
    return 0;
}

void listarHistorico(char Placa[])
{
    FILE *fplerHist = fopen("historico.txt", "rb");
    if (fplerHist == NULL)
    {
        printf("Erro ao abrir o arquivo historico para leitura.\n");
        return;
    }
    FILE *fp = fopen("cliente.txt", "rb");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo cliente para leitura.\n");
        fclose(fplerHist);
        return;
    }

    fseek(fplerHist, 0, SEEK_SET);
    fseek(fp, 0, SEEK_SET);
    textcolor(BLACK);
    textbackground(WHITE);
    char Dados[120][120];
    Vaga P;
    Cliente C;
    int i = 0, escolha = 0;
    double valorTotal = 0.0;
    int ultimaDataCobranca = 0; // Variável para rastrear a última data de cobrança

    char stringHoraEntrada[11];
    char stringHoraSaida[11];
    char stringDataEntrada[11];
    char stringDataSaida[11];

    while (fread(&P, sizeof(Vaga), 1, fplerHist))
    {
        if (strcasecmp(Placa, P.Placa) == 0)
        {
            fseek(fp, 0, SEEK_SET); // Resetar a posição do fp para o início

            while (fread(&C, sizeof(Cliente), 1, fp))
            {
                if (strcasecmp(Placa, C.Placa) == 0)
                {
                    double valor = calcularValorEstacionamento(C, P, ultimaDataCobranca);
                    valorTotal += valor;

                    converterIntHora(P.HoraEntrada, stringHoraEntrada);
                    converterIntHora(P.HoraSaida, stringHoraSaida);
                    converterIntData(P.DataEntrada, stringDataEntrada);
                    converterIntData(P.DataSaida, stringDataSaida);

                    sprintf(Dados[i], "%-24s %-14s %-6d %-10s %-12s %-7s %-12s %-7s %-8.2lf",
                            C.Nome, C.Plano, P.NumeroVaga, P.Placa, stringDataEntrada, stringHoraEntrada, stringDataSaida, stringHoraSaida, valor);
                    i++;

                    // Atualizar a última data de cobrança
                    ultimaDataCobranca = P.DataSaida;
                    break;
                }
            }
        }
    }

    if (i == 0)
    {
        printf("Nenhuma informação encontrada para a placa: %s\n", Placa);
    }
    else
    {
        Borda(1, 1, 116, 25, 1, 1);
        gotoxy(45, 2);
        printf("HISTORICO PESSOAL DO CLIENTE");
        gotoxy(3, 4);
        printf("%-24s %-14s %-6s %-10s %-12s %-7s %-12s %-7s %-8s", "Nome", "Plano", "Vaga",
               "Placa", "Entrada", "Hora", "Saida", "Hora", "Valor");
        gotoxy(3, 23);
        printf("Valor total acumulado: R$ %.2lf", valorTotal);
        Selecao(Dados, i, 3, 6, 110, 20, escolha);



        textcolor(WHITE);
        textbackground(BLACK);
    }

    fclose(fplerHist);
    fclose(fp);
}

void TelaHistorico()
{
    textcolor(BLACK);
    textbackground(WHITE);
    Borda(1, 1, 66, 23, 0, 1);
    gotoxy(19, 2);
    printf("CONSULTAR HISTORICO PESSOAL");
    gotoxy(4, 8);
    printf("   Placa:");
    Borda(16, 7, 40, 2, 0, 0);

    textcolor(WHITE);
    textbackground(BLACK);
}

Vaga DigitarPlaca(int *status, Vaga P)
{
    textcolor(BLACK);
    textbackground(WHITE);
    char Entrada[1000];
    int Tecla, Atual = 0;
    do
    {
        Tecla = EntradaDados(17, 7, 9, P.Placa);
    }
    while(Tecla != TEC_ESC);
    if (Tecla == TEC_ESC)
    {
        *status = 0;
        gotoxy(28, 7);
        printf("Operacao cancelada pelo usuario.");
        gotoxy(6, 22);
        system("pause");
    }
    else
    {
        *status = 1;
    }
    return P;
}

void menuHistorico()
{
    int i, status, opcao;
    char Placa[9];
    Vaga P;
    do
    {
        textcolor(WHITE);
        textbackground(BLACK);
        system("cls");

        TelaHistorico();
        textcolor(BLACK);
        textbackground(WHITE);
        char opcoes[][20] = {"Digitar Placa", "Voltar"};
        int x[] = {20, 38};
        int y[] = {21, 21};
        int tam[] = {15, 9};
        opcao = 0;
        opcao = Menu(opcoes, x, y, tam, 2, opcao);

        if (opcao == 0)
        {
            int pos = 0;
            int cancelado = 0;
            gotoxy(7, 4);
            printf("Digite a placa para informar o historico:              ");
            gotoxy(17, 8);
            while (1)
            {
                int Tecla = getch();
                if (Tecla == TEC_ESC)
                {
                    cancelado = 1;
                    break;
                }
                else if (Tecla == '\r')
                {
                    Placa[pos] = '\0';
                    break;
                }
                else if (Tecla == TEC_BACKSPACE && pos > 0)
                {
                    pos--;
                    Placa[pos] = '\0';
                    printf("\b \b");
                }
                else if (pos < sizeof(Placa) - 1)
                {
                    Placa[pos++] = Tecla;
                    putchar(Tecla);
                }
            }
            if (cancelado)
            {
                gotoxy(7, 10);
                printf("Operacao cancelada pelo usuario.");
                gotoxy(7, 19);
                system("pause");
            }
            else
            {
                if (PesquisarPlaca(Placa, &P))
                {
                    gotoxy(7, 10);
                    printf("Placa encontrada! Imprimindo informacoes...\n");
                    gotoxy(7, 19);
                    system("pause");
                    listarHistorico(Placa);
                    textcolor(WHITE);
                    textbackground(BLACK);
                }
                else
                {
                    gotoxy(7, 10);
                    printf("Placa nao encontrada!\n");
                    gotoxy(7, 19);
                    system("pause");
                }
            }
        }
    } while (opcao != 1);
    FecharVaga();
    textcolor(WHITE);
    textbackground(BLACK);
}
