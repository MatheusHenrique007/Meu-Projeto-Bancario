#ifndef TELA_H
#define TELA_H

void gotoxy(int x, int y);
void tela();
void titulo(const char *txt);
void limparBuffer();
void limpa_mensagem();
int le_inteiro();
double le_double();
void le_texto(char *destino, int tamanho_max);
int le_posicao(const char *acao, int max);

#endif
