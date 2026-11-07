/* ============================================================================
 *  TELA.C - FUNCOES DE TELA E DE ENTRADA DE DADOS
 *  Disciplina : Estrutura de Dados
 * ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "tela.h"

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

//Função que escreve um título centralizado na linha 3 da tela
void titulo(const char *txt)
{
    gotoxy(60 - (int)(strlen(txt) / 2), 3);
    printf("%s", txt);
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

//Função que lê um número real; devolve -1 se o usuário não digitar um número
//e 0 se a entrada do teclado acabar (Ctrl+Z)
double le_double()
{
    double v;
    int ret = scanf("%lf", &v);

    if (ret == EOF){
        return 0;
    }
    if (ret != 1){
        v = -1;
    }
    limparBuffer();
    return v;
}

//Função que lê um texto com fgets e tira o ENTER do final
void le_texto(char *destino, int tamanho_max)
{
    int len;

    if (fgets(destino, tamanho_max, stdin) == NULL){
        destino[0] = '\0';
    }

    len = 0;
    while (destino[len] != '\0') len++;

    if (len > 0 && destino[len-1] == '\n'){
        destino[len-1] = '\0';
    }else{
        limparBuffer();
    }
}

//Função que pede uma posição da lista (1 a max); devolve 0 se o usuário cancelar
int le_posicao(const char *acao, int max)
{
    int pos;

    do{
        limpa_mensagem();
        gotoxy(07,23);
        printf("Posicao para %s (1 a %d; 0=cancelar).: ", acao, max);
        pos = le_inteiro();

        if (pos < 0 || pos > max){
            limpa_mensagem();
            gotoxy(07,23);
            printf("Posicao invalida..");
            getch();
        }
    }while(pos < 0 || pos > max);

    return pos;
}
