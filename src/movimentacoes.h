#ifndef MOVIMENTACOES_H
#define MOVIMENTACOES_H

#include "contas.h"

//Movimentacao e cada no da lista simplesmente encadeada de movimentacoes
typedef struct Movimentacao
{
    int    sequencial;
    int    codigo_conta;
    char   dt_movimento[11];
    char   tp_movimentacao[15];
    char   ds_favorecido[50];
    double vl_movimento;
    double vl_saldo;
    struct Movimentacao *prox;
}Movimentacao;

//ListaMovimentacoes guarda o primeiro/ultimo no e o proximo numero sequencial
typedef struct
{
    Movimentacao *Primeiro;
    Movimentacao *Ultimo;
    int proximo_sequencial;
}ListaMovimentacoes;

void inicializa_movimentacoes(ListaMovimentacoes *M);
int insere_final_movimentacao(ListaMovimentacoes *M, Movimentacao mv);
int existe_movimentacao_conta(ListaMovimentacoes *M, int codigo_conta);

int data_valida(const char *data);
int compara_datas(const char *d1, const char *d2);

void registrar_movimentacao(ListaContas *C, ListaMovimentacoes *M, int tipo_credito);
void consultar_movimentacao(ListaContas *C, ListaMovimentacoes *M);

int salvar_movimentacoes(ListaMovimentacoes *M);
int carregar_movimentacoes(ListaMovimentacoes *M);

#endif
