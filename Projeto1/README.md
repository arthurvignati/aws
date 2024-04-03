Considere o problema da escada rolante em anexo. Implemente uma solução utilizando threads e outra utilizando processos e responda às seguintes perguntas:

1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

  R: A estratégia utilizada no PROCESSO consiste basicamente em  utilizar dois pipes para facilitar a comunicação bidirecional entre o processo pai e o processo filho. Um pipe é usado para enviar informações do filho para o pai (pipefd_pai_filho), e o outro é usado na direção oposta (pipefd_filho_pai). Isso permite que cada processo receba atualizações sobre o estado da escada rolante do outro processo. O processo filho é responsável por gerenciar todas as subidas. Ele percorre todas as solicitações e determina o tempo em que cada subida terminará, considerando o tempo de início da subida e se precisa esperar que uma descida anterior termine.
  
   Após o processo filho concluir suas operações e comunicar o tempo final da última subida, o processo pai inicia o processamento das descidas. Similarmente ao processo filho, ele considera o tempo de início de cada descida e se precisa esperar que uma subida anterior termine. Através da leitura do tempo final da última subida pelo processo pai (e vice-versa para descidas, se aplicável), garante-se que as ações de descida só começarão após a conclusão de todas as subidas, e que uma nova série de subidas, se houver, aguarde a conclusão das descidas.

   R: Já a estratégia utilizada com THREADS...

2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

  R: Para garantir que somente uma das direções está ativa de cada vez no PROCESSO, observa-se o uso de fim_subida e fim_descida para calcular quando a próxima pessoa pode começar sua subida ou descida. Essas variáveis são inicialmente definidas como zero, representando que a escada rolante está pronta para uso. O processo filho, ao terminar de processar todas as subidas, envia através de um pipe (pipefd_pai_filho) o tempo em que a última subida terminou (fim_subida) para o processo pai. Isso significa que qualquer subida subsequente só pode ocorrer após todas as descidas serem processadas, garantindo que a escada opere em uma única direção por vez. O processo pai, antes de iniciar o processamento das descidas, aguarda (wait(NULL)) a conclusão do processo filho. Isso assegura que as descidas só comecem após todas as subidas planejadas serem concluídas. O processo pai então lê o tempo final da última subida enviada pelo filho antes de processar as descidas.
  
  Portanto, essa comunicação bidirecional garante que todas as subidas são concluídas antes de iniciar quaisquer descidas, e uma nova série de subidas só pode começar após a conclusão de todas as descidas.

   R: Já a estratégia utilizada com THREADS...

3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
