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
#include <math.h>

// Macros

#define UNIXSTR_PATH "/tmp/str_r"
#define UNIXDG_PATH  "/tmp/dgx_r"
#define UNIXDG_TMP   "/tmp/dg_r"

// Variáveis

char messageToLog[128];
char* writeToLog;
FILE* logFile;

time_t     UNIXts;
struct tm  ts;
char       hmsTimeStamp[80];

int maxClients;
int spawnedClients;
int durationOpen;

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
int unitsSoldCoffeeA;
int unitsSoldCoffeeB;
int unitsSoldCoffeeC;
int avgTimeToServeCoffeeA;
int avgTimeToServeCoffeeB;
int avgTimeToServeCoffeeC;

int canWriteStats;
int currentTime;
int timeStartOfSimulation;
int waitingTimeInLine;
int maxClientsPerEmployee;
int actualEmployeesUsedNow = 1;
int clientsLeftStore;
int unitsCoffeeA;
int unitsCoffeeB;
int unitsCoffeeC;
int stockWarehouse;
int idClient = 0;
int probWithdrawl;

int outputSuccessful;
char simBuffer[256];
int opInt;

int halt;

int simPause;

//int unitsBought;
//int coffee;

int probChangeOrder;

int timeToServeCoffeeA; // importante para inicialização
int timeToServeCoffeeB; // importante para inicialização
int timeToServeCoffeeC; // importante para inicialização

int timeToServeClient;

// Variáveis - SOCKETS

struct sockaddr_un simSocketAddress;
int simSocketAddressLength = sizeof(struct sockaddr_un);

int monSocketConnection;

int client_socket;
struct sockaddr_un monSocketAddress;
int monLength;
int monSocket;
int simSocketAddressLength;


// Sockets

struct sockaddr_un serverAddr;
struct sockaddr_un clientAddr;
int sockfd;
int newsockfd;
int lengthServer;

// Arrays

char operation[64];

// Trincos

pthread_mutex_t someMutex;

// Threads

pthread_t tClient;

// Semáforos

sem_t semEmployee;
sem_t semQueueManager;
sem_t semRestock;
sem_t semAvailableProduct;

// Funções personalizadas

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

    printf("limpei logfile\n");

}

void writeLogFiles(char* writeToLog) {

    // openLogFile();
    //pthread_mutex_lock(&someMutex);

    char *timeStamp = getTimeStamp();
    printf("%s %s", timeStamp, writeToLog);
    fprintf(logFile, "%s %s", timeStamp, writeToLog);

    //pthread_mutex_unlock(&someMutex);

    // closeFile(logFile);
}

void openLogFile() {

    logFile = fopen("log.txt", "a");

    printf("abri logfile\n");

}

void closeFile(FILE* fileToClose) {

    fclose(fileToClose);

}

int getRandomNumber(int maxNumber) {

    srand(time(NULL));

    int randomNumber;

    randomNumber = rand() % maxNumber+1;

    //printf("Número qualquer gerado aleatoriamente: %d\n", randomNumber);

    sleep(1);

    return randomNumber;

}

void writeStatsToLog() {

    if((createdClients - clientsInLine) != 0) {
        avgTimeWaitingClientsInLine = waitingTimeInLine / (createdClients - clientsInLine);
    }

    if(unitsSoldCoffeeA != 0) {
        avgTimeToServeCoffeeA = timeToServeCoffeeA / unitsSoldCoffeeA;
    }

    if(unitsSoldCoffeeB != 0) {
        avgTimeToServeCoffeeB = timeToServeCoffeeB / unitsSoldCoffeeB;
    }

    if(unitsSoldCoffeeC != 0) {
        avgTimeToServeCoffeeC = timeToServeCoffeeC / unitsSoldCoffeeC;
    }

    //currentTime = time(NULL);

    //if (logFile == NULL) {
        //open(logFile, "a+");
    //}

    fprintf(logFile, "┌─────────────────────────────────────────────────────────────┐\n");
    fprintf(logFile, "│                         Estatisticas                        │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Geral ###                                               │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Duração da simulação: %d                                     │\n", currentTime-timeStartOfSimulation);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Clientes ###                                            │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Clientes criados na simulação: %d                            │\n", createdClients);
    fprintf(logFile, "│Clientes à espera na fila: %d                                │\n", clientsInLine);
    fprintf(logFile, "│Tempo médio de espera em fila: %d                            │\n", avgTimeWaitingClientsInLine);
    fprintf(logFile, "│Clientes que mudaram o seu pedido: %d                        │\n", totalChangedOrder);
    fprintf(logFile, "│Clientes que desistiram: %d                                  │\n", totalWithdrawls);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Empregados ###                                          │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Empregados ao serviço no máximo: %d                          │\n", maxEmployeesUsed);
    fprintf(logFile, "│Empregados ao serviço: %d                                    │\n", actualEmployeesUsedNow);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Cafés ###                                               │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Vendas do café 1: %d                                         │\n", unitsSoldCoffeeA);
    fprintf(logFile, "│Vendas do café 2: %d                                         │\n", unitsSoldCoffeeB);
    fprintf(logFile, "│Vendas do café 3: %d                                         │\n", unitsSoldCoffeeC);
    fprintf(logFile, "│Tempo médio de serviço do café 1: %d                         │\n", avgTimeToServeCoffeeA);
    fprintf(logFile, "│Tempo médio de serviço do café 2: %d                         │\n", avgTimeToServeCoffeeB);
    fprintf(logFile, "│Tempo médio de serviço do café 3: %d                         │\n", avgTimeToServeCoffeeC);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");

    fclose(logFile);

}
