/* ============================================================================
 *  MAIN.C - MENUS DO SISTEMA DE CONTROLE BANCARIO
 *  Disciplina : Estrutura de Dados
 *  Alunos: Miguel Possatti e Matheus Henrique
 *
 *  Compilar   : gcc -g *.c -o ..\output\bancario.exe
 *  Executar   : ..\output\bancario.exe
 * ========================================================================== */

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "tela.h"
#include "contas.h"
#include "movimentacoes.h"
#include "relatorios.h"

/* ---------------------------------------------------------------------------
 *  OPERACOES DE CONTA (usam contas.h; Remover tambem usa movimentacoes.h)
 * ------------------------------------------------------------------------- */

//Inclusao: modo 1 = no inicio, modo 2 = em uma posicao, modo 3 = no final
void incluir_conta(ListaContas *L, int modo)
{
    ContaBancaria conta;
    ContaBancaria *achou;
    int codigo;
    int pos;
    int resp;
    int ok;

    do{
        do
        {
            system("cls");
            tela();
            tela_conta();

            titulo("====Incluir Conta====");

            gotoxy(07,23);
            printf("Digite 0 para sair..");

            gotoxy(26,05);
            codigo = le_inteiro();

            achou = (codigo > 0) ? pesquisa_conta(L, codigo) : NULL;

            limpa_mensagem();

            if (codigo < 0){
                gotoxy(07,23);
                printf("Codigo invalido..");
                getch();
            }else if (achou != NULL){
                gotoxy(07,23);
                printf("Codigo ja cadastrado...");
                getch();
            }

        }while(codigo < 0 || achou != NULL);

        if (codigo != 0)
        {
            pos = 0;

            if (modo == 2){
                pos = le_posicao("incluir", tamanho_contas(L) + 1);
            }

            if (modo != 2 || pos != 0){
                conta.codigo_conta = codigo;
                le_conta(&conta);

                limpa_mensagem();
                gotoxy(07,23);
                printf("Deseja gravar os dados (1=Sim; 2=Nao).: ");
                resp = le_inteiro();

                if (resp == 1){
                    if (modo == 1){
                        ok = insere_inicio_conta(L, conta);
                    }else if (modo == 2){
                        ok = insere_posicao_conta(L, conta, pos);
                    }else{
                        ok = insere_final_conta(L, conta);
                    }

                    limpa_mensagem();
                    gotoxy(07,23);
                    if (ok){
                        printf("Conta cadastrada com sucesso..");
                    }else{
                        printf("Erro: memoria insuficiente..");
                    }
                    getch();
                }
            }

            limpa_mensagem();

            gotoxy(07,23);
            printf("Deseja incluir outra? (1=Sim;2=Nao).: ");
            resp = le_inteiro();

            if (resp != 1)
            {
                break;
            }
        }

    }while(codigo != 0);
}

//Função que faz a Alteração de uma conta
void alterar_conta(ListaContas *L)
{
    ContaBancaria conta;
    ContaBancaria *achou;
    int codigo;
    int campo;
    int resp;

    do{
        do
        {
            system("cls");
            tela();
            tela_conta();

            titulo("====Alterar Conta====");

            gotoxy(07,23);
            printf("Digite 0 para sair..");

            gotoxy(26,05);
            codigo = le_inteiro();

            achou = (codigo > 0) ? pesquisa_conta(L, codigo) : NULL;

            limpa_mensagem();

            if ((achou == NULL) && (codigo != 0)){
                gotoxy(07,23);
                printf("Codigo nao cadastrado..");
                getch();
            }

        }while((achou == NULL) && (codigo != 0));

        if (codigo != 0)
        {
            conta = *achou;
            mostra_conta(&conta);

            do
            {
                limpa_mensagem();

                gotoxy(07,23);
                printf("Digite o numero do campo a alterar (0=Fim).: ");
                campo = le_inteiro();

                limpa_mensagem();

                if (campo >= 1 && campo <= 7){
                    le_campo_conta(campo, &conta);
                }else if (campo != 0){
                    gotoxy(07,23);
                    printf("Campo invalido, digite de 1 a 7..");
                    getch();
                }

            }while(campo != 0);

            limpa_mensagem();

            gotoxy(07,23);
            printf("Deseja gravar as alteracoes (1=Sim; 2=Nao).: ");
            resp = le_inteiro();

            if (resp == 1){
                *achou = conta;

                limpa_mensagem();
                gotoxy(07,23);
                printf("Conta alterada com sucesso..");
                getch();
            }

            limpa_mensagem();

            gotoxy(07,23);
            printf("Deseja alterar outra? (1=Sim;2=Nao).: ");
            resp = le_inteiro();

            if (resp != 1)
            {
                break;
            }
        }

    }while(codigo != 0);
}

