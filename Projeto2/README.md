<h1 align="center"> PROJETO 2 - TRANSFERÊNCIA ENTRE CONTAS </h1>

# Problema
O código realiza transferências de valores entre duas contas usando threads criadas com a chamada de sistema clone. Inicialmente, ambas as contas têm saldo de 100, e 10 transferências de 10 unidades cada são realizadas da conta from para a conta to. No entanto, devido à falta de mecanismos de sincronização, ocorrem condições de corrida que resultam em resultados inconsistentes nos saldos das contas. O problema principal é garantir que as transferências sejam realizadas corretamente e que os saldos sejam atualizados de maneira segura e consistente, evitando interferências entre threads (condição de corrida gerada pela solução concorrente).


# Solução
Para solucionar o problema de condição de corrida nas transferências entre contas, utilizamos pthread_mutex para garantir a sincronização das threads. Em um primeiro momento, definimos um mutex (pthread_mutex_t lock) e inicializamos com pthread_mutex_init. Na função de transferência, usamos pthread_mutex_lock(&lock) antes de verificar e modificar os saldos, garantindo que apenas uma thread acesse a seção crítica de cada vez. Após a atualização dos saldos, chamamos pthread_mutex_unlock(&lock) para liberar o mutex, evitando que múltiplas threads modifiquem os saldos simultaneamente. Além disso, utilizamos pthread_join para garantir que cada thread termine sua execução antes de iniciar a próxima, assegurando a ordem correta das operações e a integridade dos dados nas transferências. Dessa forma, evitamos condições de corrida e garantimos que as transferências ocorram corretamente e os saldos sejam consistentes.

# Explicação geral do código
O código realiza transferências de valores entre duas contas utilizando threads e mutexes para sincronização. Inicialmente, ambas as contas (from e to) começam com um saldo de 100. A cada iteração, criamos uma nova thread que realiza uma transferência de 10 unidades da conta from para a conta to. Para garantir que as operações de transferência sejam seguras e não causem condições de corrida, utilizamos um mutex (pthread_mutex_t lock), como dito anteriormente. Após cada conjunto de 10 transferências, trocamos as contas from e to e continuamos as operações, com a condição de parada em que as duas contas devem voltar a ter um saldo de 100. Além disso, temos a função pthread_join, utilizada para esperar que cada thread termine sua execução antes de iniciar a próxima. Com isso, exibimos os saldos atualizados das contas e mensagens de status após cada transferência e após a conclusão de todas as operações, garantindo que a saída seja clara e informativa.



# Implementação

Ponto 1 e 2: A conta to pode receber mais de uma transferência simultânea e a conta from pode enviar mais de uma transferência simultânea

Ponto 3: A conta from não pode enviar dinheiro se não tiver mais saldo (deve aparecer um aviso falando que não é possível mais enviar dinheiro)

Ponto 4: A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode receber e a conta que recebia pode enviar

Ponto 5: Poderão ser realizadas até 100 transações simultâneas de transferência

