#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "interface.h"
#include <stdio.h>
#include "vagas.h"
#include <math.h>
#include "planos.h"

NomePlano planos[5] =
    {
        {"Noturno", "Acesso das 18:00 ate as 06:00", 150.0},
        {"24 Horas", "Acesso 24 horas por dia", 400.0},
        {"Diurno", "Acesso das 06:00 ate as 18:00", 120.0},
        {"familia anual", "Acesso completo 24h para ate 4 carros por familia", 7200.0}
    };
void TelaPlano ()
{
    textcolor(WHITE);
    textbackground(BLACK);
    system ("cls");
    textcolor(BLACK);
    textbackground(WHITE);
    Borda(1,1,66,25,0,1);
    gotoxy(20,3);
    printf("CONFIRA OS NOSSOS PLANOS:");

    for(int i = 0; i < 4; i++)
    {
        gotoxy(6,5 + 4 * i);
        printf("Plano: %s\n", planos[i].nome);
        gotoxy(6,6 + 4 * i);
        printf("Descricao: %s\n", planos[i].descricao);
        gotoxy(6,7 + 4 * i);
        printf("Preco: R$ %.2lf\n", planos[i].valor);
    }
    gotoxy(6,24);
    system ("pause");

    textcolor(WHITE);
    textbackground(BLACK);
}



// Função para calcular a diferença em meses entre duas datas no formato DDMMYYYY
int calcularMesesPassados(int dataInicio, int dataFim)
{
    int diaInicio = dataInicio / 1000000;
    int mesInicio = (dataInicio / 10000) % 100;
    int anoInicio = dataInicio % 10000;
    int diaFim = dataFim / 1000000;
    int mesFim = (dataFim / 10000) % 100;
    int anoFim = dataFim % 10000;

    int meses = (anoFim - anoInicio) * 12 + (mesFim - mesInicio);
    if (diaFim < diaInicio)
    {
        meses--;
    }

    return meses;
}

// Função para calcular a diferença em anos entre duas datas no formato DDMMYYYY
int calcularAnosPassados(int dataInicio, int dataFim)
{
    int anoInicio = dataInicio % 10000;
    int anoFim = dataFim % 10000;

    return anoFim - anoInicio;
}

double calcularValorEstacionamento(Cliente C, Vaga P, int ultimaDataCobranca)
{
    double valorFinal = 0.0;
    int minutosDentroPlano = 0, minutosForaPlano = 0;

    // Converte a hora de entrada e saída para minutos
    int entradaEmMinutos = (P.HoraEntrada / 100) * 60 + (P.HoraEntrada % 100);
    int saidaEmMinutos = (P.HoraSaida / 100) * 60 + (P.HoraSaida % 100);

    // Ajusta para o caso de passar da meia-noite
    if (saidaEmMinutos < entradaEmMinutos) {
        saidaEmMinutos += 24 * 60;
    }

    // Calcule a diferença total em minutos
    int minutosTotais = saidaEmMinutos - entradaEmMinutos;

    // Identifica o plano do cliente
    if (strcasecmp(C.Plano, "Noturno") == 0) {
        // Horário do plano: 18:00 às 06:00
        int inicioPlano = 18 * 60; // 18:00 em minutos
        int fimPlano = 6 * 60;    // 06:00 em minutos (no dia seguinte)

        for (int i = entradaEmMinutos; i < saidaEmMinutos; i++) {
            int horaAtual = i % (24 * 60); // Normaliza para o intervalo de 24 horas
            if ((horaAtual >= inicioPlano || horaAtual < fimPlano)) {
                minutosDentroPlano++;
            } else {
                minutosForaPlano++;
            }
        }

        // Adiciona horas do dia seguinte, se necessário
        if (P.DataSaida != P.DataEntrada) {
            for (int i = 0; i < saidaEmMinutos % (24 * 60); i++) {
                int horaAtual = i % (24 * 60);
                if ((horaAtual >= inicioPlano || horaAtual < fimPlano)) {
                    minutosDentroPlano++;
                } else {
                    minutosForaPlano++;
                }
            }
        }

        // Calcular o valor: minutos fora do plano * taxa por hora
        valorFinal = (minutosForaPlano / 60.0) * 20.0;

        // Correção da cobrança
        int mesesPassados = calcularMesesPassados(ultimaDataCobranca, P.DataSaida);

        if (ultimaDataCobranca == 0) {
            valorFinal += 150.0; // Cobrar o primeiro mês
        }
        else if (mesesPassados >= 1) {
            valorFinal += mesesPassados * 150.0; // Corrigir a cobrança para todos os meses passados
        }

    } else if (strcasecmp(C.Plano, "Diurno") == 0) {
        // Horário do plano: 06:00 às 18:00
        int inicioPlano = 6 * 60; // 06:00 em minutos
        int fimPlano = 18 * 60;  // 18:00 em minutos

        for (int i = entradaEmMinutos; i < saidaEmMinutos; i++) {
            int horaAtual = i % (24 * 60); // Normaliza para o intervalo de 24 horas
            if (horaAtual >= inicioPlano && horaAtual < fimPlano) {
                minutosDentroPlano++;
            } else {
                minutosForaPlano++;
            }
        }

        // Adiciona horas do dia seguinte, se necessário
        if (P.DataSaida != P.DataEntrada) {
            for (int i = 0; i < saidaEmMinutos % (24 * 60); i++) {
                int horaAtual = i % (24 * 60);
                if (horaAtual >= inicioPlano && horaAtual < fimPlano) {
                    minutosDentroPlano++;
                } else {
                    minutosForaPlano++;
                }
            }
        }

        // Calcular o valor: minutos fora do plano * taxa por hora
        valorFinal = (minutosForaPlano / 60.0) * 20.0;

        // Correção da cobrança
        int mesesPassados = calcularMesesPassados(ultimaDataCobranca, P.DataSaida);

        if (ultimaDataCobranca == 0) {
            valorFinal += 120.0; // Cobrar o primeiro mês
        }
        else if (mesesPassados >= 1) {
            valorFinal += mesesPassados * 120.0; // Corrigir a cobrança para todos os meses passados
        }

    } else if (strcasecmp(C.Plano, "24 Horas") == 0) {
        // Correção da cobrança
        int mesesPassados = calcularMesesPassados(ultimaDataCobranca, P.DataSaida);

        if (ultimaDataCobranca == 0) {
            valorFinal += 400.0; // Cobrar o primeiro mês
        }
        else if (mesesPassados >= 1) {
            valorFinal += mesesPassados * 400.0; // Corrigir a cobrança para todos os meses passados
        }

    } else if (strcasecmp(C.Plano, "Familia Anual") == 0) {
        // Correção da cobrança
        int anosPassados = calcularAnosPassados(ultimaDataCobranca, P.DataSaida);

        if (ultimaDataCobranca == 0) {
            valorFinal += 7200.0; // Cobrar o primeiro ano
        }
        else if (anosPassados >= 1) {
            valorFinal += anosPassados * 7200.0; // Corrigir a cobrança para todos os anos passados
        }

    } else {
        // Se o cliente não possui plano, cobra pelas horas totais
        valorFinal = (minutosTotais / 60.0) * 20.0;
    }

    return valorFinal;
}
