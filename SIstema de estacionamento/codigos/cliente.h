#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

typedef struct {

    int codigo;
    char Nome[50];
    char ModeloVeiculo [50];
    char Placa [9];
    char Plano [50];
} Cliente;
Cliente DigitarCliente(int *status);
void ImprimirCliente(Cliente C);
void Abrircliente();
void Fecharcliente();
void InserirCliente(Cliente C);
void excluirCliente(int Codigo);
void telacliente ();
int PesquisarCliente(int Codigo, Cliente *P);
int AlterarCliente (Cliente C);
void listarCliente ();
void menucliente();
int lerNumero();
int MaxCodigo();

#endif
