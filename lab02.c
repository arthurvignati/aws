#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define LEITURA 0
#define ESCRITA 1

int main(void) {

  //inicializa os pipe's do filho e do pai antes do fork para os dois herdarem
    int pipefd_pai_filho[2];  //comunicação pai para filho
    int pipefd_filho_pai[2];  //comunicação filho para pai
    char mensagemByte;        //var que armazena um byte da mensagem
    pid_t pid;                

    if (pipe(pipefd_pai_filho) == -1 || pipe(pipefd_filho_pai) == -1) {
        fprintf(stderr, "Falha ao criar pipe\n");
        return 1; 
    }

   // Fork --> divide o processo entre pai e filho
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");  
        return 1;
    }

    if (pid == 0) {  //PROCESSO FILHO
      
        close(pipefd_pai_filho[ESCRITA]); //fecha escrita no pipe pai-filho
        close(pipefd_filho_pai[LEITURA]); //fecha leitura no pipe filho-pai
      
        //ler as mensagens do pipe pai para filho
        while (read(pipefd_pai_filho[LEITURA], &mensagemByte, 1) > 0) {
            printf("%c", mensagemByte); 
        }
        printf("\n");

        // enviar mensagem filho para o pai
        char msg_filho[] = "Mensagem do filho\n";
        write(pipefd_filho_pai[ESCRITA], msg_filho, sizeof(msg_filho) - 1);

        close(pipefd_pai_filho[LEITURA]); //fecha leitura do pipe pai para filho
        close(pipefd_filho_pai[ESCRITA]); //fecha escrita do pipe filho-pai
        exit(0);


      
    } else {  //PROCESSO PAI
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