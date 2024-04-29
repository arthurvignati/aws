##MULTIPLICAÇÃO MATRIZxVETOR UTILIZANDO THREADS
  O programa em questão utiliza a biblioteca pthread para paralelizar a multiplicação de uma matriz por um vetor, visando um processamento mais eficiente e rápido. A matriz A, de dimensão 4x3, é multiplicada pelo vetor x de tamanho 3, resultando no vetor y de tamanho 4. Para alcançar a paralelização, dividimos as iterações do loop externo, que corresponde às linhas da matriz A, entre várias threads, em que cada uma das quatro threads calcula uma parte do vetor resultado y.

  Essa divisão é estruturada de modo que cada thread é responsável por um conjunto específico de linhas da matriz. O número total de linhas que cada thread deve processar é determinado pela divisão do número total de linhas m pelo número de threads thread_count. As threads processam suas linhas designadas calculando o produto escalar de cada linha com o vetor x armazenando o resultado correspondente no vetor y. Além disso, a utilização de pthread_create facilita a criação das múltiplas threads que executam a função Pth_matriz_vetor, em que cada uma recebe um identificador único que controla as linhas que ela deve processar. Isso assegura que o trabalho é distribuído de maneira equilibrada e que cada thread opera paralelamente, maximizando o uso dos núcleos disponíveis no processador.

  Portanto, essa abordagem paralela não apenas acelera o cálculo da multiplicação matriz-vetor mas também otimiza o uso dos recursos computacionais, sendo uma estratégia eficaz para o processamento de grandes volumes de dados ou para aplicações que exigem alta performance.

EXECUÇÃO SERVIDOR AWS

![image](https://github.com/arthurvignati/so/assets/161461962/77dceb0a-8e70-436d-9ba3-d86f8a3c0482)
