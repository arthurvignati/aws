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
