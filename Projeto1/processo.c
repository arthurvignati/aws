#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE

typedef struct {
    int n;
    int* t;
    int* direcoes;
} Passageiros;

Passageiros lerPassageiros(const char* caminhoArquivo) {
  FILE* arquivo = fopen(caminhoArquivo, "r");
  if (arquivo == NULL) {
    fprintf(stderr, "Erro ao abrir o arquivo %s.\n", caminhoArquivo);
    exit(EXIT_FAILURE);
  } else{
      printf("Arquivo %s aberto com sucesso.\n", caminhoArquivo);
  }
  Passageiros p; 
  fscanf(arquivo, "%d", &p.n);
  p.t = (int*) malloc(p.n * sizeof(int));
  p.direcoes = (int*) malloc(p.n * sizeof(int));

  for (int i = 0; i < p.n; i++) {
    fscanf(arquivo, "%d %d", &p.t[i], &p.direcoes[i]);
  }
  fclose(arquivo);
  return p;  
}

int main() {
  char caminhoEntrada[100];
  printf("Utilize ./input/E_n, onde n será a entrada que você quer utilizar.\n");
  printf("Por Exemplo ./input/E_5\n");
  printf("Qual o caminho do arquivo de entrada: ");
  scanf("%s", caminhoEntrada);    
    
  Passageiros p = lerPassageiros(caminhoEntrada);
  printf("Número de passageiros: %d\n", p.n);
  
  int fim_subida = 0;
  int fim_descida = 0;
  int tempo_final = 0;
  int pipefd_filho_pai[2], pipefd_pai_filho[2];
  
  if (pipe(pipefd_filho_pai) == -1 || pipe(pipefd_pai_filho) == -1){
    perror("Falha ao criar pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("Fork Failed");
    exit(EXIT_FAILURE);
  }
  
  //PROCESSO FILHO
  if (pid == 0) {  
    close(pipefd_filho_pai[1]); //fecha escrita filho --> pai
    close(pipefd_pai_filho[0]); // fecha leitura pai --> filho
    
    for (int i = 0; i < p.n; i++){
      if(p.direcoes[i] == 0){ //SUBIDA
        if (p.t[i] >= fim_descida){
          fim_subida = p.t[i] + 10;
        }else{
          fim_subida = fim_descida + 10; 
        }
      }
    }

    write(pipefd_pai_filho[1], &fim_subida, sizeof(fim_subida));
    close(pipefd_pai_filho[1]);
    exit(EXIT_SUCCESS);    
   
    //PROCESSO PAI
  } else {  
    close(pipefd_filho_pai[0]); //fecha leitura filho --> pai 
    close(pipefd_filho_pai[1]); //fecha escrita pai --> filho
    
    read(pipefd_pai_filho[0], &fim_subida, sizeof(fim_subida));

    for (int i = 0; i < p.n; i++){  
      if (p.direcoes[i] == 1){ //DESCIDA
        if (p.t[i] >= fim_subida){
          fim_descida = p.t[i] + 10;
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
    close(pipefd_pai_filho[0]);
    
    tempo_final = (fim_subida > fim_descida) ? fim_subida : fim_descida;
    printf("Tempo final: %d\n", tempo_final);        
    }
  free(p.t);
  free(p.direcoes);
  return 0;
}
