Considere o problema da escada rolante em anexo. Implemente uma solução utilizando threads e outra utilizando processos e responda às seguintes perguntas:

1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

  R: A estratégia utilizada no PROCESSO consiste basicamente em utilizar dois pipes para facilitar a comunicação bidirecional entre o processo pai e o processo filho. Um pipe é usado para enviar informações do filho para o pai (pipefd_pai_filho), e o outro é usado na direção oposta (pipefd_filho_pai). Isso permite que cada processo receba atualizações sobre o estado da escada rolante do outro processo, evitando assim, que duas pessoas acessem a escada rolante ao mesmo tempo.

   R: Já a estratégia utilizada com THREADS consiste em utilizar os mutexes, visto que são essenciais no controle do acesso à escada rolante em um ambiente multithread para garantir que apenas uma thread opere sobre o estado da escada em um dado momento. Isso é crucial porque a escada rolante, sendo um recurso compartilhado, pode levar a condições de corrida se múltiplas threads tentarem modificar seu estado simultaneamente. O uso de mutexes previne esse problema ao bloquear o acesso exclusivo às variáveis que determinam o fim da subida ou da descida. Assim, enquanto uma thread ajusta ou verifica essas variáveis, outras threads são bloqueadas até que o mutex seja liberado, garantindo operações seguras e consistentes.

2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

  R: Para garantir que somente uma das direções está ativa de cada vez no PROCESSO, observa-se o uso de fim_subida e fim_descida para calcular quando a próxima pessoa pode começar sua subida ou descida. Essas variáveis são inicialmente definidas como zero, representando que a escada rolante está pronta para uso. O processo filho, ao terminar de processar todas as subidas, envia através de um pipe (pipefd_pai_filho) o tempo em que a última subida terminou (fim_subida) para o processo pai. Isso significa que qualquer subida subsequente só pode ocorrer após todas as descidas serem processadas, garantindo que a escada opere em uma única direção por vez. O processo pai, antes de iniciar o processamento das descidas, aguarda (wait(NULL)) a conclusão do processo filho. Isso assegura que as descidas só comecem após todas as subidas planejadas serem concluídas. O processo pai então lê o tempo final da última subida enviada pelo filho antes de processar as descidas.

   R: Já a estratégia utilizada com THREADS observamos as variáveis de condição "pthread_cond_t pode_descer" e "pthread_cond_t pode_subir", que são essenciais para garantir que apenas uma direção da escada rolante esteja ativa por vez, já que elas funcionam como sinais que permitem que as threads aguardem por certas condições antes de continuar sua execução. Isso é alcançado fazendo uma thread esperar até que outra sinalize que é seguro proceder, utilizando funções como pthread_cond_wait() para bloquear a thread e pthread_cond_signal() para sinaliza-la, garantindo uma transição ordenada e segura entre as operações.

3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

  R: A implementação com processos cria um processo filho e utiliza pipes para comunicação entre processos, o que implica em maior isolamento e segurança, mas também em maior custo de recursos e complexidade na comunicação. Já a implementação com threads compartilha o espaço de memória entre as threads de subida e descida, usando mutexes e variáveis de condição para sincronização, resultando em uma comunicação mais eficiente e rápida, porém requer cuidados adicionais para evitar problemas de acesso concorrente aos recursos compartilhados. Em termos de eficiência operacional, especialmente em tarefas que exigem interação frequente e compartilhamento de estado, como na gestão de passageiros na escada rolante, a abordagem com threads tende a ser mais eficaz



Executando no AWS

Processos (E_2) --> Tempo final = 29

![image](https://github.com/arthurvignati/so/assets/161461962/7086c2d5-33b4-41cf-9a71-1e2058ab3cad)



Threads (E_2) --> Tempo final = 29

![image](https://github.com/arthurvignati/so/assets/161461962/8af07d2c-51f5-499e-b1e9-a73da571b11c)



Processos (E_5) --> Tempo final = 35 

![image](https://github.com/arthurvignati/so/assets/161461962/ad958305-1b94-4d3a-9190-a485049cf4e9)


Threads (E_5) --> Tempo final = 35

![image](https://github.com/arthurvignati/so/assets/161461962/c1e94c73-4a47-4a8d-9e43-bceb1c95854d)



Processos (E_25) --> Tempo final = 80316

![image](https://github.com/arthurvignati/so/assets/161461962/c6bdfe5b-bd48-4b99-b801-6e1cae1543f7)




Threads (E_25) --> Tempo final = 80316

![image](https://github.com/arthurvignati/so/assets/161461962/09ac23fc-80dd-4222-a132-79ff0f0f9898)



Processos (E_58) --> Tempo final = 55020

![image](https://github.com/arthurvignati/so/assets/161461962/47164a34-936c-4732-b253-67f7d18de3b0)



Threads (E_58) --> Tempo final = 55020

![image](https://github.com/arthurvignati/so/assets/161461962/9b829c84-ec89-4f9a-a3e7-0d1d1d6fb030)

