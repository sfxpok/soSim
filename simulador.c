#include "libs.h"
#include "unix.h"

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

pthread_mutex_t msg;

void sendMessages(int idEvent) {

    sprintf(messageToLog, "%d", idEvent);

    pthread_mutex_lock(&msg);

    // EDITA ISTO

    if ((send(simSocket, messageToLog, strlen(messageToLog), 0)) < 0)
    {
        printf("Failed to send...\n");
        //Retry sending
        //send(sock, str, TAMANHO_MSG, 0);
    } else {
        send(simSocket, messageToLog, strlen(messageToLog), 0);
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

int simLength;
int simSocketConnection;

int startSimulatorSocket() {

     // create a socket
    
    if ((simSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("Não foi possível criar a socket.\n");
        return -1;
    }

    printf("Socket foi criada.\n");

    // specify an address for the socket
    //struct sockaddr_in simSocketAddress;
    simSocketAddress.sun_family = AF_UNIX;
    //simSocketAddress.sun_port = htons(PORT);
    strcpy(simSocketAddress.sun_path, UNIXSTR_PATH);
    //simSocketAddress.sun_addr.s_addr = INADDR_ANY;
    simLength = strlen(simSocketAddress.sun_path) + sizeof(simSocketAddress.sun_family);

    if (connect(simSocket, (struct sockaddr *) &simSocketAddress, simLength) < 0) {
        printf("Conexão falhada.\n");
        return -1;
    }

    printf("Conexão feita.\n");
    
    // recieve data from the server
    //char server_response[256];
    //recv(simSocket, &server_response, sizeof(server_response), 0);

    // print out the server's response
    //printf("The server sent the data: %s\n", server_response);

    // and then close the socket
    // close(simSocket);

    return 0;

}

void altStartSimulatorSocket() {
    //Criacao do socket UNIX e associacao ao Simulador
    if ((simSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        perror("cant open socket stream");
    simSocketAddress.sun_family = AF_UNIX;
    strcpy(simSocketAddress.sun_path, UNIXSTR_PATH);
    simLength = strlen(simSocketAddress.sun_path) + sizeof(simSocketAddress.sun_family);
    unlink(UNIXSTR_PATH);
    if (bind(simSocket, (struct sockaddr *)&simSocketAddress, simLength) < 0)
        perror("cant bind local address");
    listen(simSocket, 1);

    printf("alt socket criada\n");

}

void closeSocket() {
    close(simSocket);
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

/*

Recebe mensagens do simulador e envia pelo socket

*/

void *recMSG() {

    printf("tou na thread das mensagens\n");

    while(1) {


        printf("tou no loop\n");



        if((outputSuccessful=recv(simSocket, opInt, sizeof(opInt), 0)) > 0) {

            printf("tou dentro do recv\n");

            simBuffer[outputSuccessful] = "\0";

            switch(opInt) {

                case 1:
                    printf("\nSim init\n");
                    isItOpen = 1;
                    break;

                case 2:
                    printf("\nSim pause\n");
                    isItOpen = 0;
                    break;

            }

        }

        else {

            if (outputSuccessful < 0) {
                printf("Erro no recv");
            }
            else {
                printf("\nServidor não tem conexão.\n");
            }

            exit(1);

        }

    }

    closeSocket();
    return NULL;

}

void *mensagens(void *tid)
{
    int n;
    char buffer[256];
    //Ciclo que fica a espera das respostas do Simulador para apresentar os seus resultados
    while (1)
    {
        do
        {
            if ((n = recv(simSocket, buffer, sizeof(buffer), 0)) <= 0)
            {

                if (n < 0)
                    perror("recv");
                else
                    printf("\nServer closed connection\n");
                halt = 1;
                exit(1);
            }
            else
            {
                buffer[n] = '\0';
                if (!strcmp(buffer, "start\n"))
                {
                    printf("\nSimulacao iniciada\n\n");
                    isItOpen = 1;
                    //pausa = 0;
                }
                if (!strcmp(buffer, "pause\n"))
                {
                    printf("\nSimulacao parada\n\n");
                    //pausa = 1;
                    sprintf(buffer, "pause");
                    send(simSocket, buffer, sizeof(buffer), 0);
                }
            }
        } while (!halt);
    }
    close(simSocket);
    return NULL;
}

void threadMessage() {

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &mensagens, &simSocket);


}

/*

Funcionamento do gestor de filas de clientes

*/

void *clientManager(void *tid) {
    //
}

/*

Funcionamento do empregado

*/

void *employee(void *tid) {
    //
}

/*

Funcionamento do cliente

*/

void *client(void *tid) {
    //
}

void threadsShop() {

    pthread_t tClientManager;
    pthread_create(&tClientManager, NULL, &clientManager, NULL);

    pthread_t tEmployee;
    pthread_create(&tEmployee, NULL, employee, NULL);

}

void closeShop() {
    printf("A loja está fechada, mas falta atender os clientes em fila.\n");

    while(clientsInLine != 0) {
        printf("Já não existem clientes.\n");
    }

    printf("Simulação term.\n");

    isItOpen = 0;
    close(simSocket);

}

void sleepingShop() {

    while(time(NULL) < closingTime) {
        while(!isItOpen) {

            pthread_create(&tClient, NULL, client, NULL);
            sleep((rand() % avgTimeArrivalClients + 1) + avgTimeArrivalClients * 0.5);

        }
    }

    //closeShop();

}

void shopRuntime() {

/*     while(isItOpen) {

        openingTime = time(NULL);
        closingTime = openingTime + timeCounter;

        threadsShop();
        sleepingShop();
        closeShop();

    } */

    while(isItOpen) {
        openingTime = time(NULL);
    }

        closingTime = openingTime + timeCounter;

        threadsShop();
        sleepingShop();
        closeShop();

    

}

void simpleMessages() {

    sprintf(messageToLog, "clientIsHere %s", getTimeStamp());
	send(simSocket, messageToLog, sizeof(messageToLog), 0);

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

    //startSimulatorSocket();
    altStartSimulatorSocket();

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &mensagens, &simSocket);

    //threadMessage();
    //shopRuntime();
    //simpleMessages();
    //threadMessage();



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
