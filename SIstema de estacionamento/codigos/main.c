#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "interface.h"
#include "vagas.h"
#include "saida.h"
#include "planos.h"
#include "historico.h"
#include "cliente.h"


void TelaPrincipal()
{
    system("cls");
    textcolor(BLACK);
    textbackground(WHITE);
    Borda(1, 1, 70, 20, 1, 0);

    gotoxy(17, 8);  printf(" _  __      _       _           ");
    gotoxy(17, 9);  printf("| |/ / __ _| |_ ___| |__   __ _ _   _ ");
    gotoxy(17, 10); printf("| ' / / _` | __/ __| '_ \\ / _` | | | |");
    gotoxy(17, 11); printf("| . \\  (_| | || (__| | | | (_| | |_| |");
    gotoxy(17, 12); printf("|_|\\_\\ __,_|\\__\\___|_| |_|\\__,_|\\__,_|");
    gotoxy(18, 13); printf("  ____ ");
    gotoxy(18, 14); printf(" / ___|  __ _ _ __ __ _  __ _  ___  ");
    gotoxy(18, 15); printf("| |  _  / _` | '__/ _` |/ _` |/ _ \\ ");
    gotoxy(18, 16); printf("| |_| |  (_| | | | (_| | (_| |  __/ ");
    gotoxy(18, 17); printf(" \\____| \\__,_|_|  \\__,_|\\__, |\\___| ");
    gotoxy(18, 18); printf("                        |___/      ");

    gotoxy(23, 1);  printf("ESCOLHA A OPCAO DESEJADA:");
    gotoxy(30, 20); printf("versao 0.1");
}




int main()
{

    char opcoes [][20]= {"Cliente", "Vagas", "Saida", "Planos", "Historico"};
    int x[]= {5,17,29,41,53};
    int y[]= {3,3,3,3,3};
    int tam[]= {9,9,9,9,9};
    int opcao = 0;
    do
    {
        TelaPrincipal();
        opcao = Menu(opcoes,x,y,tam,5,0);
        if (opcao == 0)
        {
            menucliente();
        }
        else if (opcao ==1)
        {
           menuvagas();
        }
        else if (opcao ==2)
        {
            menuSaida();
            system ("Cls");
            printf ("\n\n");
        }
        else if (opcao ==3)
        {

        TelaPlano();
        }
        else if (opcao ==4)
        {

        menuHistorico();
        }
    }
    while (opcao != 5);
    {
        printf ("Ate a proxima!\n\n");
        return 0;
    }
}




