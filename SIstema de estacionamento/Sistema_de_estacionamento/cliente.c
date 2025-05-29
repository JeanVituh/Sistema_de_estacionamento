#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "interface.h"
#include "vagas.h"
FILE *fpcliente;
void Abrircliente()
{
    fpcliente = fopen("cliente.txt", "ab+");
    if(fpcliente == NULL)
    {
        printf("nao abriu cliente.txt!\n");
        exit(1);
    }
}
void Fecharcliente()
{
    fclose (fpcliente);
}
void InserirCliente(Cliente P)
{
    fseek(fpcliente, 0, SEEK_END);
    fwrite(&P, sizeof(Cliente),1, fpcliente);
    fflush(fpcliente);

}


/*Cliente Produtos[100];
int qtdprodutos = 0; */
void excluirCliente(int Codigo)
{
       textcolor(BLACK);
       textbackground(WHITE);
    FILE *fp = fopen("cliente.txt", "rb+");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura/escrita.\n");
        return;
    }
    FILE *tmp = fopen("temp.txt", "wb");
    if (tmp == NULL)
    {
        printf("Erro ao criar arquivo tempor�rio.\n");
        fclose(fp);
        return;
    }
    Cliente P;
    while (fread(&P, sizeof(Cliente), 1, fp))
    {
        if (P.codigo != Codigo)
        {
            fwrite(&P, sizeof(Cliente), 1, tmp);
        }
    }
    fclose(fp);
    fclose(tmp);
    remove("cliente.txt");
    rename("temp.txt", "cliente.txt");
    gotoxy(6, 21);
    printf("Cliente com codigo %d foi excluido com sucesso.\n", Codigo);
}





void telacliente ()
{
    textcolor(BLACK);
    textbackground(WHITE);
    Borda(1,1,66,25,0,1);
    gotoxy(17,2);
    printf("CADASTRO/CONSULTA DE CLIENTES");
    gotoxy (4,7);
    printf ("   Codigo:");
    Borda (15,6,10,2,0,0);
    gotoxy (4,10);
    printf ("    Nome:");
    Borda (15,9,40,2,0,0);
    gotoxy (4,12);
    printf ("  Modelo\n");
    gotoxy (4,13);
    printf ("  veiculo:");
    Borda (15,12,40,2,0,0);
    gotoxy (4,16);
    printf ("   placa:");
    Borda (15,15,15,2,0,0);
    gotoxy (4,19);
    printf ("   plano:");
    Borda (15,18,40,2,0,0);
}
int MaxCodigo() {
    fseek(fpcliente, 0, SEEK_SET);
    Cliente P;
    int maxcodigo = 0;

    while (fread(&P, sizeof(Cliente), 1, fpcliente)) {
        if (P.codigo > maxcodigo) {
            maxcodigo = P.codigo;
        }
    }

    return maxcodigo;
}

int ClienteCodigo()
{
    fseek(fpcliente, 0, SEEK_SET);
    Cliente P;
    int codigo = 1; // Inicia com o menor c�digo poss�vel

    while (1)
    {
        int encontrado = 0; // Usar uma vari�vel para verificar se o c�digo j� existe

        fseek(fpcliente, 0, SEEK_SET); // Voltar ao in�cio do arquivo para verificar todos os c�digos



        while (fread(&P, sizeof(Cliente), 1, fpcliente))
        {
            if (P.codigo == codigo)
            {
                encontrado = 1;
                break; // Se o c�digo for encontrado, interromper o loop interno
            }
        }

        if (encontrado != 1)
        {
         return codigo;

        }


        codigo++;
    }
}
Cliente DigitarClientealterado(Cliente P, int *status)
{
    FILE *fp = fopen("cliente.txt", "rb+");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura/escrita.\n");
        return;
    }
    textcolor(BLACK);
    textbackground(WHITE);
    char Entrada [1000];
    int Tecla, Atual = 0;
    gotoxy(16, 7);
    printf("%d",P.codigo);
    do
    {
        if (Atual == 0)
            Tecla = EntradaDados (16,10,30, P.Nome);
        if (Atual == 1)
            Tecla = EntradaDados (16,13,30, P.ModeloVeiculo);
        if (Atual == 2)
            Tecla = EntradaDados (16,16,9, P.Placa);
        if (Atual == 3)
            Tecla = EntradaDados (16,19,30, P.Plano);
        if (Tecla == TEC_ENTER || Tecla == TEC_BAIXO)Atual++;
        if (Tecla == TEC_CIMA) Atual--;
   if (Atual > 3 && Tecla == TEC_BAIXO) Atual = 0;
        if (Atual > 3 && Tecla == TEC_ENTER) break;


    }while(Tecla != TEC_ESC);
    if (Tecla == TEC_ESC)
    {
        *status = 0;
    }
    else
    {
        *status = 1;
    }
    fclose(fp);
    return P;
}

