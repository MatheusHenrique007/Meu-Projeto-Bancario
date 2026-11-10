# Casos de Teste

Testes feitos rodando o `bancario.exe` antes da entrega, seguindo os cenarios
sugeridos no enunciado.

## 1. Cadastro de contas

Cadastrei conta no inicio, uma no final e uma em posicao do meio. Tentei
cadastrar o mesmo codigo de novo e deu "Codigo ja cadastrado". Funcionou certo.

## 2. Alterar e remover conta

Alterei o banco de uma conta e salvou certo. Tentei remover uma conta que tinha
movimentacao e o programa bloqueou ("Conta possui movimentacoes, remocao nao
permitida"). Removi uma conta sem movimentacao e funcionou normal.

## 3. Lista encadeada

Inseri contas em posicoes diferentes (inicio, meio, fim) e percorri a lista nos
dois sentidos pra conferir os ponteiros. Ficou: 5, 10, 15, 20, 30 indo pra
frente e 30, 20, 15, 10, 5 voltando. Nenhum numero repetido ou perdido.

## 4. Credito e debito (exemplo do enunciado)

Testei exatamente o exemplo do PDF: conta com saldo 500, credito de 200,
debito de 100 e debito de 150. Saldo foi passando 700 -> 600 -> 450, igual o
esperado.

## 5. Limite de debito

Conta com saldo 500 e limite 200. Debito de 600 passou (saldo -100). Debito de
700 tambem passou (saldo -200). Debito de 700,01 foi bloqueado com "Saldo
insuficiente".

## 6. Data da movimentacao

Tentei registrar uma data invalida (31/02/2024) e deu erro certo. Tentei uma
data anterior a ultima movimentacao da conta e tambem bloqueou. Com uma data
valida e posterior, registrou normal.

## 7. Entradas invalidas

Digitei letra no lugar do codigo, uma opcao de menu que nao existe, e um
codigo de conta que nao existe na movimentacao. Em todos os casos apareceu
mensagem de erro e o programa continuou rodando, sem travar.

## 8. Relatorios

Cadastrei uma conta ativa e uma inativa, fiz uma movimentacao e olhei os 4
relatorios. O de contas cadastradas mostrou as duas, o de inativas so a
inativa, e o de movimentacoes so trouxe a da conta que eu pedi.

## 9. Salvar e abrir de novo

Cadastrei conta, fiz movimentacao, saí do programa e abri de novo. Os dados
voltaram do jeito que ficaram salvos (saldo e historico certos).

## 10. Memoria

Conferi no codigo que toda conta/movimentacao alocada com `malloc` tem um
`free` quando é removida, pra nao vazar memoria.
