#ifndef HISTORICO_H_INCLUDED
#define HISTORICO_H_INCLUDED
FILE *fphistorico;
void AbrirHistorico();
void FecharHistorico();
int PesquisarPlaca(char Placa[], Vaga *P);
void listarHistorico (char Placa[]);
void TelaHistorico ();
Vaga DigitarPlaca(int *status, Vaga P);
void menuHistorico();

#endif // HISTORICO_H_INCLUDED
