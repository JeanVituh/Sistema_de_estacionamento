#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "interface.h"
#include "vagas.h"
#include "historico.h"
#include <conio.h>
#include "planos.h"
int PesquisarVaga(char Placa[], Vaga *P)
{
    FILE *fpler = fopen("vagas.txt", "rb");
    if (fpler == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    fseek(fpler, 0, SEEK_SET);
    while(fread(P, sizeof(Vaga),1, fpler))
    {
        if( strcmp(P -> Placa, Placa) ==0)
        {
            fclose(fpler);
            return 1;
        }
    }
    fclose (fpler);
    return 0;

}
int AlterarVaga (Vaga P)
{
    FILE *fp = fopen("vagas.txt", "rb+");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura/escrita.\n");
        return 0;
    }
    Vaga PA; // P antigo
    fseek (fp, 0, SEEK_SET);
    while(fread(&PA, sizeof(Vaga),1, fp))
    {
        if  (strcmp (PA.Placa,P.Placa) == 0)
        {
            fseek(fp, -sizeof(Vaga), SEEK_CUR);
            fwrite (&P, sizeof(Vaga), 1, fp);
            fflush(fp);
            fclose (fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
void ResetarVaga(char Placa[])//trocar excluir por alterar
{
    textcolor(BLACK);
    textbackground(WHITE);
    FILE *fpler = fopen("vagas.txt", "rb+");
    if (fpler == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura/escrita.\n");
        return 0;
    }
    FILE *tmp2 = fopen("temp.txt", "wb");
    if (tmp2 == NULL)
    {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(tmp2);
        return;
    }
    Vaga P;
    while (fread(&P, sizeof(Vaga), 1, fpler))
    {
        if ( strcmp(P.Placa, Placa) !=0)
        {
            fwrite(&P, sizeof(Vaga), 1, tmp2);
        }
    }
    fclose(fpler);
    fclose(tmp2);
    remove("vagas.txt");
    rename("temp.txt", "vagas.txt");
    gotoxy(6, 20);
    printf("vaga com codigo %s foi resetada com sucesso.\n", Placa);
}
void TelaSaida ()
{
    textcolor(BLACK);
    textbackground(WHITE);
    Borda(1,1,66,27,0,1);
    gotoxy(24,2);
    printf("CADASTRO DE SAIDA");
    gotoxy (4,5);
    printf ("   Placa:");
    Borda (16,4,10,2,0,0);
    gotoxy (4,8);
    printf ("NumeroVaga:");
    Borda (16,7,40,2,0,0);
    gotoxy (4,11);
    printf ("DataEntrada:");
    Borda (16,10,40,2,0,0);
    gotoxy (4,14);
    printf ("HoraEntrada:");
    Borda (16,13,40,2,0,0);
    gotoxy (4,17);
    printf ("DataSaida:");
    Borda (16,16,40,2,0,0);
    gotoxy (4,20);
    printf ("HoraSaida:");
    Borda (16,19,40,2,0,0);

    textcolor(WHITE);
    textbackground(BLACK);
}
Vaga DigitarSaida(int *status, Vaga P)
{
    textcolor(BLACK);
    textbackground(WHITE);
    char Entrada [1000];
    int Tecla, Atual = 0;
    int primeiroNumero = 0;
    int segundoNumero = 0;
    int terceiroNumero = 0;
    do
    {



        if (Atual == 0)
        {

            gotoxy(19, 17);
            printf("/");
            gotoxy(22, 17);
            printf("/");
            sprintf (Entrada, "%d", P.DataSaida/1000000);
            if (P.DataSaida / 1000000 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (17,17,2, Entrada);
            primeiroNumero = atoi(Entrada);


            sprintf (Entrada, "%d",(P.DataSaida / 10000) % 100);
            if ((P.DataSaida - P.DataSaida /1000000)/10000 == 0)
                if ((P.DataSaida / 10000) % 100 ==0)
                    Entrada [0] = 0;
            Tecla = EntradaDados (20,17,2, Entrada);
            segundoNumero = atoi(Entrada);

            sprintf (Entrada, "%d", P.DataSaida%10000);
            if (P.DataSaida == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (23,17,5, Entrada);
            terceiroNumero = atoi(Entrada);
            P.DataSaida = (primeiroNumero*1000000)+(segundoNumero*10000)+terceiroNumero;
        }
        if (Atual == 1)
        {
            gotoxy(19, 20);
            printf(":");

            sprintf(Entrada, "%d", P.HoraSaida/100);
            if (P.HoraSaida / 100 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (17,20,2, Entrada);
            primeiroNumero = atoi(Entrada);

            sprintf(Entrada, "%d", P.HoraSaida%100);
            if (P.HoraSaida % 100 == 0)
                Entrada [0] = 0;
            Tecla = EntradaDados (20,20,2, Entrada);
            segundoNumero = atoi(Entrada);
            P.HoraSaida  = (primeiroNumero*100)+segundoNumero;
        }
        if (Tecla == TEC_ENTER || Tecla == TEC_BAIXO)Atual++;
        if (Tecla == TEC_CIMA) Atual --;
        if (Atual < 0) Atual = 0;
        if (Atual >1) break;
    }
    while(Tecla != TEC_ESC);
    if (Tecla == TEC_ESC)
    {
        *status = 0;
    }
    else
    {
        *status = 1;
    }

    return P;
}

void ImprimirInfoVaga(Vaga P)
{
    char entrada[100];

    textcolor(BLACK);
    textbackground(WHITE);
    gotoxy (17,5);
    printf("%s", P.Placa);
    gotoxy (17,8);
    printf("%d", P.NumeroVaga );
    gotoxy (17,11);
    converterIntData(P.DataEntrada, entrada);
    printf("%s", entrada);
    gotoxy (17,14);
    converterIntHora(P.HoraEntrada, entrada);
    printf("%s", entrada);
    gotoxy (17,17);



}
void registrarHistorico(Vaga P, double valor)
{
    AbrirHistorico();
    fwrite(&P, sizeof(Vaga), 1, fphistorico);
    FecharHistorico();
}


void menuSaida()
{
    textcolor(WHITE);
    textbackground(BLACK);
    system("cls");
    TelaSaida();
    int Tecla, i, status, opcao;
    char Placa[9];
    Vaga P;
    Cliente C;
    int ultimaDataCobranca = 0; // Variável para armazenar a última data de cobrança

    do
    {
        TelaSaida();
        textcolor(BLACK);
        textbackground(WHITE);
        char opcoes[][20] = {"Digitar Placa", "Voltar"};
        int x[] = {17, 35};
        int y[] = {25, 25};
        int tam[] = {15, 9};
        opcao = 0;
        opcao = Menu(opcoes, x, y, tam, 2, opcao);

        if (opcao == 0)
        {
            gotoxy(7, 3);
            printf("Digite a placa para informar a saida:                        ");
            gotoxy(17, 5);
            int pos = 0;
            int cancelado = 0;  // Flag para verificar se a operação foi cancelada
            while ((Tecla = getch()) != '\r')  // Loop para capturar cada caractere até Enter ser pressionado
            {
                if (Tecla == TEC_ESC)
                {
                    cancelado = 1;  // Marca a operação como cancelada
                    gotoxy(30, 5);
                    printf("Operacao cancelada pelo usuario.");
                    gotoxy(6, 23);
                    system("pause");
                    break;
                }
                else if (Tecla == TEC_BACKSPACE && pos > 0)
                {
                    pos--;
                    Placa[pos] = '\0';
                    printf("\b \b");  // Remove o último caractere da tela
                }
                else if (pos < sizeof(Placa) - 1)
                {
                    Placa[pos++] = Tecla;
                    putchar(Tecla);  // Exibe o caractere na tela
                }
            }
            Placa[pos] = '\0';  // Termina a string

            if (!cancelado)
            {
                if (PesquisarVaga(Placa, &P)) // Remove a necessidade de PesquisarCliente
                {
                    gotoxy(7, 3);
                    printf("Vaga encontrada! Digite a data e a hora de saida:\n");
                    ImprimirInfoVaga(P);
                    P = DigitarSaida(&status, P);
                    if (AlterarVaga(P))
                    {
                        gotoxy(7, 23);
                        printf("Saida registrada com sucesso!\n");
                        gotoxy(7, 24);
                        system("pause");

                        double valor = calcularValorEstacionamento(C, P, ultimaDataCobranca);
                        registrarHistorico(P, valor);
                        ultimaDataCobranca = P.DataSaida; // Atualiza a última data de cobrança
                        ResetarVaga(P.Placa);
                    }
                    else
                    {
                        gotoxy(10, 24);
                        printf("Erro ao alterar a vaga.\n");
                        gotoxy(10, 25);
                        system("pause");
                    }
                }
                else
                {
                    gotoxy(7, 23);
                    printf("Placa nao encontrada!\n");
                    gotoxy(7, 24);
                    system("pause");
                }
            }
        }
    } while (opcao != 1);
    FecharVaga();
    textcolor(WHITE);
    textbackground(BLACK);
}