//Função que consulta uma conta pelo codigo
static void consultar_codigo(ListaContas *L)
{
    ContaBancaria *achou;
    int codigo;
    int resp;

    do{
        do
        {
            system("cls");
            tela();
            tela_conta();

            titulo("====Consultar Conta====");

            gotoxy(07,23);
            printf("Digite 0 para sair..");

            gotoxy(26,05);
            codigo = le_inteiro();

            achou = (codigo > 0) ? pesquisa_conta(L, codigo) : NULL;

            limpa_mensagem();

            if ((achou == NULL) && (codigo != 0)){
                gotoxy(07,23);
                printf("Codigo nao cadastrado..");
                getch();
            }

        }while((achou == NULL) && (codigo != 0));

        if (codigo != 0)
        {
            mostra_conta(achou);

            gotoxy(07,23);
            printf("Conta encontrada..");
            getch();

            limpa_mensagem();

            gotoxy(07,23);
            printf("Deseja consultar outra? (1=Sim;2=Nao).: ");
            resp = le_inteiro();

            if (resp != 1)
            {
                break;
            }
        }

    }while(codigo != 0);
}

//Função que desenha a tela e o cabeçalho da listagem de contas
static void cabecalho_listagem_contas()
{
    tela();
    titulo("====Listar Todas as Contas====");

    gotoxy(3,5);
    printf("%-4s %-4s %-14s %-7s %-8s %8s %8s %-8s",
        "Pos", "Cod", "Banco", "Agencia", "Conta", "Saldo", "Limite", "Status");
}

//Função que lista todas as contas cadastradas
static void listar_contas(ListaContas *L)
{
    ContaBancaria *p;
    int pos = 0;
    int linha;

    if (L->Primeiro == NULL){
        system("cls");
        tela();
        titulo("====Listar Todas as Contas====");
        gotoxy(07,23);
        printf("Nao existem contas cadastradas..");
        getch();
        return;
    }

    system("cls");
    cabecalho_listagem_contas();
    linha = 7;

    for (p = L->Primeiro; p != NULL; p = p->prox){
        pos++;

        gotoxy(3,linha);
        printf("%-4d %-4d %-14.14s %-7.7s %-8.8s %8.2f %8.2f %-8.8s",
            pos, p->codigo_conta, p->banco, p->agencia, p->numero_conta,
            p->vl_saldo, p->vl_limite, p->status);
        linha++;

        if (linha >= 19 && p->prox != NULL){
            limpa_mensagem();
            gotoxy(07,23);
            printf("Pressione uma tecla para a proxima pagina..");
            getch();

            cabecalho_listagem_contas();
            linha = 7;
        }
    }

    limpa_mensagem();
    gotoxy(07,23);
    printf("Total de contas cadastradas: %d (pressione uma tecla)", pos);
    getch();
}

