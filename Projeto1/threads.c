#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct EscadaArgs{
    int n;
    int* t;
    int* direcoes;
} EscadaArgs;

int fim_subida = 0, fim_descida = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pode_descer = PTHREAD_COND_INITIALIZER;
pthread_cond_t pode_subir = PTHREAD_COND_INITIALIZER;



