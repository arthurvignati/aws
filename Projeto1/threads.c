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




