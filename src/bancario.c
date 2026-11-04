/* ============================================================================
 *  SISTEMA DE CONTROLE BANCARIO
 *  Disciplina : Estrutura de Dados
 *   Alunos: Matheus Henrique Barros e Miguel Possatti Camargo
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//Declaração das Constantes do Programa
#define ARQ_CONTAS          "Contas.dat"
#define ARQ_MOVIMENTACOES   "Movimentacoes.dat"

//Definição das Estruturas de Dados

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
    struct ContaBancaria *ant;
    struct ContaBancaria *prox;
}ContaBancaria;

//ListaContas guarda so os dois pontos de acesso: o primeiro e o ultimo no
typedef struct
{
    ContaBancaria *Primeiro;
    ContaBancaria *Ultimo;
}ListaContas;

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

//ListaMovimentacoes guarda o primeiro/ultimo no da lista
typedef struct
{
    Movimentacao *Primeiro;
    Movimentacao *Ultimo;
}ListaMovimentacoes;

/* ---------------------------------------------------------------------------
 *  FUNCOES DE TELA E DE ENTRADA DE DADOS
 * ------------------------------------------------------------------------- */

//Função para posicionar o cursor em um determinado ponto da Tela
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tela(){
    gotoxy(1,1);
    printf("+--------------------------------------------------------------------------------------------------------------------+");
    gotoxy(1,3);
    printf("|                                                                                                                    |");
    gotoxy(1,2);
    printf("|  UNICIVE                              SISTEMA DE CONTROLE BANCARIO                             ESTRUTURA DE DADOS  |");
    gotoxy(1,4);
    printf("+--------------------------------------------------------------------------------------------------------------------+");
    gotoxy(1,5);
    printf("|                                                                                                                    |");
    gotoxy(1,6);
    printf("|                                                                                                                    |");
    gotoxy(1,7);
    printf("|                                                                                                                    |");
    gotoxy(1,8);
    printf("|                                                                                                                    |");
    gotoxy(1,9);
    printf("|                                                                                                                    |");
    gotoxy(1,10);
    printf("|                                                                                                                    |");
    gotoxy(1,11);
    printf("|                                                                                                                    |");
    gotoxy(1,12);
    printf("|                                                                                                                    |");
    gotoxy(1,13);
    printf("|                                                                                                                    |");
    gotoxy(1,14);
    printf("|                                                                                                                    |");
    gotoxy(1,15);
    printf("|                                                                                                                    |");
    gotoxy(1,16);
    printf("|                                                                                                                    |");
    gotoxy(1,17);
    printf("|                                                                                                                    |");
    gotoxy(1,18);
    printf("|                                                                                                                    |");
    gotoxy(1,19);
    printf("|                                                                                                                    |");
    gotoxy(1,20);
    printf("|                                                                                                                    |");
    gotoxy(1,21);
    printf("|                                                                                                                    |");
    gotoxy(1,22);
    printf("+--------------------------------------------------------------------------------------------------------------------+");
    gotoxy(1,23);
    printf("| MSG:                                                                                                               |");
    gotoxy(1,24);
    printf("+--------------------------------------------------------------------------------------------------------------------+");
}

//Função que limpa o buffer da mensagem
void limparBuffer()
{
    int c;
    while ((c = getchar()) !=  '\n' && c != EOF);
}

//Função que limpa a mensagem
void limpa_mensagem(){
    gotoxy(07,23);
    printf("                                                                        ");
}

//Função que escreve um título centralizado na linha 3 da tela
void titulo(const char *txt)
{
    gotoxy(60 - (int)(strlen(txt) / 2), 3);
    printf("%s", txt);
}

//Função que lê um número inteiro; devolve -1 se o usuário não digitar um número
//e 0 se a entrada do teclado acabar (Ctrl+Z), o que equivale a sair/cancelar
int le_inteiro()
{
    int n;
    int ret = scanf("%d", &n);

    if (ret == EOF){
        return 0;
    }
    if (ret != 1){
        n = -1;
    }
    limparBuffer();
    return n;
}

/* ---------------------------------------------------------------------------
 *  PROGRAMA PRINCIPAL
 * ------------------------------------------------------------------------- */

void menu_cadastro_contas(){
    tela();
    titulo("====Cadastro de Contas====");
    gotoxy(07,23);
    printf("Em construcao..");
    getch();
}

void menu_movimentacao(){
    tela();
    titulo("====Movimentacao Financeira====");
    gotoxy(07,23);
    printf("Em construcao..");
    getch();
}

int main(){
    int opcao;

    do
    {
        system("cls");
        tela();

        titulo("====Menu Principal====");

        gotoxy(45,8);
        printf("1. Cadastro de Contas");

        gotoxy(45,10);
        printf("2. Movimentacao Financeira");

        gotoxy(45,12);
        printf("3. Sair");

        gotoxy(8,23);
        printf("Digite sua opcao: ");
        opcao = le_inteiro();

        switch (opcao)
        {
            case 1 :
                system("cls");
                menu_cadastro_contas();
                break;

            case 2 :
                system("cls");
                menu_movimentacao();
                break;

            case 3 :
                break;

            default:
                limpa_mensagem();
                gotoxy(07,23);
                printf("Opcao invalida..");
                getch();
                break;
        }

    } while (opcao != 3);

    return 0;
}
