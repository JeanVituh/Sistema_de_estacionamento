#ifndef VAGAS_H_INCLUDED
#define VAGAS_H_INCLUDED
typedef struct
{
    int NumeroVaga;
    char Placa[9];
    int DataEntrada;
    int HoraEntrada;
    int DataSaida;
    int HoraSaida;
    char Status[10];


} Vaga;
void AbrirVaga();
void FecharVaga();
void listarVagas ();
void InserirVaga (Vaga P);
Vaga DigitarVaga(int *status);
void TelaVaga ();
void menuvagas();



#endif // VAGAS_H_INCLUDED
