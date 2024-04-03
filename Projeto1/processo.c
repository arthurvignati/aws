#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//#define LEITURA 0
//#define ESCRITA 1

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
    close(pipefd[1]);

    wait(NULL);
    read(pipefd[0], &fim_subida, sizeof(fim_subida));

    for (int i = 0; i < n; i++){
      if (direcoes[i] == 1){
        if (t[i] >= fim_subida){
          fim_descida = t[i] + 10;
        }
        else{
          fim_descida = fim_subida + 10;
        }
      }
    }

    tempo_final = (fim_subida > fim_descida) ? fim_subida : fim_descida;
    printf("Tempo final: %d\n", tempo_final);
    close(pipefd[0]);
    return 0;
    
    }
}
