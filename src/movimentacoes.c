/* ============================================================================
 *  MOVIMENTACOES.C - MOVIMENTACOES FINANCEIRAS (LISTA SIMPLESMENTE ENCADEADA)
 *  Disciplina : Estrutura de Dados
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "tela.h"
#include "contas.h"
#include "movimentacoes.h"

#define ARQ_MOVIMENTACOES "Movimentacoes.dat"

//RegistroMovimentacao e o formato gravado no arquivo (sem o ponteiro prox)
typedef struct
{
    int    sequencial;
    int    codigo_conta;
    char   dt_movimento[11];
    char   tp_movimentacao[15];
    char   ds_favorecido[50];
    double vl_movimento;
    double vl_saldo;
}RegistroMovimentacao;

/* ---------------------------------------------------------------------------
 *  OPERACOES SOBRE A LISTA DE MOVIMENTACOES
 * ------------------------------------------------------------------------- */

//Função que deixa a lista de movimentacoes vazia
void inicializa_movimentacoes(ListaMovimentacoes *M)
{
    M->Primeiro = NULL;
    M->Ultimo = NULL;
    M->proximo_sequencial = 1;
}

//Função que insere no FINAL da lista; devolve 1 se deu certo, 0 se falhou
int insere_final_movimentacao(ListaMovimentacoes *M, Movimentacao mv)
{
    Movimentacao *novo = (Movimentacao *) malloc(sizeof(Movimentacao));

    if (novo == NULL){
        return 0;
    }
    *novo = mv;
    novo->prox = NULL;

    if (M->Ultimo != NULL){
        M->Ultimo->prox = novo;
    }else{
        M->Primeiro = novo;
    }
    M->Ultimo = novo;
    return 1;
}

//Função que verifica se uma conta tem alguma movimentacao registrada
int existe_movimentacao_conta(ListaMovimentacoes *M, int codigo_conta)
{
    Movimentacao *p = M->Primeiro;

    while (p != NULL){
        if (p->codigo_conta == codigo_conta){
            return 1;
        }
        p = p->prox;
    }
    return 0;
}

/* ---------------------------------------------------------------------------
 *  VALIDACAO DE DATA (formato dd/mm/aaaa)
 * ------------------------------------------------------------------------- */

//Função que devolve quantos dias tem um mes, considerando ano bissexto
static int dias_no_mes(int mes, int ano)
{
    int dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)){
        return 29;
    }
    return dias[mes-1];
}

//Função que verifica se uma data no formato dd/mm/aaaa existe de verdade
int data_valida(const char *data)
{
    int i;
    int d, m, a;

    if (strlen(data) != 10){
        return 0;
    }
    for (i = 0; i < 10; i++){
        if (i == 2 || i == 5){
            if (data[i] != '/'){
                return 0;
            }
        }else if (!isdigit((unsigned char) data[i])){
            return 0;
        }
    }

    sscanf(data, "%d/%d/%d", &d, &m, &a);

    if (m < 1 || m > 12){
        return 0;
    }
    if (d < 1 || d > dias_no_mes(m, a)){
        return 0;
    }
    return 1;
}

