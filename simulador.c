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

void initCommunication() {

    /* Cria socket stream */

	if ((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) < 0)
		perror("server: can't open stream socket");

	/* Primeiro uma limpeza preventiva!
	   Dados para o socket stream: tipo + nome do ficheiro.
         O ficheiro serve para que os clientes possam identificar o servidor */

	// bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, UNIXSTR_PATH);

      /* O servidor  quem cria o ficheiro que identifica o socket.
         Elimina o ficheiro, para o caso de algo ter ficado pendurado.
         Em seguida associa o socket ao ficheiro. 
         A dimenso a indicar ao bind no  a da estrutura, pois depende
         do nome do ficheiro */

	servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0)
		perror("connect error");

}

void main () {

    initSimulation();
    initThreads();
    initCommunication();
    // readConfig();
    calculateRunningTimeShop();
    // createClient(2);
    // createEmployee(1);
    askForPoncha(2, 'B');

    closeFile(logFile);

}