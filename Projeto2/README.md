<h1 align="center"> PROJETO 2 - TRANSFERÊNCIA ENTRE CONTAS </h1>

# Grupo
Arthur Vignati Moscardi (10409688)

Guilherme Pascucci (10314281)

# Problema
O código realiza transferências de valores entre duas contas usando threads criadas com a chamada de sistema clone. Inicialmente, ambas as contas têm saldo de 100, e 10 transferências de 10 unidades cada são realizadas da conta from para a conta to. No entanto, devido à falta de mecanismos de sincronização, ocorrem condições de corrida que resultam em resultados inconsistentes nos saldos das contas. O problema principal é garantir que as transferências sejam realizadas corretamente e que os saldos sejam atualizados de maneira segura e consistente, evitando interferências entre threads (condição de corrida gerada pela solução concorrente).


# Solução
Para solucionar o problema de condição de corrida nas transferências entre contas, utilizamos pthread_mutex para garantir a sincronização das threads. Em um primeiro momento, definimos um mutex (pthread_mutex_t lock) e inicializamos com pthread_mutex_init. Na função de transferência, usamos pthread_mutex_lock(&lock) antes de verificar e modificar os saldos, garantindo que apenas uma thread acesse a seção crítica de cada vez. Após a atualização dos saldos, chamamos pthread_mutex_unlock(&lock) para liberar o mutex, evitando que múltiplas threads modifiquem os saldos simultaneamente. Além disso, utilizamos pthread_join para garantir que cada thread termine sua execução antes de iniciar a próxima, assegurando a ordem correta das operações e a integridade dos dados nas transferências. Dessa forma, evitamos condições de corrida e garantimos que as transferências ocorram corretamente e os saldos sejam consistentes.

# Explicação geral do código
O código realiza transferências de valores entre duas contas utilizando threads e mutexes para sincronização. Inicialmente, ambas as contas (from e to) começam com um saldo de 100. A cada iteração, criamos uma nova thread que realiza uma transferência de 10 unidades da conta from para a conta to. Para garantir que as operações de transferência sejam seguras e não causem condições de corrida, utilizamos um mutex (pthread_mutex_t lock), como dito anteriormente. Após cada conjunto de 10 transferências, trocamos as contas from e to e continuamos as operações, com a condição de parada em que as duas contas devem voltar a ter um saldo de 100. Além disso, temos a função pthread_join, utilizada para esperar que cada thread termine sua execução antes de iniciar a próxima. Com isso, exibimos os saldos atualizados das contas e mensagens de status após cada transferência e após a conclusão de todas as operações, garantindo que a saída seja clara e informativa.



# Implementação

Ponto 1 e 2: A conta to pode receber mais de uma transferência simultânea e a conta from pode enviar mais de uma transferência simultânea

![image](https://github.com/arthurvignati/so/assets/161461962/bb7b41b9-c94f-4626-9ea5-5c9c9f1afbed)

![image](https://github.com/arthurvignati/so/assets/161461962/35b2b07e-8766-4058-bb36-15a222950867)



Ponto 3: A conta from não pode enviar dinheiro se não tiver mais saldo (deve aparecer um aviso falando que não é possível mais enviar dinheiro)

*Para demonstrar o aviso falando que não é possível mais enviar dinheiro, atribuímos a conta From o valor de 50 e a Conta To o valor de 50, e o valor de transferência nesse caso seria de 20 reais, de tal forma que quando a conta From possuir o valor 10 e a conta To possuir o valor 90 (após duas transferências) aparecerá o aviso de erro, uma vez que From não possuí mais dinheiro para enviar.

Ponto 4: A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode receber e a conta que recebia pode enviar

![image](https://github.com/arthurvignati/so/assets/161461962/be02e669-40c6-485b-bd3a-f825c7427a63)

![image](https://github.com/arthurvignati/so/assets/161461962/8bb0e6b4-48f7-483e-89ce-4624eef42946)




Ponto 5: Poderão ser realizadas até 100 transações simultâneas de transferência

