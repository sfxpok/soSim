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

#include <stdbool.h>

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

int simSocket;
int isItOpen;
int openingTime;
int closingTime;
int timeCounter;
int avgTimeArrivalClients;
int createdClients;
int clientsInLine;
int avgTimeWaitingClientsInLine;
int totalWithdrawls;
int totalChangedOrder;
int maxEmployeesUsed;
int actualEmployeesUsedNow;
int unitsSoldPonchaA;
int unitsSoldPonchaB;
int unitsSoldPonchaC;
int avgTimeToServePonchaA;
int avgTimeToServePonchaB;
int avgTimeToServePonchaC;

// Variáveis - SOCKETS

int sockfd, newsockfd, clilen, childpid, servlen;
struct sockaddr_un cli_addr, serv_addr;

struct sockaddr_in simSocketAddress;
int simSocketAddressLength = sizeof(struct sockaddr_in);

int monSocketConnection;

// Semáforos

sem_t semLine, semPA, semPB, semPC;
sem_t semLoja;

pthread_t tClient;

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

char* getTimeStamp() {

    // Get current time
    time(&UNIXts);

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&UNIXts);
    strftime(hmsTimeStamp, sizeof(hmsTimeStamp), "%H:%M:%S", &ts);
    return hmsTimeStamp;
}

void cleanLogFile() {

    FILE * logFile = fopen("log.txt", "w"); // A flag "w" cria um novo ficheiro de raíz
    fclose(logFile);

}

void writeLogFiles(char* writeToLog) {

    // openLogFile();

    char *timeStamp = getTimeStamp();
    fprintf(logFile, "%s %s", timeStamp, writeToLog);

    // closeFile(logFile);
}

void openLogFile() {

    logFile = fopen("log.txt", "a");

}

void closeFile(FILE* fileToClose) {

    fclose(fileToClose);

}

void writeOutputToMonitor(char* writeToMonitor) {

    printf("%s", writeToMonitor);

}

void printToScreen(FILE *logFile, char *string) {

    pthread_mutex_lock(&mutexPrintToScreen);

    printf("LOCKED\n");

    // snprintf(messageToLog, sizeof(messageToLog), "%s", string);
    // fprintf(logFile, "%s", string);
    writeOutputToMonitor(string);
    writeLogFiles(string);

    pthread_mutex_unlock(&mutexPrintToScreen);

    printf("UNLOCKED\n");

}

int getRandomNumber(int maxNumber) {

    srand(time(NULL));

    int randomNumber;

    randomNumber = rand() % maxNumber+1;

    printf("%d\n", randomNumber);

    sleep(1);

    return randomNumber;

}
