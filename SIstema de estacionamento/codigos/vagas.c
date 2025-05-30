#include <stdio.h>
#include <stdlib.h>
#include "vagas.h"
#include "cliente.h"
#include "interface.h"



FILE *fpvaga;
void AbrirVaga()
{
    fpvaga = fopen ("vagas.txt", "ab+");
    if(fpvaga == NULL)
    {
        printf("nao abriu Produto.txt!\n");
        exit(1);
    }
}
void FecharVaga()
{
    fclose (fpvaga);
}

void listarVagas()
{
    textcolor(WHITE);
    textbackground(BLACK);
    system("cls");
    AbrirVaga();
    fseek(fpvaga, 0, SEEK_SET);
    textcolor(BLACK);
    textbackground(WHITE);
    char Dados[120][120];
    Vaga P;
    int j, escolha = 0;
    char stringDataEntrada[11];
    char stringHoraEntrada[10];
    for (j = 0; j < 100; j++)
    {
        sprintf(Dados[j], "%-10d %-2s", j + 1, "--");
    }

    while (fread(&P, sizeof(Vaga), 1, fpvaga))
    {
        for (j = 0; j < 100; j++)
        {
            if (P.NumeroVaga == j + 1)
            {
                converterIntData(P.DataEntrada, stringDataEntrada);
                converterIntHora(P.HoraEntrada, stringHoraEntrada);
                sprintf(Dados[j], "%-7d %-10s %-16s %-16s %-8s", P.NumeroVaga, P.Placa, stringDataEntrada, stringHoraEntrada, "Ocupada");
            }
        }
    }

    Borda(1, 1, 80, 25, 1, 1);
    gotoxy(30, 2);
    printf("LISTA DE VAGAS");
    gotoxy(3, 4);
    printf("%-7s %-10s %-16s %-16s %-8s", "Vaga", "Placa", "Data de Entrada", "Hora de Entrada", "Status");

    Selecao(Dados, 100, 3, 5, 75, 20, escolha);

    textcolor(WHITE);
    textbackground(BLACK);
    system("cls");

    FecharVaga();
}

void InserirVaga (Vaga P)
{
    fseek(fpvaga, 0, SEEK_END);
    fwrite(&P, sizeof(Vaga),1, fpvaga);
    fflush(fpvaga);

}
int VerificarVagaOcupada(int numeroVaga)
{
    Vaga P;
    fseek(fpvaga, 0, SEEK_SET);
    while (fread(&P, sizeof(Vaga), 1, fpvaga))
    {
        if (P.NumeroVaga == numeroVaga)
        {
            return 1;
        }
    }
    return 0;
}
Vaga DigitarVaga(int *status)
{
    textcolor(BLACK);
    textbackground(WHITE);
    Vaga P;
    char Entrada [1000];
    int Tecla, Atual = 0;
    int primeiroNumero = 0;
    int segundoNumero = 0;
    int terceiroNumero = 0;

    P.NumeroVaga = 0;
    P.Placa [0]=0;
    P.DataEntrada = 0;
    P.HoraEntrada = 0;
    P.DataSaida = 0;
    P.HoraSaida = 0;
    do
    {
        if (Atual == 0)
        {
            sprintf(Entrada, "%d", P.NumeroVaga);
             if (P.NumeroVaga == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados(17, 5, 3, Entrada);
            P.NumeroVaga = atoi(Entrada);
            if (VerificarVagaOcupada(P.NumeroVaga))
            {
                gotoxy(6, 18);
                printf("Vaga ocupada. Escolha outra vaga.");
                gotoxy(6, 19);
                system("pause");
                *status = 0;
                return P;
            }
        }
        if (Atual == 1)
            Tecla = EntradaDados (17,8,8, P.Placa);
        if (Atual == 2)
        {
            gotoxy(19, 11);
            printf("/");
            gotoxy(22, 11);
            printf("/");
            sprintf (Entrada, "%d", P.DataEntrada/1000000);
            if (P.DataEntrada / 1000000 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (17,11,2, Entrada);
            primeiroNumero = atoi(Entrada);


            sprintf (Entrada, "%d",(P.DataEntrada / 10000) % 100);
            if ((P.DataEntrada - P.DataEntrada /1000000)/10000 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (20,11,2, Entrada);
            segundoNumero = atoi(Entrada);

            sprintf (Entrada, "%d", P.DataEntrada%10000);
            if (P.DataEntrada % 10000 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (23,11,5, Entrada);
            terceiroNumero = atoi(Entrada);
            P.DataEntrada = (primeiroNumero*1000000)+(segundoNumero*10000)+terceiroNumero;
        }
        if (Atual == 3)
        {
            gotoxy(19, 14);
            printf(":");

            sprintf(Entrada, "%d", P.HoraEntrada/100);
            if (P.HoraEntrada / 100 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (17,14,2, Entrada);
            primeiroNumero = atoi(Entrada);

            sprintf(Entrada, "%d", P.HoraEntrada%100);
            if (P.HoraEntrada % 100 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (20,14,2, Entrada);
            segundoNumero = atoi(Entrada);
            P.HoraEntrada  = (primeiroNumero*100)+segundoNumero;
        }
        if (Tecla == TEC_ENTER || Tecla == TEC_BAIXO)Atual++;
        if (Tecla == TEC_CIMA) Atual --;
        if (Atual > 3 && Tecla == TEC_BAIXO) Atual = 0;
        if (Atual > 3 && Tecla == TEC_ENTER) break;
    }
    while(Tecla != TEC_ESC);
    if (Tecla == TEC_ESC)
    {
        *status = 0;
        gotoxy(6, 18);
        printf("Operacao cancelada pelo usuario.");
        gotoxy(6, 19);
        system("pause");
    }
    else
    {
        *status = 1;
    }
    return P;
}
void TelaVaga ()
{
    textcolor(BLACK);
    textbackground(WHITE);
    Borda(1,1,66,23,0,1);
    gotoxy(17,2);
    printf("CADASTRO/CONSULTA DE VAGAS");
    gotoxy (4,5);
    printf ("NumeroVaga:");
    Borda (16,4,10,2,0,0);
    gotoxy (4,8);
    printf ("   Placa:");
    Borda (16,7,40,2,0,0);
    gotoxy (4,11);
    printf ("DataEntrada:");
    Borda (16,10,40,2,0,0);
    gotoxy (4,14);
    printf ("HoraEntrada:");
    Borda (16,13,40,2,0,0);

    textcolor(WHITE);
    textbackground(BLACK);
}

void menuvagas()
{
    textcolor(WHITE);
    textbackground(BLACK);
    system ("cls");
    int opcao, Codigo, i, status;
    Vaga P;
    do
    {
        TelaVaga();
        textcolor(BLACK);
        textbackground(WHITE);
        char opcoes [][20]= {"Cadastrar Vaga", "Consultar Vagas", "Voltar"};
        int x []= {9, 27, 45};
        int y []= {21, 21, 21};
        int tam [] = {15, 15, 9};
        opcao = 0;
        opcao = Menu(opcoes,x,y,tam,3,opcao);

        if(opcao == 0)
        {
            AbrirVaga();

            P = DigitarVaga(&status);
            if (status == 1)
            {
                InserirVaga(P);
                gotoxy(7, 19);
                printf("Vaga cadastrada com sucesso!");
                gotoxy(7, 20);
                system ("pause");



            }
            FecharVaga();

        }
        if(opcao == 1)
        {

            listarVagas();

        }
        textcolor(WHITE);
        textbackground(BLACK);

    }


    while (opcao != 2);
    FecharVaga();
    system("cls");
}
