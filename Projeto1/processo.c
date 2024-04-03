#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//#define LEITURA 0
//#define ESCRITA 1

int main(void) {
  
  

  //inicializa os pipe's do filho e do pai antes do fork para os dois herdarem
//int pipefd_pai_filho[2];  //comunicação pai para filho
//int pipefd_filho_pai[2];  //comunicação filho para pai
//char mensagemByte;        //var que armazena a mensagem
  pid_t pid;

  int n;
printf("Quantas pessoas? R: ")
  scanf("%d", &n);

  int t[n], direcoes[n];
  int fim_subida = 0;
  int fim_descida = 0;
  int tempo_final = 0;

  for (int i=0; i<n; i++){
    printf("Digite o momento e a direção para a pessoa %d: ", i+1);
    scanf("%d %d", &t[i], &direcoes[i];
  }

  int pipefd[2];
  if (pipe(pipefd) == -1){
    perror("Falha ao criar pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("Fork Failed");
    return 1;
  }

  if (pid == 0) {  //PROCESSO FILHO (SUBIDA)
    close(pipefd[0]); //fecha o lado de leitura
    for (int i = 0; i < n; i++){
      if(direcoes[i] == 0){ //SUBIDA
        if (t[i] >= fim_descida){
          fim_subida = t[i] + 10;
        }else{//espera a descida acabar
          fim_subida = fim_descida + 10; 
        }
      }
    }

    write(pipefd[1], &fim_subida, sizeof(fim_subida));
    close(pipefd[1]);
    exit(EXIT_SUCESS)






    
  } 
  else {  //PROCESSO PAI
    close(pipefd_pai_filho[LEITURA]); //fecha leitura no pipe pai para filho
    close(pipefd_filho_pai[ESCRITA]); //fecha escrita no pipe filho para pai
    //mensagem pai para filho
    char msg_pai[] = "Mensagem do pai\n";
    write(pipefd_pai_filho[ESCRITA], msg_pai, sizeof(msg_pai) - 1);
    close(pipefd_pai_filho[ESCRITA]);    
    wait(NULL);
    //ler as mensagens do pipe filho para o pai 
    while (read(pipefd_filho_pai[0], &mensagemByte, 1) > 0) {
      printf("%c", mensagemByte); 
        }
    printf("\n");
    close(pipefd_filho_pai[LEITURA]);
    return 0;  
    }
}
