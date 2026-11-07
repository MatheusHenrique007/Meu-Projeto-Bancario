/* ============================================================================
 *  CONTAS.C - DADOS, REGRAS E PERSISTENCIA DAS CONTAS (LISTA DUPLAMENTE ENCADEADA)
 *  Disciplina : Estrutura de Dados
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "tela.h"
#include "contas.h"

#define ARQ_CONTAS "Contas.dat"

//RegistroConta e o formato gravado no arquivo (sem os ponteiros ant/prox)
typedef struct
{
    int    codigo_conta;
    char   banco[50];
    char   agencia[10];
    char   numero_conta[20];
    char   tipo_conta[20];
    double vl_saldo;
    double vl_limite;
    char   status[10];
    char   dt_ultimo_mov[11];
}RegistroConta;

/* ---------------------------------------------------------------------------
 *  OPERACOES SOBRE A LISTA DE CONTAS
 * ------------------------------------------------------------------------- */

//Função que deixa a lista de contas vazia
void inicializa_contas(ListaContas *L)
{
    L->Primeiro = NULL;
    L->Ultimo = NULL;
}

//Função que conta quantas contas existem na lista
int tamanho_contas(ListaContas *L)
{
    int n = 0;
    ContaBancaria *p = L->Primeiro;

    while (p != NULL){
        n++;
        p = p->prox;
    }
    return n;
}