//Função que compara duas datas dd/mm/aaaa; <0 se d1<d2, 0 se iguais, >0 se d1>d2
//uma data vazia (conta que nunca movimentou) e sempre considerada a mais antiga
int compara_datas(const char *d1, const char *d2)
{
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    if (d1[0] == '\0'){
        return -1;
    }
    if (d2[0] == '\0'){
        return 1;
    }

    sscanf(d1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(d2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
}

/* ---------------------------------------------------------------------------
 *  TELA E LEITURA DA MOVIMENTACAO
 * ------------------------------------------------------------------------- */

//Função que desenha os rótulos do formulário de movimentacao
static void tela_movimentacao()
{
    gotoxy(3,5);
    printf("Codigo da Conta......:");
    gotoxy(3,7);
    printf("Banco................:");
    gotoxy(3,9);
    printf("Saldo Atual..........:");
    gotoxy(3,11);
    printf("Limite...............:");
    gotoxy(3,14);
    printf("1- Data..............:");
    gotoxy(50,14);
    printf("(dd/mm/aaaa)");
    gotoxy(3,16);
    printf("2- Favorecido........:");
    gotoxy(3,18);
    printf("3- Valor.............:");
    gotoxy(50,18);
    printf("(use ponto: 150.00)");
}

//Função que pede uma data valida e nao anterior a ultima movimentacao da conta
static void le_data_movimento(char *destino, const char *dt_ultimo_mov)
{
    do{
        gotoxy(26,14);
        printf("            ");
        gotoxy(26,14);
        le_texto(destino, 11);

        if (!data_valida(destino)){
            limpa_mensagem();
            gotoxy(07,23);
            printf("Data invalida, use o formato dd/mm/aaaa..");
            getch();
            limpa_mensagem();
        }else if (compara_datas(destino, dt_ultimo_mov) < 0){
            limpa_mensagem();
            gotoxy(07,23);
            printf("Data anterior a ultima movimentacao da conta (%s)..", dt_ultimo_mov);
            getch();
            limpa_mensagem();
            destino[0] = '\0';
        }
    }while(!data_valida(destino) || compara_datas(destino, dt_ultimo_mov) < 0);
}

/* ---------------------------------------------------------------------------
 *  REGISTRO DE MOVIMENTACAO (credito ou debito)
 * ------------------------------------------------------------------------- */

//tipo_credito: 1 = registra credito, 0 = registra debito
void registrar_movimentacao(ListaContas *C, ListaMovimentacoes *M, int tipo_credito)
{
    ContaBancaria *conta;
    Movimentacao mv;
    int codigo;
    int resp;
    double novo_saldo;

    do{
        do
        {
            system("cls");
            tela();
            tela_movimentacao();

            if (tipo_credito){
                titulo("====Registrar Entrada (Credito)====");
            }else{
                titulo("====Registrar Saida (Debito)====");
            }

            gotoxy(07,23);
            printf("Digite 0 para sair..");

            gotoxy(26,05);
            codigo = le_inteiro();

            conta = (codigo > 0) ? pesquisa_conta(C, codigo) : NULL;

            limpa_mensagem();

            if (codigo < 0){
                gotoxy(07,23);
                printf("Codigo invalido..");
                getch();
            }else if (codigo > 0 && conta == NULL){
                gotoxy(07,23);
                printf("Conta nao encontrada..");
                getch();
            }

        }while(codigo != 0 && conta == NULL);

        if (codigo != 0)
        {
            gotoxy(26,7);
            printf("%s", conta->banco);
            gotoxy(26,9);
            printf("%.2f", conta->vl_saldo);
            gotoxy(26,11);
            printf("%.2f", conta->vl_limite);

            le_data_movimento(mv.dt_movimento, conta->dt_ultimo_mov);

            gotoxy(26,16);
            le_texto(mv.ds_favorecido, sizeof(mv.ds_favorecido));

            do{
                gotoxy(26,18);
                printf("                    ");
                gotoxy(26,18);
                mv.vl_movimento = le_double();

                if (mv.vl_movimento <= 0){
                    limpa_mensagem();
                    gotoxy(07,23);
                    printf("Valor deve ser maior que zero..");
                    getch();
                    limpa_mensagem();
                    continue;
                }

                if (tipo_credito){
                    novo_saldo = conta->vl_saldo + mv.vl_movimento;
                }else{
                    novo_saldo = conta->vl_saldo - mv.vl_movimento;

                    if (novo_saldo < -conta->vl_limite){
                        limpa_mensagem();
                        gotoxy(07,23);
                        printf("Saldo insuficiente, limite ultrapassado..");
                        getch();
                        limpa_mensagem();
                        mv.vl_movimento = -1;
                    }
                }

            }while(mv.vl_movimento <= 0);

            limpa_mensagem();
            gotoxy(07,23);
            printf("Confirma a movimentacao (1=Sim;2=Nao).: ");
            resp = le_inteiro();

            if (resp == 1){
                mv.sequencial = M->proximo_sequencial;
                mv.codigo_conta = codigo;
                strcpy(mv.tp_movimentacao, tipo_credito ? "credito" : "debito");
                mv.vl_saldo = novo_saldo;

                if (insere_final_movimentacao(M, mv)){
                    M->proximo_sequencial++;
                    conta->vl_saldo = novo_saldo;
                    strcpy(conta->dt_ultimo_mov, mv.dt_movimento);

                    limpa_mensagem();
                    gotoxy(07,23);
                    printf("Movimentacao registrada, saldo atual: %.2f", conta->vl_saldo);
                }else{
                    limpa_mensagem();
                    gotoxy(07,23);
                    printf("Erro: memoria insuficiente..");
                }
                getch();
            }

            limpa_mensagem();
            gotoxy(07,23);
            printf("Deseja registrar outra? (1=Sim;2=Nao).: ");
            resp = le_inteiro();

            if (resp != 1)
            {
                break;
            }
        }

    }while(codigo != 0);
}

/* ---------------------------------------------------------------------------
 *  CONSULTA DE MOVIMENTACOES DE UMA CONTA
 * ------------------------------------------------------------------------- */

void consultar_movimentacao(ListaContas *C, ListaMovimentacoes *M)
{
    ContaBancaria *conta;
    Movimentacao *p;
    int codigo;
    int linha;
    int achou;

    system("cls");
    tela();
    titulo("====Consultar Movimentacoes====");

    gotoxy(07,23);
    printf("Codigo da conta (0=cancelar).: ");
    codigo = le_inteiro();

    if (codigo == 0){
        return;
    }

    conta = pesquisa_conta(C, codigo);
    if (conta == NULL){
        limpa_mensagem();
        gotoxy(07,23);
        printf("Conta nao encontrada..");
        getch();
        return;
    }

    system("cls");
    tela();
    titulo("====Consultar Movimentacoes====");

    gotoxy(3,5);
    printf("%-10s %-10s %-9s %12s %12s", "Data", "Tipo", "Sequencial", "Valor", "Saldo Apos");

    linha = 7;
    achou = 0;

    for (p = M->Primeiro; p != NULL; p = p->prox){
        if (p->codigo_conta == codigo){
            gotoxy(3,linha);
            printf("%-10s %-10s %10d %12.2f %12.2f",
                p->dt_movimento, p->tp_movimentacao, p->sequencial, p->vl_movimento, p->vl_saldo);
            linha++;
            achou = 1;
        }
    }

    if (!achou){
        gotoxy(07,23);
        printf("Nenhuma movimentacao encontrada para esta conta..");
    }else{
        gotoxy(07,23);
        printf("Pressione uma tecla para voltar..");
    }
    getch();
}

/* ---------------------------------------------------------------------------
 *  PERSISTENCIA: GRAVAR E CARREGAR O ARQUIVO DE DADOS
 * ------------------------------------------------------------------------- */

//Função que grava a lista inteira no arquivo; devolve 1 se deu certo, 0 se falhou
int salvar_movimentacoes(ListaMovimentacoes *M)
{
    Movimentacao *p;
    RegistroMovimentacao r;
    FILE *arq = fopen(ARQ_MOVIMENTACOES, "wb");

    if (arq == NULL){
        return 0;
    }
    for (p = M->Primeiro; p != NULL; p = p->prox){
        r.sequencial = p->sequencial;
        r.codigo_conta = p->codigo_conta;
        strcpy(r.dt_movimento, p->dt_movimento);
        strcpy(r.tp_movimentacao, p->tp_movimentacao);
        strcpy(r.ds_favorecido, p->ds_favorecido);
        r.vl_movimento = p->vl_movimento;
        r.vl_saldo = p->vl_saldo;

        fwrite(&r, sizeof(RegistroMovimentacao), 1, arq);
    }
    fclose(arq);
    return 1;
}

//Função que lê o arquivo e monta a lista na memória; devolve quantas movimentacoes carregou
int carregar_movimentacoes(ListaMovimentacoes *M)
{
    FILE *arq = fopen(ARQ_MOVIMENTACOES, "rb");
    RegistroMovimentacao r;
    Movimentacao mv;
    int qtd = 0;

    if (arq == NULL){
        return 0;
    }

    while (fread(&r, sizeof(RegistroMovimentacao), 1, arq) == 1){
        mv.sequencial = r.sequencial;
        mv.codigo_conta = r.codigo_conta;
        strcpy(mv.dt_movimento, r.dt_movimento);
        strcpy(mv.tp_movimentacao, r.tp_movimentacao);
        strcpy(mv.ds_favorecido, r.ds_favorecido);
        mv.vl_movimento = r.vl_movimento;
        mv.vl_saldo = r.vl_saldo;

        if (insere_final_movimentacao(M, mv)){
            qtd++;
            if (mv.sequencial >= M->proximo_sequencial){
                M->proximo_sequencial = mv.sequencial + 1;
            }
        }
    }
    fclose(arq);
    return qtd;
}
