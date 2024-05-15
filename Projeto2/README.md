<h1 align="center"> PROJETO 2 - TRANSFERÊNCIA ENTRE CONTAS </h1>

# Problema
O código realiza transferências de valores entre duas contas usando threads criadas com a chamada de sistema clone. Inicialmente, ambas as contas têm saldo de 100, e 10 transferências de 10 unidades cada são realizadas da conta from para a conta to. No entanto, devido à falta de mecanismos de sincronização, ocorrem condições de corrida que resultam em resultados inconsistentes nos saldos das contas. O problema principal é garantir que as transferências sejam realizadas corretamente e que os saldos sejam atualizados de maneira segura e consistente, evitando interferências entre threads (condição de corrida gerada pela solução concorrente).


# Solução



# Implementação

Ponto 1 e 2: A conta to pode receber mais de uma transferência simultânea e a conta from pode enviar mais de uma transferência simultânea

Ponto 3: A conta from não pode enviar dinheiro se não tiver mais saldo (deve aparecer um aviso falando que não é possível mais enviar dinheiro)

Ponto 4: A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode receber e a conta que recebia pode enviar

Ponto 5: Poderão ser realizadas até 100 transações simultâneas de transferência

