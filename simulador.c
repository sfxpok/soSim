#include "libs.h"

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

void readConfig() {

    // Adiciona uma excepção qualquer para valores disparatados no parâmetros

    FILE * fileConfig = fopen("config.conf", "r");

    char param[128];
    int value;

    if (fileConfig == NULL) {
        printf("Erro ao abrir o ficheiro. O programa irá usar valores pré-definidos.");

        // Valores pré-definidos
        simulador.maxClients = 3;
        simulador.spawnedClients = 6;
        estatistica.avgTimeArrivalClients = 3;
        simulador.timeToServePonchaA = 2;
        simulador.timeToServePonchaB = 3;
        simulador.timeToServePonchaC = 4;
        simulador.probWithdrawl = 2;
        simulador.openingTime = 10;
        simulador.closingTime = 13;
        simulador.timeCounter = 0;
        simulador.isItOpen = 1;
        estatistica.durationOpen = 0;
    }

    else {
        printf("A ler o ficheiro de configuração...\n");

        while(fscanf(fileConfig, "%s %d\n", param, &value) != EOF) {

            if (strcmp(param, "maxClients") == 0) simulador.maxClients = value;
            else if (strcmp(param, "spawnedClients") == 0) simulador.spawnedClients = value;
            else if (strcmp(param, "avgTimeArrivalClients") == 0) estatistica.avgTimeArrivalClients = value;
            else if (strcmp(param, "timeToServePonchaA") == 0) simulador.timeToServePonchaA = value;
            else if (strcmp(param, "timeToServePonchaB") == 0) simulador.timeToServePonchaB = value;
            else if (strcmp(param, "timeToServePonchaC") == 0) simulador.timeToServePonchaC = value;
            else if (strcmp(param, "probWithdrawl") == 0) simulador.probWithdrawl = value;
            else if (strcmp(param, "openingTime") == 0) simulador.openingTime = value;
            else if (strcmp(param, "closingTime") == 0) simulador.closingTime = value;
            else if (strcmp(param, "timeCounter") == 0) simulador.timeCounter = value;
            else if (strcmp(param, "isItOpen") == 0) simulador.isItOpen = value;
            else if (strcmp(param, "durationOpen") == 0) estatistica.durationOpen = value;

        }

        fclose(fileConfig);
        printf("Inicialização feita.\n");
    }

}

void writeOutputToMonitor(char* writeToMonitor) {
    
    printf("%s", writeToMonitor);

}

void createClient(int idClient) {

    // printf("O cliente %d acabou de chegar.\n", idClient);
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", idClient);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);

}

void createEmployee(int idEmployee) {
    
    // printf("O empregado %d chegou à loja.", idEmployee);
    snprintf(messageToLog, sizeof(messageToLog), "O empregado %d chegou à loja.\n", idEmployee);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);

}

void calculateRunningTimeShop() {
    
    estatistica.durationOpen = (simulador.closingTime - simulador.openingTime) * 60;

    snprintf(messageToLog, sizeof(messageToLog), "A loja está aberta durante %d minutos.\n", estatistica.durationOpen);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);
    
}

void giveUpClient(int idClient) {

    // printf("Cliente %d desistiu.\n", idClient);
    snprintf(messageToLog, sizeof(messageToLog), "Cliente %d desistiu.\n", idClient);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);

}

void askForPoncha(int idClient, char charPoncha) {

    // printf("O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);

    switch (charPoncha) {
        case 'A':
            // da-lhe poncha A

            if (simulador.unitsPonchaA < 2) {
                // cliente espera
            }

            snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);
            writeOutputToMonitor(messageToLog);
            writeLogFiles(messageToLog);

            break;
        case 'B':
            // da-lhe poncha B

            if (simulador.unitsPonchaB < 2) {
                // cliente espera
            }

            snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);
            writeOutputToMonitor(messageToLog);
            writeLogFiles(messageToLog);

            break;
        case 'C':
            // da-lhe poncha C

            if (simulador.unitsPonchaC < 2) {
                // cliente espera
            }

            snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);
            writeOutputToMonitor(messageToLog);
            writeLogFiles(messageToLog);

            break;
    }

}

void givePonchaToClient(int idClient, char charPoncha, int idEmployee) {
    //
}

void changeOrder() {
    //
}

void appendFinalReport() {
    //
}

void restockPoncha(int idEmployee, char charPoncha) {

    switch (charPoncha) {
        case 'a':
            // repoe poncha A
            printf("O empregado %d repôs a poncha %c.\n", idEmployee, charPoncha);
            break;
        case 'b':
            // repoe poncha B
            printf("O empregado %d repôs a poncha %c.\n", idEmployee, charPoncha);
            break;
        case 'c':
            // repoe poncha C
            printf("O empregado %d repôs a poncha %c.\n", idEmployee, charPoncha);
            break;
    }

}

void moveEmployeeToCashier(int idEmployee) {
    //
}

void moveEmployeeToWarehouse(int idEmployee) {
    //
}

void checkIfProductIsOutOfStock(char charPoncha) {
    //
}

void initSimulation() {
    readConfig();
    cleanLogFile();
    openLogFile();
}

void *THREADCreateClient(void *tid) {

    // printf("I reached the thread function\n");
    printf("PID do cliente: %d\n", getpid());

    createClient(3);

    // return 0;

}

void *THREADCreateEmployee(void *tid) {

    printf("PID do empregado: %d\n", getpid());

    createEmployee(4);

}

void initThreads() {

    pthread_t tMessages;
    // pthread_create(&tMessages, NULL, &messages, NULL);

    // é preciso mais 3 threads: mensagens (entre sim e mon), 
    // gerente e repositor

    pthread_t tClient;
    pthread_create(&tClient, NULL, &THREADCreateClient, NULL);

    pthread_join(tClient, NULL);

    pthread_t tEmployee;
    pthread_create(&tEmployee, NULL, &THREADCreateEmployee, NULL);

    pthread_join(tEmployee, NULL);

    // printf("dd\n");

}

int connectSocket() {

    struct sockaddr_in address; 
    // int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
/*     send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0;  */
}

pthread_mutex_t msg;

void sendMessages() {
    
    pthread_mutex_lock(&msg);

    // EDITA ISTO

    if ((send(sockfd, messageToLog, strlen(messageToLog), 0)) < 0)
    {
        printf("Failed to send...\n");
        //Retry sending
        //send(sock, str, TAMANHO_MSG, 0);
    } else {
        send(sockfd, messageToLog, strlen(messageToLog), 0);
    }

    pthread_mutex_unlock(&msg);

}

void initCommunication() {

}

void closeSocket() {
    close(sockfd);
    exit(0);
}

void main () {

    initSimulation();
    connectSocket();
    //initThreads();
    //initCommunication();
    //readConfig();
    //calculateRunningTimeShop();
    createClient(2);
    //createEmployee(1);
    //askForPoncha(2, 'B');

    closeFile(logFile);
    closeSocket();

}