//Função que procura uma conta pelo codigo; devolve o nó encontrado ou NULL
ContaBancaria *pesquisa_conta(ListaContas *L, int codigo)
{
    ContaBancaria *p = L->Primeiro;

    while (p != NULL){
        if (p->codigo_conta == codigo){
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

//Função que devolve o nó que está na posição pos (1 = primeiro) ou NULL
ContaBancaria *conta_na_posicao(ListaContas *L, int pos)
{
    int i;
    ContaBancaria *p = L->Primeiro;

    if (pos < 1){
        return NULL;
    }
    for (i = 1; i < pos && p != NULL; i++){
        p = p->prox;
    }
    return p;
}

//Função que aloca um novo nó com a conta dentro; devolve NULL se faltar memória
static ContaBancaria *cria_no_conta(ContaBancaria c)
{
    ContaBancaria *novo = (ContaBancaria *) malloc(sizeof(ContaBancaria));

    if (novo != NULL){
        *novo = c;
        novo->ant = NULL;
        novo->prox = NULL;
    }
    return novo;
}

//Função que insere no INÍCIO da lista; devolve 1 se deu certo, 0 se falhou
int insere_inicio_conta(ListaContas *L, ContaBancaria c)
{
    ContaBancaria *novo = cria_no_conta(c);

    if (novo == NULL){
        return 0;
    }
    novo->prox = L->Primeiro;
    novo->ant = NULL;

    if (L->Primeiro != NULL){
        L->Primeiro->ant = novo;
    }else{
        L->Ultimo = novo;
    }
    L->Primeiro = novo;
    return 1;
}

//Função que insere no FINAL da lista; devolve 1 se deu certo, 0 se falhou
int insere_final_conta(ListaContas *L, ContaBancaria c)
{
    ContaBancaria *novo = cria_no_conta(c);

    if (novo == NULL){
        return 0;
    }
    novo->ant = L->Ultimo;
    novo->prox = NULL;

    if (L->Ultimo != NULL){
        L->Ultimo->prox = novo;
    }else{
        L->Primeiro = novo;
    }
    L->Ultimo = novo;
    return 1;
}

//Função que insere numa POSIÇÃO (1 a tamanho+1); devolve 1 se deu certo, 0 se falhou
int insere_posicao_conta(ListaContas *L, ContaBancaria c, int pos)
{
    int n = tamanho_contas(L);
    ContaBancaria *anterior;
    ContaBancaria *posterior;
    ContaBancaria *novo;

    if (pos < 1 || pos > n + 1){
        return 0;
    }
    if (pos == 1){
        return insere_inicio_conta(L, c);
    }
    if (pos == n + 1){
        return insere_final_conta(L, c);
    }

    novo = cria_no_conta(c);
    if (novo == NULL){
        return 0;
    }
    anterior = conta_na_posicao(L, pos - 1);
    posterior = anterior->prox;

    novo->ant = anterior;
    novo->prox = posterior;
    anterior->prox = novo;
    posterior->ant = novo;
    return 1;
}

//Função que remove o PRIMEIRO da lista; devolve 1 se removeu, 0 se a lista estava vazia
int remove_inicio_conta(ListaContas *L)
{
    ContaBancaria *aux = L->Primeiro;

    if (aux == NULL){
        return 0;
    }
    L->Primeiro = aux->prox;

    if (L->Primeiro != NULL){
        L->Primeiro->ant = NULL;
    }else{
        L->Ultimo = NULL;
    }
    free(aux);
    return 1;
}

//Função que remove o ÚLTIMO da lista; devolve 1 se removeu, 0 se a lista estava vazia
int remove_final_conta(ListaContas *L)
{
    ContaBancaria *aux = L->Ultimo;

    if (aux == NULL){
        return 0;
    }
    L->Ultimo = aux->ant;

    if (L->Ultimo != NULL){
        L->Ultimo->prox = NULL;
    }else{
        L->Primeiro = NULL;
    }
    free(aux);
    return 1;
}

//Função que remove de uma POSIÇÃO (1 a tamanho); devolve 1 se removeu, 0 se a posição é inválida
int remove_posicao_conta(ListaContas *L, int pos)
{
    int n = tamanho_contas(L);
    ContaBancaria *alvo;

    if (pos < 1 || pos > n){
        return 0;
    }
    if (pos == 1){
        return remove_inicio_conta(L);
    }
    if (pos == n){
        return remove_final_conta(L);
    }

    alvo = conta_na_posicao(L, pos);
    alvo->ant->prox = alvo->prox;
    alvo->prox->ant = alvo->ant;
    free(alvo);
    return 1;
}

/* ---------------------------------------------------------------------------
 *  FORMULARIO DE CONTA (mostrar e ler os dados de uma conta)
 * ------------------------------------------------------------------------- */

//Função que desenha os rótulos do formulário de conta
void tela_conta(){
    gotoxy(12,5);
    printf("Codigo da Conta......:");
    gotoxy(9,7);
    printf("1- Banco.............:");
    gotoxy(9,9);
    printf("2- Agencia...........:");
    gotoxy(9,11);
    printf("3- Numero da Conta...:");
    gotoxy(9,13);
    printf("4- Tipo da Conta.....:");
    gotoxy(85,13);
    printf("(corrente/poupanca/credito)");
    gotoxy(9,15);
    printf("5- Saldo.............:");
    gotoxy(85,15);
    printf("(use ponto: 500.00)");
    gotoxy(9,17);
    printf("6- Limite............:");
    gotoxy(85,17);
    printf("(use ponto: 200.00)");
    gotoxy(9,19);
    printf("7- Status............:");
    gotoxy(85,19);
    printf("(ativo/inativo)");
}

//Função que mostra os dados de uma conta no formulário
void mostra_conta(ContaBancaria *c)
{
    gotoxy(32,5);
    printf("%d", c->codigo_conta);

    gotoxy(32,7);
    printf("%s", c->banco);

    gotoxy(32,9);
    printf("%s", c->agencia);

    gotoxy(32,11);
    printf("%s", c->numero_conta);

    gotoxy(32,13);
    printf("%s", c->tipo_conta);

    gotoxy(32,15);
    printf("%.2f", c->vl_saldo);

    gotoxy(32,17);
    printf("%.2f", c->vl_limite);

    gotoxy(32,19);
    printf("%s", c->status);
}

//Função que lê UM campo (1 a 7) do formulário, apagando antes o valor antigo
void le_campo_conta(int campo, ContaBancaria *c)
{
    int linha = 5 + campo * 2;

    gotoxy(32,linha);
    printf("                                                  ");
    gotoxy(32,linha);

    switch (campo)
    {
        case 1 :
            le_texto(c->banco, sizeof(c->banco));
            break;

        case 2 :
            le_texto(c->agencia, sizeof(c->agencia));
            break;

        case 3 :
            le_texto(c->numero_conta, sizeof(c->numero_conta));
            break;

        case 4 :
            le_texto(c->tipo_conta, sizeof(c->tipo_conta));
            break;

        case 5 :
            do{
                gotoxy(32,linha);
                printf("                    ");
                gotoxy(32,linha);
                c->vl_saldo = le_double();

                if (c->vl_saldo < 0){
                    limpa_mensagem();
                    gotoxy(07,23);
                    printf("Saldo invalido, use ponto nos centavos (ex: 500.00)");
                    getch();
                    limpa_mensagem();
                }
            }while(c->vl_saldo < 0);
            break;

        case 6 :
            do{
                gotoxy(32,linha);
                printf("                    ");
                gotoxy(32,linha);
                c->vl_limite = le_double();

                if (c->vl_limite < 0){
                    limpa_mensagem();
                    gotoxy(07,23);
                    printf("Limite invalido, use ponto nos centavos (ex: 200.00)");
                    getch();
                    limpa_mensagem();
                }
            }while(c->vl_limite < 0);
            break;

        case 7 :
            do{
                gotoxy(32,linha);
                printf("                    ");
                gotoxy(32,linha);
                le_texto(c->status, sizeof(c->status));

                if (strcmp(c->status, "ativo") != 0 && strcmp(c->status, "inativo") != 0){
                    limpa_mensagem();
                    gotoxy(07,23);
                    printf("Status invalido, digite ativo ou inativo");
                    getch();
                    limpa_mensagem();
                }
            }while(strcmp(c->status, "ativo") != 0 && strcmp(c->status, "inativo") != 0);
            break;
    }
}

//Função que lê todos os campos (1 a 7) de uma conta nova, um apos o outro
void le_conta(ContaBancaria *c)
{
    int campo;

    c->dt_ultimo_mov[0] = '\0';

    for (campo = 1; campo <= 7; campo++){
        le_campo_conta(campo, c);
    }
}

/* ---------------------------------------------------------------------------
 *  PERSISTENCIA: GRAVAR E CARREGAR O ARQUIVO DE DADOS
 * ------------------------------------------------------------------------- */

//Função que grava a lista inteira no arquivo; devolve 1 se deu certo, 0 se falhou
int salvar_contas(ListaContas *L)
{
    ContaBancaria *p;
    RegistroConta r;
    FILE *arq = fopen(ARQ_CONTAS, "wb");

    if (arq == NULL){
        return 0;
    }
    for (p = L->Primeiro; p != NULL; p = p->prox){
        r.codigo_conta = p->codigo_conta;
        strcpy(r.banco, p->banco);
        strcpy(r.agencia, p->agencia);
        strcpy(r.numero_conta, p->numero_conta);
        strcpy(r.tipo_conta, p->tipo_conta);
        r.vl_saldo = p->vl_saldo;
        r.vl_limite = p->vl_limite;
        strcpy(r.status, p->status);
        strcpy(r.dt_ultimo_mov, p->dt_ultimo_mov);

        fwrite(&r, sizeof(RegistroConta), 1, arq);
    }
    fclose(arq);
    return 1;
}

//Função que lê o arquivo e monta a lista na memória; devolve quantas contas carregou
int carregar_contas(ListaContas *L)
{
    FILE *arq = fopen(ARQ_CONTAS, "rb");
    RegistroConta r;
    ContaBancaria c;
    int qtd = 0;

    if (arq == NULL){
        return 0;
    }

    while (fread(&r, sizeof(RegistroConta), 1, arq) == 1){
        c.codigo_conta = r.codigo_conta;
        strcpy(c.banco, r.banco);
        strcpy(c.agencia, r.agencia);
        strcpy(c.numero_conta, r.numero_conta);
        strcpy(c.tipo_conta, r.tipo_conta);
        c.vl_saldo = r.vl_saldo;
        c.vl_limite = r.vl_limite;
        strcpy(c.status, r.status);
        strcpy(c.dt_ultimo_mov, r.dt_ultimo_mov);

        if (insere_final_conta(L, c)){
            qtd++;
        }
    }
    fclose(arq);
    return qtd;
}
