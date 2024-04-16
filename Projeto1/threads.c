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

EscadaArgs lerPassageiros(char* caminhoArquivo) {
    FILE* arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", caminhoArquivo);
        exit(1);
    } else {
      printf("Arquivo %s aberto com sucesso.\n", caminhoArquivo);
  }

    EscadaArgs escadaArgs;

    fscanf(arquivo, "%d", &escadaArgs.n);

    escadaArgs.t = (int*)malloc(escadaArgs.n * sizeof(int));
    escadaArgs.direcoes = (int*)malloc(escadaArgs.n * sizeof(int));

    for (int i = 0; i < escadaArgs.n; i++) {
        fscanf(arquivo, "%d %d", &escadaArgs.t[i], &escadaArgs.direcoes[i]);
    }

    fclose(arquivo);

    return escadaArgs;
}


void* subida(void* arg) {
    EscadaArgs* escadaArgs = (EscadaArgs*) arg;
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < escadaArgs->n; i++) {
        if (escadaArgs->direcoes[i] == 0) {
            if (escadaArgs->t[i] >= fim_descida) {
                fim_subida = escadaArgs->t[i] + 10;
            } else {
                fim_subida = fim_descida + 10;
            }
        }
    }

    pthread_cond_signal(&pode_descer);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* descida(void* arg) {
    EscadaArgs* escadaArgs = (EscadaArgs*) arg;
    pthread_mutex_lock(&mutex);

    while (fim_subida == 0) {
        pthread_cond_wait(&pode_descer, &mutex);
    }

    for (int i = 0; i < escadaArgs->n; i++) {
        if (escadaArgs->direcoes[i] == 1) {
            if (escadaArgs->t[i] >= fim_subida) {
                fim_descida = escadaArgs->t[i] + 10;
            } else {
                fim_descida = fim_subida + 10;
            }
        }
    }

    pthread_cond_signal(&pode_subir);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    pthread_t tid_subida, tid_descida;
    char* caminhoArquivo = "./input/E_58";
    EscadaArgs escadaArgs = lerPassageiros(caminhoArquivo);
    printf("Número de passageiros: %d\n", escadaArgs.n);
    
    for (int i = 0; i < escadaArgs.n; i++) {
        printf("Passageiro %d - Momento: %d, Direção: %d\n", i+1, escadaArgs.t[i], escadaArgs.direcoes[i]);
    }

    pthread_create(&tid_subida, NULL, subida, &escadaArgs);
    pthread_create(&tid_descida, NULL, descida, &escadaArgs);

    pthread_join(tid_subida, NULL);
    pthread_join(tid_descida, NULL);

    int tempoFinal = (fim_subida > fim_descida) ? fim_subida : fim_descida; 
    printf("Tempo final: T=%d\n", tempoFinal);
    free(escadaArgs.t);
    free(escadaArgs.direcoes);

    return 0; 
    
}
