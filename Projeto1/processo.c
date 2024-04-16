#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
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
    scanf("%d %d", &t[i], &direcoes[i]);
  }

  int pipefd_filho_pai[2], pipefd_pai_filho[2];
  if (pipe(pipefd_filho_pai) == -1 || pipe(pipefd_pai_filho) == -1){
    perror("Falha ao criar pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("Fork Failed");
    return 1;
  }
  
  //PROCESSO FILHO
  if (pid == 0) {  
    close(pipefd_filho_pai[1]); //fecha escrita filho --> pai
    close(pipefd_pai_filho[0]); // fecha leitura pai --> filho
    for (int i = 0; i < n; i++){
      if(direcoes[i] == 0){ //SUBIDA
        if (t[i] >= fim_descida){
          fim_subida = t[i] + 10;
        }else{
          fim_subida = fim_descida + 10; 
        }
      }
    }

    write(pipefd_pai_filho[1], &fim_subida, sizeof(fim_subida));
    close(pipefd_pai_filho[1]);

    // Aguarda a última descida do pai
    read(pipefd_filho_pai[0], &fim_descida, sizeof(fim_descida));
    close(pipefd_filho_pai[0]);
    exit(EXIT_SUCESS)
    
  } 
  //PROCESSO PAI
  else {  
    close(pipefd_filho_pai[0]); //fecha leitura filho --> pai 
    close(pipefd_filho_pai[1]); //fecha escrita pai --> filho
    
    read(pipefd_pai_filho[0], &fim_subida, sizeof(fim_subida));

    for (int i = 0; i < n; i++){  
      if (direcoes[i] == 1){ //DESCIDA
        if (t[i] >= fim_subida){
          fim_descida = t[i] + 10;
        }
        else{
          fim_descida = fim_subida + 10;
        }
      }
    }    
    // Envia o tempo final de descida de volta para o filho
    write(pipefd_filho_pai[1], &fim_descida, sizeof(fim_descida));
    close(pipefd_filho_pai[1]);
    wait(NULL); // Espera pelo término do filho

    
    tempo_final = (fim_subida > fim_descida) ? fim_subida : fim_descida;
    printf("Tempo final: %d\n", tempo_final);
    close(pipefd_pai_filho[0]);
        
    }
  return 0;
}