Cliente DigitarCliente(int *status)
{
   textcolor(BLACK);
    textbackground(WHITE);
    Cliente P;
    char Entrada [1000];
    int Tecla, Atual = 0;
    P.codigo = ClienteCodigo();
    P.Nome [0]= 0;
    P.ModeloVeiculo [0]=0;
    P.Placa [0]=0;
    P.Plano [0]= 0;
    do
    {

            gotoxy(16, 7); printf("%d", P.codigo);

        if (Atual == 0)
            Tecla = EntradaDados (16,10,30, P.Nome);
        if (Atual == 1)
            Tecla = EntradaDados (16,13,30, P.ModeloVeiculo);
        if (Atual == 2)
            Tecla = EntradaDados (16,16,9, P.Placa);
        if (Atual == 3)
            Tecla = EntradaDados (16,19,30, P.Plano);
        if (Tecla == TEC_ENTER || Tecla == TEC_BAIXO)Atual++;
        if (Tecla == TEC_CIMA) Atual --;
        if (Atual < 0) Atual = 3;
        if (Atual > 3 && Tecla == TEC_BAIXO) Atual = 0;
        if (Atual > 3 && Tecla == TEC_ENTER) break;
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


/*gotoxy (19,6);
scanf("%d", &P.codigo);
gotoxy (19,9);
scanf(" %[^\n]", &P.Nome);
gotoxy (19,12);
scanf(" %[^\n]", &P.ModeloVeiculo);
gotoxy (19,15);
scanf("%s", &P.Placa);
gotoxy (19,18);
scanf(" %[^\n]", &P.Plano);
printf("\n\n\n");
return P;}*/

int PesquisarCliente(int Codigo, Cliente *P)
{
    FILE *fp = fopen("cliente.txt", "rb");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    fseek(fp, 0, SEEK_SET);
    while(fread(P, sizeof(Cliente),1, fp))
    {
        if( P -> codigo ==Codigo)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose (fp);
    return 0;

}

int AlterarCliente (Cliente P)
{
    FILE *fp = fopen("cliente.txt", "rb+");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura/escrita.\n");
        return 0;
    }
    Cliente PA; // P antigo
    fseek (fp, 0, SEEK_SET);
    while(fread(&PA, sizeof(Cliente),1, fp))
    {
        if  (PA.codigo == P.codigo)
        {
            fseek(fp, -sizeof(Cliente), SEEK_CUR);
            fwrite (&P, sizeof(Cliente), 1, fp);
            fflush(fp);
            fclose (fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void ImprimirCliente(Cliente P)
{
    gotoxy (16,7);
    printf("%d", P.codigo);
    gotoxy (16,10);
    printf("%s", P.Nome);
    gotoxy (16,13);
    printf("%s", P.ModeloVeiculo);
    gotoxy (16,16);
    printf("%s", P.Placa);
    gotoxy (16,19);
    printf("%s", P.Plano);

}
void listarCliente ()
{
     textcolor(WHITE);
    textbackground(BLACK);
    system ("cls");
    Abrircliente();
    fseek(fpcliente, 0, SEEK_SET);
   textcolor(BLACK);
    textbackground(WHITE);
    char Dados[120][120];
    Cliente P;
    int j =0,  escolha=0;
     while (fread(&P, sizeof(Cliente), 1, fpcliente))
    {
        for (j = 0; j < 1000; j++)
        {
            if (P.codigo == j + 1)
            {
                sprintf (Dados[j], "%03d %-30s %-18s %-10s %-16s",P.codigo, P.Nome,P.ModeloVeiculo, P.Placa, P.Plano);
            }
        }
    }
    //while(fread(&P, sizeof(Cliente),1, fpcliente))
   // {
    //    sprintf (Dados[i], "%03d %-30s %-18s %-10s %-15s",P.codigo, P.Nome,P.ModeloVeiculo, P.Placa, P.Plano);
   //     i++;
   // }

    Borda (1,1,100,25,1,1);
    gotoxy(38,2);
    printf("%s", "LISTA DE CLIENTES");
    gotoxy (3,4);
    printf("%-3s %-30s %-18s %-10s %-16s", "Cod", "Nome Completo", "Modelo Veiculo", "Placa", "Plano");


    Selecao (Dados, MaxCodigo(), 3,5,80,20, escolha);


    textcolor(WHITE);
    textbackground(BLACK);
    Fecharcliente();

}


void menucliente()
{
    textcolor(WHITE);
    textbackground(BLACK);
    system("cls");
    int opcao = 0, Codigo, i, status;
    Cliente P;
    do
    {
        telacliente();
        textcolor(BLACK);
        textbackground(WHITE);
        char opcoes[][20] = {"Novo", "Pesquisa", "Alterar", "Excluir", "Listar", "Voltar"};
        int x[] = {2, 13, 24, 35, 46, 57};
        int y[] = {23, 23, 23, 23, 23, 23};
        int tam[] = {9, 9, 9, 9, 9, 9};
        opcao = Menu(opcoes, x, y, tam, 6, opcao);

        if (opcao == 0)
        {
            Abrircliente();

            gotoxy(7, 4);
            printf("Digite os dados do cliente: ");
            P = DigitarCliente(&status);
            if (status == 1)
            {
                InserirCliente(P);
                gotoxy(6, 21);
                printf("Cliente cadastrado com sucesso!");
                gotoxy(6, 22);
                system("pause");
            }
            Fecharcliente();
        }
        if (opcao == 1)
        {
            gotoxy(7, 4);
            printf("Digite o codigo do cliente a ser pesquisado: ");
            gotoxy(16, 7);
            int Tecla, numero = 0, pos = 0;
            char buffer[20] = {0};  // Buffer para armazenar a entrada como string
            int cancelado = 0;  // Flag para verificar se a opera��o foi cancelada
            while ((Tecla = getch()) != '\r')
            {
                if (Tecla == TEC_ESC)
                {
                    cancelado = 1;  // Marca a opera��o como cancelada
                    gotoxy(28, 7);
                    printf("Operacao cancelada pelo usuario.");
                    gotoxy(6, 22);
                    system("pause");
                    break;
                }
                if (Tecla >= '0' && Tecla <= '9')
                {
                    if (pos < sizeof(buffer) - 1) {
                        buffer[pos++] =Tecla;  // Armazena o caractere no buffer
                        putchar(Tecla);  // Exibe o caractere na tela
                        numero = numero * 10 + (Tecla - '0');
                    }
                }
                else if (Tecla == TEC_BACKSPACE && pos > 0)
                {
                    pos--;  // Diminui a posi��o
                    buffer[pos] = 0;  // Remove o �ltimo caractere no buffer
                    printf("\b \b");  // Remove o �ltimo caractere da tela
                    numero = 0;  // Recalcula o n�mero
                    for (int i = 0; i < pos; i++) {
                        numero = numero * 10 + (buffer[i] - '0');
                    }
                }
                else
                {
                    gotoxy(6, 21);
                    printf("Caractere invalido. Digite apenas numeros.");
                    gotoxy(6, 22);
                    system("pause");
                    numero = -1;  // Define o n�mero como inv�lido
                    break;
                }
            }
            Codigo = numero;
            if (!cancelado && Codigo != -1)
            {
                if (PesquisarCliente(Codigo, &P))
                {
                    ImprimirCliente(P);
                    gotoxy(6, 21);
                    printf("Cliente encontrado!");
                }
                else
                {
                    gotoxy(28, 7);
                    printf("Codigo nao encontrado");
                }
                gotoxy(6, 22);
                system("pause");
            }
        }
        if (opcao == 2)
        {
            gotoxy(7, 4);
            printf("Digite o codigo do cliente a ser alterado: ");
            gotoxy(16, 7);
            int Tecla, numero = 0, pos = 0;
            char buffer[20] = {0};  // Buffer para armazenar a entrada como string
            int cancelado = 0;  // Flag para verificar se a opera��o foi cancelada
            while ((Tecla = getch()) != '\r')
            {
                if (Tecla == TEC_ESC)
                {
                    cancelado = 1;  // Marca a opera��o como cancelada
                    gotoxy(28, 7);
                    printf("Operacao cancelada pelo usuario.");
                    gotoxy(6, 22);
                    system("pause");
                    break;
                }
                if (Tecla >= '0' && Tecla <= '9')
                {
                    if (pos < sizeof(buffer) - 1) {
                        buffer[pos++] = Tecla;  // Armazena o caractere no buffer
                        putchar(Tecla);  // Exibe o caractere na tela
                        numero = numero * 10 + (Tecla- '0');
                    }
                }
                else if (Tecla == TEC_BACKSPACE && pos > 0)
                {
                    pos--;  // Diminui a posi��o
                    buffer[pos] = 0;  // Remove o �ltimo caractere no buffer
                    printf("\b \b");  // Remove o �ltimo caractere da tela
                    numero = 0;  // Recalcula o n�mero
                    for (int i = 0; i < pos; i++) {
                        numero = numero * 10 + (buffer[i] - '0');
                    }
                }
                else
                {
                    gotoxy(6, 21);
                    printf("Caractere invalido. Digite apenas numeros.");
                    gotoxy(6, 22);
                    system("pause");
                    numero = -1;  // Define o n�mero como inv�lido
                    break;
                }
            }
            Codigo = numero;
            if (!cancelado && Codigo != -1)
            {
                if (PesquisarCliente(Codigo, &P))
                {
                    ImprimirCliente(P);
                    P = DigitarClientealterado(P, &status);
                    if (status == 1 && AlterarCliente(P))
                    {
                        gotoxy(6, 21);
                        printf("Cliente alterado com sucesso!");
                        gotoxy(6, 22);
                        system("pause");
                    }
                }
                else
                {
                    gotoxy(28, 7);
                    printf("Codigo nao encontrado.");
                    gotoxy(6, 22);
                    system("pause");
                }
            }
        }
        if (opcao == 3)
        {
            gotoxy(7, 4);
            printf("Digite o codigo do cliente que deseja excluir: ");
            gotoxy(16, 7);
            int Tecla, numero = 0, pos = 0;
            char buffer[20] = {0};  // Buffer para armazenar a entrada como string
            int cancelado = 0;  // Flag para verificar se a opera��o foi cancelada
            while ((Tecla = getch()) != '\r')
            {
                if (Tecla == TEC_ESC)
                {
                    cancelado = 1;  // Marca a opera��o como cancelada
                    gotoxy(28, 7);
                    printf("Operacao cancelada pelo usuario.");
                    gotoxy(6, 22);
                    system("pause");
                    break;
                }
                if (Tecla >= '0' && Tecla <= '9')
                {
                    if (pos < sizeof(buffer) - 1) {
                        buffer[pos++] = Tecla;  // Armazena o caractere no buffer
                        putchar(Tecla);  // Exibe o caractere na tela
                        numero = numero * 10 + (Tecla - '0');
                    }
                }
                else if (Tecla == TEC_BACKSPACE && pos > 0)
                {
                    pos--;  // Diminui a posi��o
                    buffer[pos] = 0;  // Remove o �ltimo caractere no buffer
                    printf("\b \b");  // Remove o �ltimo caractere da tela
                    numero = 0;  // Recalcula o n�mero
                    for (int i = 0; i < pos; i++) {
                        numero = numero * 10 + (buffer[i] - '0');
                    }
                }
                else
                {
                    gotoxy(6, 21);
                    printf("Caractere invalido. Digite apenas numeros.");
                    gotoxy(6, 22);
                    system("pause");
                    numero = -1;  // Define o n�mero como inv�lido
                    break;
                }
            }
            Codigo = numero;
            if (!cancelado && Codigo != -1)
            {
                if (PesquisarCliente(Codigo, &P))
                {
                    ImprimirCliente(P);
                    excluirCliente(Codigo);
                }
                else
                {
                    gotoxy(28, 7);
                    printf("Codigo nao encontrado.");
                }
                textcolor(BLACK);
                textbackground(WHITE);
                gotoxy(6, 22);
                system("pause");
            }
        }
        if (opcao == 4)
        {
            listarCliente();
            system("cls");
            textcolor(WHITE);
            textbackground(BLACK);
        }
     textcolor(WHITE);
        textbackground(BLACK);

    } while (opcao != 5);
    Fecharcliente();
    system("cls");
}
