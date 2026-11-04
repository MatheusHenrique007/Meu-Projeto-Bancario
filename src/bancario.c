/* ============================================================================
 *  SISTEMA DE CONTROLE BANCARIO  -  LISTA DUPLAMENTE ENCADEADA (CONTAS)
 *                                   LISTA SIMPLESMENTE ENCADEADA (MOVIMENTACOES)
 *  Disciplina : Estrutura de Dados
 *
 *  Descricao  : Cadastro de contas bancarias (lista duplamente encadeada,
 *               alocacao dinamica com malloc/free) e registro das
 *               movimentacoes financeiras de cada conta (lista simplesmente
 *               encadeada). Ao abrir o programa os dados sao carregados dos
 *               arquivos Contas.dat e Movimentacoes.dat e, ao escolher
 *               "Sair", eles sao gravados de volta nesses arquivos.
 *
 *  Compilar   : gcc src/bancario.c -o bancario
 *  Executar   : bancario   (os arquivos .dat devem ficar na mesma pasta
 *               de onde o programa e executado)
 *
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------------
 *  COMPATIBILIDADE DE TELA (Windows x Linux)
 *  No Windows usa conio.h/windows.h (igual aos exemplos da disciplina).
 *  No Linux usa codigos ANSI, para permitir compilar e testar no ambiente
 *  de desenvolvimento antes de rodar na maquina com Windows.
 * ------------------------------------------------------------------------- */
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>

    //Funcao que emula o getch() do conio.h no Linux (le 1 tecla sem ECHO)
    int getch(void)
    {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

//Declaração das Constantes do Programa
#define ARQ_CONTAS          "Contas.dat"
#define ARQ_MOVIMENTACOES   "Movimentacoes.dat"

/* ---------------------------------------------------------------------------
 *  DEFINICAO DAS ESTRUTURAS DE DADOS (conforme o enunciado do trabalho)
 * ------------------------------------------------------------------------- */

//ContaBancaria e cada no da lista DUPLAMENTE encadeada de contas
typedef struct ContaBancaria
{
    int    codigo_conta;
    char   banco[50];
    char   agencia[10];
    char   numero_conta[20];
    char   tipo_conta[20];      //corrente, poupanca, credito
    double vl_saldo;
    double vl_limite;           //limite negativo permitido (cheque especial)
    char   status[10];          //ativo, inativo
    char   dt_ultimo_mov[11];   //data da ultima movimentacao (dd/mm/aaaa) ou "" se nunca movimentou
    struct ContaBancaria *ant;
    struct ContaBancaria *prox;
} ContaBancaria;

//ListaContas guarda so os dois pontos de acesso: o primeiro e o ultimo no
typedef struct
{
    ContaBancaria *Primeiro;
    ContaBancaria *Ultimo;
} ListaContas;

//Movimentacao e cada no da lista SIMPLESMENTE encadeada de movimentacoes
typedef struct Movimentacao
{
    int    sequencial;
    int    codigo_conta;
    char   dt_movimento[11];    //dd/mm/aaaa
    char   tp_movimentacao[15]; //credito, debito
    char   ds_favorecido[50];
    double vl_movimento;
    double vl_saldo;            //saldo da conta apos a movimentacao
    struct Movimentacao *prox;
} Movimentacao;

//ListaMovimentacoes guarda o primeiro/ultimo no e o proximo numero sequencial
typedef struct
{
    Movimentacao *Primeiro;
    Movimentacao *Ultimo;
    int proximo_sequencial;
} ListaMovimentacoes;

/* ---------------------------------------------------------------------------
 *  FUNCOES DE TELA (iguais ao padrao usado nos trabalhos anteriores)
 * ------------------------------------------------------------------------- */

#ifdef _WIN32
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#else
//Funcao que emula o gotoxy() do windows.h no Linux (codigo ANSI)
void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}
#endif

//Funcao que limpa a tela (equivalente ao system("cls") usado no Windows)
void limpa_tela(void)
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
#endif
}

void tela(void)
{
    int i;
    gotoxy(1,1);
    for (i = 0; i < 120; i++) putchar('-');
    gotoxy(1,2);
    printf("|  UNICV                       SISTEMA DE CONTROLE BANCARIO                     ESTRUTURA DE DADOS  |");
    gotoxy(1,3);
    for (i = 0; i < 120; i++) putchar('-');

    for (i = 4; i <= 21; i++){
        gotoxy(1,i);
        printf("|");
        gotoxy(120,i);
        printf("|");
    }

    gotoxy(1,22);
    for (i = 0; i < 120; i++) putchar('-');
    gotoxy(1,23);
    printf("| MSG:");
    gotoxy(1,24);
    for (i = 0; i < 120; i++) putchar('-');
}

//Funcao que escreve um titulo centralizado na linha 3 da tela
void titulo(const char *txt)
{
    gotoxy(60 - (int)(strlen(txt) / 2), 3);
    printf("%s", txt);
}

//Funcao que limpa o buffer de entrada
void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Funcao que limpa a linha de mensagem
void limpa_mensagem(void)
{
    gotoxy(7,23);
    printf("                                                                                                  ");
}

/* ---------------------------------------------------------------------------
 *  PROGRAMA PRINCIPAL (esqueleto do menu - funcionalidades vem nas proximas etapas)
 * ------------------------------------------------------------------------- */

void menu_cadastro_contas(void)
{
    limpa_tela();
    tela();
    titulo("====Cadastro de Contas====");
    gotoxy(7,23);
    printf("Em construcao... pressione uma tecla");
    getch();
}

void menu_movimentacao(void)
{
    limpa_tela();
    tela();
    titulo("====Movimentacao Financeira====");
    gotoxy(7,23);
    printf("Em construcao... pressione uma tecla");
    getch();
}

int main(void)
{
    int opcao;

    do
    {
        limpa_tela();
        tela();
        titulo("====Menu Principal====");

        gotoxy(45,8);
        printf("1. Cadastro de Contas");
        gotoxy(45,10);
        printf("2. Movimentacao Financeira");
        gotoxy(45,12);
        printf("3. Sair");

        gotoxy(7,23);
        printf("Digite sua opcao: ");

        if (scanf("%d", &opcao) != 1){
            opcao = -1;
        }
        limparBuffer();

        switch (opcao)
        {
            case 1:
                menu_cadastro_contas();
                break;
            case 2:
                menu_movimentacao();
                break;
            case 3:
                break;
            default:
                limpa_mensagem();
                gotoxy(7,23);
                printf("Opcao invalida..");
                getch();
                break;
        }

    } while (opcao != 3);

    limpa_tela();
    return 0;
}
