Considere o problema da escada rolante em anexo. Implemente uma solução utilizando threads e outra utilizando processos e responda às seguintes perguntas:

1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

  R: A estratégia utilizada no PROCESSO consiste basicamente em utilizar dois pipes para facilitar a comunicação bidirecional entre o processo pai e o processo filho. Um pipe é usado para enviar informações do filho para o pai (pipefd_pai_filho), e o outro é usado na direção oposta (pipefd_filho_pai). Isso permite que cada processo receba atualizações sobre o estado da escada rolante do outro processo, evitando assim, que duas pessoas acessem a escada rolante ao mesmo tempo.

   R: Já a estratégia utilizada com THREADS consiste em utilizar os mutexes, visto que são essenciais no controle do acesso à escada rolante em um ambiente multithread para garantir que apenas uma thread opere sobre o estado da escada em um dado momento. Isso é crucial porque a escada rolante, sendo um recurso compartilhado, pode levar a condições de corrida se múltiplas threads tentarem modificar seu estado simultaneamente. O uso de mutexes previne esse problema ao bloquear o acesso exclusivo às variáveis que determinam o fim da subida ou da descida. Assim, enquanto uma thread ajusta ou verifica essas variáveis, outras threads são bloqueadas até que o mutex seja liberado, garantindo operações seguras e consistentes.

2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

  R: Para garantir que somente uma das direções está ativa de cada vez no PROCESSO, observa-se o uso de fim_subida e fim_descida para calcular quando a próxima pessoa pode começar sua subida ou descida. Essas variáveis são inicialmente definidas como zero, representando que a escada rolante está pronta para uso. O processo filho, ao terminar de processar todas as subidas, envia através de um pipe (pipefd_pai_filho) o tempo em que a última subida terminou (fim_subida) para o processo pai. Isso significa que qualquer subida subsequente só pode ocorrer após todas as descidas serem processadas, garantindo que a escada opere em uma única direção por vez. O processo pai, antes de iniciar o processamento das descidas, aguarda (wait(NULL)) a conclusão do processo filho. Isso assegura que as descidas só comecem após todas as subidas planejadas serem concluídas. O processo pai então lê o tempo final da última subida enviada pelo filho antes de processar as descidas.

   R: Já a estratégia utilizada com THREADS observamos as variáveis de condição "pthread_cond_t pode_descer" e "pthread_cond_t pode_subir", que são essenciais para garantir que apenas uma direção da escada rolante esteja ativa por vez, já que elas funcionam como sinais que permitem que as threads aguardem por certas condições antes de continuar sua execução. Isso é alcançado fazendo uma thread esperar até que outra sinalize que é seguro proceder, utilizando funções como pthread_cond_wait() para bloquear a thread e pthread_cond_signal() para sinaliza-la, garantindo uma transição ordenada e segura entre as operações.

3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.





Executando no AWS
Processos (E_5)
![image](https://github.com/arthurvignati/so/assets/161461962/3cadef19-c378-4284-a64f-9c28ec1eaf2c)

