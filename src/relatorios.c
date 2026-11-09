/* ============================================================================
 *  RELATORIOS.C - RELATORIOS FINANCEIROS DO SISTEMA
 *  Disciplina : Estrutura de Dados
 * ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "tela.h"
#include "contas.h"
#include "movimentacoes.h"
#include "relatorios.h"

//Função que mostra o relatorio de todas as contas cadastradas
static void relatorio_contas_cadastradas(ListaContas *C)
{
    ContaBancaria *p;
    int linha;

    system("cls");
    tela();
    titulo("====Relatorio: Contas Cadastradas====");

    if (C->Primeiro == NULL){
        gotoxy(07,23);
        printf("Nao existem contas cadastradas..");
        getch();
        return;
    }

    gotoxy(2,5);
    printf("%-4s %-14s %-7s %-10s %-8s %8s %8s %-8s",
        "Cod", "Banco", "Agencia", "Conta", "Tipo", "Saldo", "Limite", "Status");

    linha = 7;
    for (p = C->Primeiro; p != NULL; p = p->prox){
        gotoxy(2,linha);
        printf("%-4d %-14.14s %-7.7s %-10.10s %-8.8s %8.2f %8.2f %-8.8s",
            p->codigo_conta, p->banco, p->agencia, p->numero_conta,
            p->tipo_conta, p->vl_saldo, p->vl_limite, p->status);
        linha++;
    }

    gotoxy(07,23);
    printf("Pressione uma tecla para voltar..");
    getch();
}

//Função que mostra o relatorio das contas com status "inativo"
static void relatorio_contas_inativas(ListaContas *C)
{
    ContaBancaria *p;
    int linha;
    int achou = 0;

    system("cls");
    tela();
    titulo("====Relatorio: Contas Inativas====");

    gotoxy(2,5);
    printf("%-4s %-14s %-7s %-10s %8s %8s",
        "Cod", "Banco", "Agencia", "Conta", "Saldo", "Limite");

    linha = 7;
    for (p = C->Primeiro; p != NULL; p = p->prox){
        if (strcmp(p->status, "inativo") == 0){
            gotoxy(2,linha);
            printf("%-4d %-14.14s %-7.7s %-10.10s %8.2f %8.2f",
                p->codigo_conta, p->banco, p->agencia, p->numero_conta,
                p->vl_saldo, p->vl_limite);
            linha++;
            achou = 1;
        }
    }

    if (!achou){
        gotoxy(07,23);
        printf("Nao ha contas inativas..");
    }else{
        gotoxy(07,23);
        printf("Pressione uma tecla para voltar..");
    }
    getch();
}

//Função que mostra o relatorio de limites de credito de todas as contas
static void relatorio_limites_credito(ListaContas *C)
{
    ContaBancaria *p;
    int linha;

    system("cls");
    tela();
    titulo("====Relatorio: Limites de Credito por Conta====");

    if (C->Primeiro == NULL){
        gotoxy(07,23);
        printf("Nao existem contas cadastradas..");
        getch();
        return;
    }

    gotoxy(2,5);
    printf("%-4s %-14s %-7s %-10s %8s %10s",
        "Cod", "Banco", "Agencia", "Conta", "Saldo", "Limite Credito");

    linha = 7;
    for (p = C->Primeiro; p != NULL; p = p->prox){
        gotoxy(2,linha);
        printf("%-4d %-14.14s %-7.7s %-10.10s %8.2f %10.2f",
            p->codigo_conta, p->banco, p->agencia, p->numero_conta,
            p->vl_saldo, p->vl_limite);
        linha++;
    }

    gotoxy(07,23);
    printf("Pressione uma tecla para voltar..");
    getch();
}

//Função do menu de relatorios
void menu_relatorios(ListaContas *C, ListaMovimentacoes *M)
{
    int opcao;

    do{
        system("cls");
        tela();
        titulo("====Relatorios====");

        gotoxy(26,8);
        printf("1. Contas Cadastradas");

        gotoxy(26,10);
        printf("2. Movimentacoes de uma Conta");

        gotoxy(26,12);
        printf("3. Contas Inativas");

        gotoxy(26,14);
        printf("4. Limites de Credito por Conta");

        gotoxy(26,16);
        printf("0. Voltar ao menu principal");

        gotoxy(8,23);
        printf("Digite sua opcao: ");
        opcao = le_inteiro();

        switch (opcao)
        {
            case 1 :
                relatorio_contas_cadastradas(C);
                break;

            case 2 :
                consultar_movimentacao(C, M);
                break;

            case 3 :
                relatorio_contas_inativas(C);
                break;

            case 4 :
                relatorio_limites_credito(C);
                break;

            case 0 :
                break;

            default:
                limpa_mensagem();
                gotoxy(07,23);
                printf("Opcao invalida..");
                getch();
                break;
        }

    }while(opcao != 0);
}
