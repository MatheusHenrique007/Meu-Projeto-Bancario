# Meu-Projeto-Bancario

Trabalho Final de Estrutura de Dados (Prof. Rodney Carneiro) - Sistema de
Controle Bancario em C.

Contas em lista duplamente encadeada, movimentacoes em lista simplesmente
encadeada, com validacao de saldo/limite e data, gravacao em arquivo e
relatorios.

## Pastas

- `src` - codigo fonte
- `tests` - casos de teste
- `docs` - documentacao

## Como rodar

1. Baixe/clone o repositorio:
   ```
   git clone https://github.com/MatheusHenrique007/Meu-Projeto-Bancario.git
   ```
2. Abra o terminal (cmd ou PowerShell) dentro da pasta `src`
3. Compile:
   ```
   gcc -g *.c -o ..\output\bancario.exe
   ```
4. Entre na pasta `output` e rode o programa:
   ```
   cd ..\output
   bancario.exe
   ```
5. Use o menu digitando o numero da opcao e Enter

Os arquivos `Contas.dat` e `Movimentacoes.dat` sao criados sozinhos na primeira
vez que roda, e ficam salvos na pasta `output` junto do `.exe`.

## Menu

1. Cadastro de Contas - incluir, alterar, consultar, remover
2. Movimentacao Financeira - entrada, saida, consultar
3. Relatorios - contas cadastradas, movimentacoes, inativas, limites