//Função do menu de consulta: por codigo ou listagem geral
void consultar_conta(ListaContas *L)
{
    int opcao;

    do{
        system("cls");
        tela();

        titulo("====Consultar Contas====");

        gotoxy(26,9);
        printf("1. Consultar por codigo");

        gotoxy(26,11);
        printf("2. Listar todas as contas");

        gotoxy(26,13);
        printf("0. Voltar ao menu anterior");

        gotoxy(8,23);
        printf("Digite sua opcao: ");
        opcao = le_inteiro();

        switch (opcao)
        {
            case 1 :
                consultar_codigo(L);
                break;

            case 2 :
                listar_contas(L);
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

//Remocao: modo 1 = do inicio, modo 2 = de uma posicao, modo 3 = do final
void remover_conta(ListaContas *L, ListaMovimentacoes *M, int modo)
{
    ContaBancaria *alvo = NULL;
    int pos = 0;
    int resp;
    int ok;

    do{
        if (L->Primeiro == NULL){
            system("cls");
            tela();
            titulo("====Remover Conta====");
            gotoxy(07,23);
            printf("Lista vazia, nao ha conta para remover..");
            getch();
            break;
        }

        system("cls");
        tela();
        tela_conta();

        titulo("====Remover Conta====");

        if (modo == 1){
            alvo = L->Primeiro;
        }else if (modo == 3){
            alvo = L->Ultimo;
        }else{
            pos = le_posicao("remover", tamanho_contas(L));
            if (pos == 0){
                break;
            }
            alvo = conta_na_posicao(L, pos);
        }

        mostra_conta(alvo);

        if (existe_movimentacao_conta(M, alvo->codigo_conta)){
            limpa_mensagem();
            gotoxy(07,23);
            printf("Conta possui movimentacoes, remocao nao permitida..");
            getch();
            break;
        }

        limpa_mensagem();
        gotoxy(07,23);
        printf("Confirma a exclusao? (1=Sim;2=Nao).: ");
        resp = le_inteiro();

        if (resp == 1){
            if (modo == 1){
                ok = remove_inicio_conta(L);
            }else if (modo == 3){
                ok = remove_final_conta(L);
            }else{
                ok = remove_posicao_conta(L, pos);
            }

            limpa_mensagem();
            gotoxy(07,23);
            if (ok){
                printf("Conta removida com sucesso..");
            }else{
                printf("Nao foi possivel remover..");
            }
            getch();
        }

        if (L->Primeiro == NULL){
            resp = 2;
        }else{
            limpa_mensagem();
            gotoxy(07,23);
            printf("Deseja remover outra? (1=Sim;2=Nao).: ");
            resp = le_inteiro();
        }

    }while(resp == 1);
}

/* ---------------------------------------------------------------------------
 *  MENUS
 * ------------------------------------------------------------------------- */

void menu_cadastro_contas(ListaContas *L, ListaMovimentacoes *M){
    int opcao;
    int modo;

    do{
        system("cls");
        tela();
        titulo("====Cadastro de Contas====");

        gotoxy(26,9);
        printf("1. Incluir Conta");

        gotoxy(26,11);
        printf("2. Alterar Conta");

        gotoxy(26,13);
        printf("3. Consultar Conta");

        gotoxy(26,15);
        printf("4. Remover Conta");

        gotoxy(26,17);
        printf("0. Voltar ao menu principal");

        gotoxy(8,23);
        printf("Digite sua opcao: ");
        opcao = le_inteiro();

        switch (opcao)
        {
            case 1 :
                system("cls");
                tela();
                titulo("====Incluir Conta====");
                gotoxy(26,9);
                printf("1. No inicio da lista");
                gotoxy(26,11);
                printf("2. Em uma posicao da lista");
                gotoxy(26,13);
                printf("3. No final da lista");
                gotoxy(8,23);
                printf("Digite sua opcao: ");
                modo = le_inteiro();

                if (modo >= 1 && modo <= 3){
                    incluir_conta(L, modo);
                }
                break;

            case 2 :
                alterar_conta(L);
                break;

            case 3 :
                consultar_conta(L);
                break;

            case 4 :
                system("cls");
                tela();
                titulo("====Remover Conta====");
                gotoxy(26,9);
                printf("1. Do inicio da lista");
                gotoxy(26,11);
                printf("2. De uma posicao da lista");
                gotoxy(26,13);
                printf("3. Do final da lista");
                gotoxy(8,23);
                printf("Digite sua opcao: ");
                modo = le_inteiro();

                if (modo >= 1 && modo <= 3){
                    remover_conta(L, M, modo);
                }
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

void menu_movimentacao(ListaContas *C, ListaMovimentacoes *M){
    int opcao;

    do{
        system("cls");
        tela();
        titulo("====Movimentacao Financeira====");

        gotoxy(26,9);
        printf("1. Registrar Entrada");

        gotoxy(26,11);
        printf("2. Registrar Saida");

        gotoxy(26,13);
        printf("3. Consultar Movimentacao");

        gotoxy(26,15);
        printf("0. Voltar ao menu principal");

        gotoxy(8,23);
        printf("Digite sua opcao: ");
        opcao = le_inteiro();

        switch (opcao)
        {
            case 1 :
                registrar_movimentacao(C, M, 1);
                break;

            case 2 :
                registrar_movimentacao(C, M, 0);
                break;

            case 3 :
                consultar_movimentacao(C, M);
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

int main(){
    int opcao;
    ListaContas contas;
    ListaMovimentacoes movimentacoes;

    inicializa_contas(&contas);
    inicializa_movimentacoes(&movimentacoes);

    carregar_contas(&contas);
    carregar_movimentacoes(&movimentacoes);

    do
    {
        system("cls");
        tela();

        titulo("====Menu Principal====");

        gotoxy(26,8);
        printf("1. Cadastro de Contas");

        gotoxy(26,10);
        printf("2. Movimentacao Financeira");

        gotoxy(26,12);
        printf("3. Relatorios");

        gotoxy(26,14);
        printf("4. Sair");

        gotoxy(8,23);
        printf("Digite sua opcao: ");
        opcao = le_inteiro();

        switch (opcao)
        {
            case 1 :
                system("cls");
                menu_cadastro_contas(&contas, &movimentacoes);
                break;

            case 2 :
                system("cls");
                menu_movimentacao(&contas, &movimentacoes);
                break;

            case 3 :
                system("cls");
                menu_relatorios(&contas, &movimentacoes);
                break;

            case 4 :
                system("cls");
                tela();
                gotoxy(07,23);
                if (salvar_contas(&contas) && salvar_movimentacoes(&movimentacoes)){
                    printf("Dados gravados. Ate logo!");
                }else{
                    printf("ERRO: nao foi possivel gravar os arquivos de dados");
                }
                getch();
                break;

            default:
                limpa_mensagem();
                gotoxy(07,23);
                printf("Opcao invalida..");
                getch();
                break;
        }

    } while (opcao != 4);

    return 0;
}
