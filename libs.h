// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h> 
#include <semaphore.h>

#include <signal.h>

#include <sys/types.h>
#include <unistd.h>

// Macros

#define UNIXSTR_PATH "/tmp/a2042416"
#define UNIXDG_PATH  "/tmp/s.unixdfddffdfdgx"
#define UNIXDG_TMP   "/tmp/dgXXXXXfdjhfdjhfdXX"
#define PORT 8080 

// Variáveis

char messageToLog[128];
char* writeToLog;
FILE* logFile;

time_t     UNIXts;
struct tm  ts;
char       hmsTimeStamp[80];

// Variáveis - SOCKETS

	int sockfd, newsockfd, clilen, childpid, servlen;
	struct sockaddr_un cli_addr, serv_addr;

// Semáforos

sem_t semLine, semPA, semPB, semPC;

// Estruturas de dados

struct shop {
    int maxClients;
    int maxEmployees;
    int maxClientsPerEmployee;
    int spawnedClients;
    int timeToServePonchaA; // importante para inicialização
    int timeToServePonchaB; // importante para inicialização
    int timeToServePonchaC; // importante para inicialização
    int unitsPonchaA;
    int unitsPonchaB;
    int unitsPonchaC;
    int replacersProducts;
    int probChangeOrder;
    int probWithdrawl; // importante para inicialização
    int openingTime;
    int closingTime;
    int timeCounter;
    int isItOpen;
};

struct stats {
    int totalWithdrawls;
    int avgTimeArrivalClients; // importante para inicialização
    int totalClients;
    int waitingClientsInLine;
    int avgTimeWaitingClientsInLine;
    int totalChangedOrder;
    int maxEmployeesUsed;
    int actualEmployeesUsedNow;
    int unitsSoldPonchaA;
    int unitsSoldPonchaB;
    int unitsSoldPonchaC;
    int avgTimeToServePonchaA;
    int avgTimeToServePonchaB;
    int avgTimeToServePonchaC;
    int durationOpen; // importante para inicialização
};

// Threads

// pthread_t threadClient;

// Inicializações

struct shop simulador;
struct stats estatistica;

// Funções personalizadas

pthread_mutex_t mutexPrintToScreen;

/* void print_message(FILE * file, char * str)
{
  pthread_mutex_lock(&prt_msg);

  prt_file_screen(file, str);

  pthread_mutex_unlock(&prt_msg);
}

void prt_file_screen(FILE * file, char * str)
{
  // char cat[TAMANHO_MSG];

  strcpy(cat,getRealTime());
  strcat(cat, " - ");
  strcat(cat, str);

  puts(cat);
  fprintf(file,"%s\n",cat);
} */