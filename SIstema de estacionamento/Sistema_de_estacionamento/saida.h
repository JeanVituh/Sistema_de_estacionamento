#ifndef SAIDA_H_INCLUDED
#define SAIDA_H_INCLUDED


int PesquisarVaga(char Placa, Vaga *P);
void ResetarVaga(char Placa[]);
void TelaSaida ();
Vaga DigitarSaida(int *status);
void ImprimirInfoVaga(Vaga P);
void menuSaida();
int AlterarVaga (Vaga P);
void registrarHistorico(Cliente C, Vaga P, double valor);


#endif // SAIDA_H_INCLUDED
