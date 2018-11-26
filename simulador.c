#include "libs.h"

void readConfig() {

    // Adiciona uma excepção qualquer para valores disparatados no parâmetros
    // Como é que verifico se o ficheiro de configuração não está direito?
    // Talvez deixa o utilizador definir parâmetros caso não haja ficheiro de configuração?

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

    // pthread_t tMessages;
    // pthread_create(&tMessages, NULL, &messages, NULL);
    // pthread_join(tMessages, NULL);

    pthread_t tClient;
    pthread_create(&tClient, NULL, &THREADCreateClient, NULL);
    pthread_join(tClient, NULL);

    pthread_t tEmployee;
    pthread_create(&tEmployee, NULL, &THREADCreateEmployee, NULL);
    pthread_join(tEmployee, NULL);

    pthread_t tFileManage;
    // pthread_create(&tEmployee, NULL, &THREADCreateEmployee, NULL);
    // pthread_join(tFileManage, NULL);

    // printf("dd\n");

}

/* int connectSocket() {

    struct sockaddr_in address;
    //int sock = 0, valread;
    int valread;
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
    send(sockfd, messageToLog, strlen(messageToLog) , 0 );
    printf("Hello message sent\n");
    valread = read( sockfd , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
} */

pthread_mutex_t msg;

void sendMessages(int idEvent) {

    sprintf(messageToLog, "%d", idEvent);

    pthread_mutex_lock(&msg);

    // EDITA ISTO

    if ((send(network_socket, messageToLog, strlen(messageToLog), 0)) < 0)
    {
        printf("Failed to send...\n");
        //Retry sending
        //send(sock, str, TAMANHO_MSG, 0);
    } else {
        send(network_socket, messageToLog, strlen(messageToLog), 0);
        printf("Envio feito.\n");
    }

    pthread_mutex_unlock(&msg);

}

void initCommunication() {

}

/* void closeSocket() {
    close(sockfd);
    exit(0);
} */

void semaphores() {
    //
}

int giveUp;
int waitInLine;
bool leaveStore = false;
int clientsInLine;
time_t arrivalTime;

void * lifeOfClient() {

    pthread_t threadClient = pthread_self();

    sprintf(messageToLog, "O cliente (thread) %lu chegou.\n", threadClient);
    printToScreen(logFile, messageToLog);

    clientsInLine++;
    arrivalTime = time(NULL);

    waitInLine = getRandomNumber(10);
    sem_wait(&semLoja);

    while(!leaveStore) {

        giveUp = getRandomNumber(100);

        if (giveUp < 50) {
            leaveStore = true;
            //clientsInStore--;
        }

        waitInLine--;

    }

    clientsInLine--;
    sem_post(&semLoja);

    sprintf(messageToLog, "O cliente (thread) %lu vai sair da loja.", threadClient);
    printToScreen(logFile, messageToLog);

    return NULL;

}

/*

Criação da ligação entre o monitor (servidor) e o simulador (cliente).

*/

int TESTstartSocket() {

     // create a socket
    
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(network_socket == -1) {
        printf("Não foi possível criar a socket.\n");
        return -1;
    }

    printf("Socket foi criada.\n");

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // check for error with the connection
    if (connection_status == -1) {
        printf("Conexão falhada.\n");
        return -1;
    }

    printf("Conexão feita.\n");
    
    // recieve data from the server
    //char server_response[256];
    //recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out the server's response
    //printf("The server sent the data: %s\n", server_response);

    // and then close the socket
    // close(network_socket);

    return network_socket;

}

void closeSocket() {
    close(network_socket);
}

int server_socket;

void *sendingMessages() {

    int n;
	char buffer[256];

    while (1) {
        if((n=recv(server_socket, buffer, sizeof(buffer), 0)) > 0) {
            
        }
    }
}

void threadMessage() {

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &recMSG, NULL);


}

void simpleMessages() {

    sprintf(messageToLog, "clientIsHere %s", getTimeStamp());
	send(network_socket, messageToLog, sizeof(messageToLog), 0);

}

//char buf[1000] = {0};

void DEBUGcreateClient(int idClient) {

    // printf("O cliente %d acabou de chegar.\n", idClient);
    //snprintf(buf, 999, "O cliente %d acabou de chegar.\n", idClient);
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", idClient);
    printToScreen(logFile, messageToLog);
    //snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", idClient);
    // writeOutputToMonitor(messageToLog);
    // writeLogFiles(messageToLog);

}

int randomNumberLoop() {

    while(1) {
        getRandomNumber(25);
    }

}

void main () {

    // sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);

    initSimulation();
    simpleMessages();
    //DEBUGcreateClient(3);
    //TESTstartSocket();
    //semaphores();
    //initThreads();
    //initCommunication();
    //readConfig();
    //calculateRunningTimeShop();
    //createClient(2);
    //sendMessages();
    //newClient();
    //createEmployee(1);
    //askForPoncha(2, 'B');

    //closeFile(logFile);
    //closeSocket();

    //randomNumberLoop();

}
