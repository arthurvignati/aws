#define _GNU_SOURCE
#include <malloc.h>
#include <pthread.h> 
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIBER_STACK 1024 * 64

struct c{
int saldo;
};

typedef struct c conta;
conta from, to;
int valor;
pthread_mutex_t lock; //Declara um mutex

struct transfer{
conta *from;
conta *to;
int valor;
char direcao[12];
char fromSaida[10];
char toSaida[10];
};
