/* ============================================================================
 *  CONTAS.H - DEFINICAO DA STRUCT ContaBancaria E DAS FUNCOES DE CONTAS
 *  Disciplina : Estrutura de Dados
 *  Alunos: Miguel Possatti e Matheus Henrique
 * ========================================================================== */

#ifndef CONTAS_H
#define CONTAS_H

//ContaBancaria e cada no da lista duplamente encadeada de contas
typedef struct ContaBancaria
{
    int    codigo_conta;
    char   banco[50];
    char   agencia[10];
    char   numero_conta[20];
    char   tipo_conta[20];
    double vl_saldo;
    double vl_limite;
    char   status[10];
    char   dt_ultimo_mov[11];   //data da ultima movimentacao; vazio = nunca movimentou
    struct ContaBancaria *ant;
    struct ContaBancaria *prox;
}ContaBancaria;

//ListaContas guarda so os dois pontos de acesso: o primeiro e o ultimo no
typedef struct
{
    ContaBancaria *Primeiro;
    ContaBancaria *Ultimo;
}ListaContas;

void inicializa_contas(ListaContas *L);
int tamanho_contas(ListaContas *L);
ContaBancaria *pesquisa_conta(ListaContas *L, int codigo);
ContaBancaria *conta_na_posicao(ListaContas *L, int pos);
int insere_inicio_conta(ListaContas *L, ContaBancaria c);
int insere_final_conta(ListaContas *L, ContaBancaria c);
int insere_posicao_conta(ListaContas *L, ContaBancaria c, int pos);
int remove_inicio_conta(ListaContas *L);
int remove_final_conta(ListaContas *L);
int remove_posicao_conta(ListaContas *L, int pos);

void tela_conta();
void mostra_conta(ContaBancaria *c);
void le_conta(ContaBancaria *c);
void le_campo_conta(int campo, ContaBancaria *c);

int salvar_contas(ListaContas *L);
int carregar_contas(ListaContas *L);

#endif
