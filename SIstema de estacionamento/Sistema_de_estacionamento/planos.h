#ifndef PLANOS_H_INCLUDED
#define PLANOS_H_INCLUDED
typedef struct
{
    char nome[50];
    char descricao[100];
    double valor;

} NomePlano;

double calcularValorEstacionamento(Cliente C, Vaga P, int ultimaDataCobranca);
int calcularMesesPassados(int dataInicio, int dataFim);
int calcularAnosPassados(int dataInicio, int dataFim);
void TelaPlano ();
#endif // PLANOS_H_INCLUDED
