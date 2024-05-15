#define _GNU_SOURCE
#include <malloc.h>
#include <pthread.h> 
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

struct c {
int saldo;
};

typedef struct c conta;
conta from, to;
int valor;
pthread_mutex_t lock; // Declara um mutex

struct transfer{
conta *from;
conta *to;
int valor;
char direcao[12];
char fromSaida[10];
char toSaida[10];
};

//Função executada pelo thread na fila
void* transferencia(void *arg) {
  struct transfer *args = (struct transfer *)arg;
  pthread_mutex_lock(&lock); //trava o mutex 
  if (args->from->saldo >= args->valor){
    args->from->saldo -= args->valor;
    args->to->saldo += args->valor;
    printf("Transferência realizada com sucesso (%s)\n", args->direcao);
  }else{
    printf("Não é possível enviar dinheiro por saldo insuficiente (%s)!\n", args->direcao);
  }
  printf("Saldo de c1(%s): %d\n", args->fromSaida, args->from->saldo);
  printf("Saldo de c2(%s): %d\n", args->toSaida, args->to->saldo);
  pthread_mutex_unlock(&lock); // Destrava o mutex
  free(arg);
  return NULL;
}

void trocarContas(char *direcao, char *fromSaida, char *toSaida){
  pthread_mutex_lock(&lock);
  conta aux = from;
  from = to;
  to = aux;
  pthread_mutex_unlock(&lock);
  snprintf(direcao, 12, "To → From");
  snprintf(fromSaida, 10, "to");
  snprintf(toSaida, 10, "from");
}

int main(){
  int i;

  //inicializar mutex
  if (pthread_mutex_init(&lock, NULL) != 0){
    perror("Falha mutex_init");
    exit(1);
  }
  
  from.saldo = 100;
  to.saldo = 100;

  printf("Transferindo 10 (10 vezes) para a conta c2\n");
  valor = 10;
  int transferCount = 0;
  char direcao[12] = "From → To";
  char fromSaida[10] = "from";
  char toSaida[10] = "to";

  for (i = 0; i < 100; i++){
    struct transfer *args = malloc(sizeof(struct transfer));
    if (args == NULL){
      perror("Não foi possível alocar memória");
      exit(1);
    }
    args->from = &from;
    args->to = &to;
    args->valor = valor;
    snprintf(args->direcao, sizeof(args->direcao), "%s", direcao);
    snprintf(args->fromSaida, sizeof(args->fromSaida), "%s", fromSaida);
    snprintf(args->toSaida, sizeof(args->toSaida), "%s", toSaida);

    pthread_t thread;
    if (pthread_create(&thread, NULL, transferencia, (void*)args) != 0){
      perror("pthread_create");
      exit(2);
    }
    pthread_join(thread, NULL);
    transferCount++;
  
  if (transferCount % 10 == 0) {
    printf("Transferências concluídas!\n");
    printf("Saldo de c1(%s): %d\n", fromSaida, from.saldo);
    printf("Saldo de c2(%s): %d\n", toSaida, to.saldo);
    if (from.saldo == 0 || to.saldo == 0){
      trocarContas(direcao, fromSaida, toSaida);
      printf("---------------------------------------------------\n");
      printf("Contas Trocadas. Transferindo 10 (10 vezes) %s\n", direcao);
    }
  }
    if (from.saldo == 100 && to.saldo == 100){
    break;
  }
  }
  pthread_mutex_destroy(&lock);

  printf("Transferências concluídas!\n");
  printf("Saldo de c1: %d\n", from.saldo);
  printf("Saldo de c2: %d\n", to.saldo);

  return 0;
  
}
