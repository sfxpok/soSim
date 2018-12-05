#include "libs.h"

void readConfig()
{

    // Adiciona uma excepção qualquer para valores disparatados no parâmetros
    // Como é que verifico se o ficheiro de configuração não está direito?
    // Talvez deixa o utilizador definir parâmetros caso não haja ficheiro de configuração?

    FILE *fileConfig = fopen("config.conf", "r");

    char param[128];
    int value;

    if (fileConfig == NULL)
    {
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

    else
    {
        printf("A ler o ficheiro de configuração...\n");

        while (fscanf(fileConfig, "%s %d\n", param, &value) != EOF)
        {

            if (strcmp(param, "maxClients") == 0)
                simulador.maxClients = value;
            else if (strcmp(param, "spawnedClients") == 0)
                simulador.spawnedClients = value;
            else if (strcmp(param, "avgTimeArrivalClients") == 0)
                estatistica.avgTimeArrivalClients = value;
            else if (strcmp(param, "timeToServePonchaA") == 0)
                simulador.timeToServePonchaA = value;
            else if (strcmp(param, "timeToServePonchaB") == 0)
                simulador.timeToServePonchaB = value;
            else if (strcmp(param, "timeToServePonchaC") == 0)
                simulador.timeToServePonchaC = value;
            else if (strcmp(param, "probWithdrawl") == 0)
                simulador.probWithdrawl = value;
            else if (strcmp(param, "openingTime") == 0)
                simulador.openingTime = value;
            else if (strcmp(param, "closingTime") == 0)
                simulador.closingTime = value;
            else if (strcmp(param, "timeCounter") == 0)
                simulador.timeCounter = value;
            else if (strcmp(param, "isItOpen") == 0)
                simulador.isItOpen = value;
            else if (strcmp(param, "durationOpen") == 0)
                estatistica.durationOpen = value;
        }

        fclose(fileConfig);
        printf("Inicialização feita.\n");
    }
}

void createClient(int idClient)
{

    // printf("O cliente %d acabou de chegar.\n", idClient);
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", idClient);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);
}

void createEmployee(int idEmployee)
{

    // printf("O empregado %d chegou à loja.", idEmployee);
    snprintf(messageToLog, sizeof(messageToLog), "O empregado %d chegou à loja.\n", idEmployee);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);
}

void calculateRunningTimeShop()
{

    estatistica.durationOpen = (simulador.closingTime - simulador.openingTime) * 60;

    snprintf(messageToLog, sizeof(messageToLog), "A loja está aberta durante %d minutos.\n", estatistica.durationOpen);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);
}

void giveUpClient(int idClient)
{

    // printf("Cliente %d desistiu.\n", idClient);
    snprintf(messageToLog, sizeof(messageToLog), "Cliente %d desistiu.\n", idClient);
    writeOutputToMonitor(messageToLog);
    writeLogFiles(messageToLog);
}

void askForPoncha(int idClient, char charPoncha)
{

    // printf("O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);

    switch (charPoncha)
    {
    case 'A':
        // da-lhe poncha A

        if (simulador.unitsPonchaA < 2)
        {
            // cliente espera
        }

        snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);
        writeOutputToMonitor(messageToLog);
        writeLogFiles(messageToLog);

        break;
    case 'B':
        // da-lhe poncha B

        if (simulador.unitsPonchaB < 2)
        {
            // cliente espera
        }

        snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);
        writeOutputToMonitor(messageToLog);
        writeLogFiles(messageToLog);

        break;
    case 'C':
        // da-lhe poncha C

        if (simulador.unitsPonchaC < 2)
        {
            // cliente espera
        }

        snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela poncha %c.\n", idClient, charPoncha);
        writeOutputToMonitor(messageToLog);
        writeLogFiles(messageToLog);

        break;
    }
}

void givePonchaToClient(int idClient, char charPoncha, int idEmployee)
{
    //
}

void changeOrder()
{
    //
}

void appendFinalReport()
{
    //
}

void restockPoncha(int idEmployee, char charPoncha)
{

    switch (charPoncha)
    {
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

void moveEmployeeToCashier(int idEmployee)
{
    //
}

void moveEmployeeToWarehouse(int idEmployee)
{
    //
}

void checkIfProductIsOutOfStock(char charPoncha)
{
    //
}

void initSimulation()
{
    readConfig();
    cleanLogFile();
    openLogFile();
}

void *THREADCreateClient(void *tid)
{

    // printf("I reached the thread function\n");
    printf("PID do cliente: %d\n", getpid());

    createClient(3);

    // return 0;
}

void *THREADCreateEmployee(void *tid)
{

    printf("PID do empregado: %d\n", getpid());

    createEmployee(4);
}

void initThreads()
{

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

void sendMessages(int idEvent)
{

    sprintf(messageToLog, "%d", idEvent);

    pthread_mutex_lock(&msg);

    // EDITA ISTO

    if ((send(simSocket, messageToLog, strlen(messageToLog), 0)) < 0)
    {
        printf("Failed to send...\n");
        //Retry sending
        //send(sock, str, TAMANHO_MSG, 0);
    }
    else
    {
        send(simSocket, messageToLog, strlen(messageToLog), 0);
        printf("Envio feito.\n");
    }

    pthread_mutex_unlock(&msg);
}

void initCommunication() {
    //
}

/* int giveUp;
int waitInLine;
bool leaveStore = false;
time_t arrivalTime;

void *lifeOfClient()
{

    pthread_t threadClient = pthread_self();

    sprintf(messageToLog, "O cliente (thread) %lu chegou.\n", threadClient);
    printToScreen(logFile, messageToLog);

    clientsInLine++;
    arrivalTime = time(NULL);

    waitInLine = getRandomNumber(10);
    sem_wait(&semLoja);

    while (!leaveStore)
    {

        giveUp = getRandomNumber(100);

        if (giveUp < 50)
        {
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
} */

void closeSocket()
{
    close(simSocket);
}

/*

Funcionamento do gestor de filas de clientes

*/

pthread_mutex_t someMutex;
int numberOfEmployeesToWork;

void *clientManager(void *tid)
{

    char bufferMonitor[512];

    while(!simPause) {

        sem_wait(&semQueueManager);
        pthread_mutex_lock(&someMutex);

        numberOfEmployeesToWork = ((clientsInLine / maxClientsPerEmployee) + 1);

        if(numberOfEmployeesToWork > actualEmployeesUsedNow) {

            actualEmployeesUsedNow = numberOfEmployeesToWork;
            actualEmployeesUsedNow++;

            sem_post(&semEmployee);

            printf("O funcionário %d foi posto no serviço às %s\n", numberOfEmployeesToWork, getTimeStamp());

            sprintf(bufferMonitor, "AddEmployee %d %s", numberOfEmployeesToWork, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }
        else if(numberOfEmployeesToWork < actualEmployeesUsedNow) {
            
            actualEmployeesUsedNow = numberOfEmployeesToWork;
            actualEmployeesUsedNow--;

            printf("O funcionário %d deixou o serviço às %s\n", numberOfEmployeesToWork, getTimeStamp());

            sprintf(bufferMonitor, "RemoveEmployee %d %s", (numberOfEmployeesToWork+1), getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }
        else {
            sem_post(&semEmployee);
        }

        pthread_mutex_unlock(&someMutex);

    }
}

/*

Funcionamento do empregado

*/

void *employee(void *tid)
{
    char bufferMonitor[512];

    while(!simPause) {

        sem_wait(&semRestock);
        pthread_mutex_lock(&someMutex);

        if(unitsPonchaA <= 3) {

            sleep(1);

            unitsPonchaA = unitsPonchaA + stockWarehouse;

            printf("%d unidades do produto %c foram repostas às %s\n", stockWarehouse, 'A', getTimeStamp());

            sprintf(bufferMonitor, "RestockProduct %c %d %s", 'A', stockWarehouse, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }


        pthread_mutex_unlock(&someMutex);
        sem_post(&semAvailableProduct);

    }

}

/*

Funcionamento do cliente

*/

void *client(void *tid)
{
    
    char bufferMonitor[512];
    int thresholdToGiveUp;

    pthread_mutex_lock(&someMutex);

    int waitingTime = getRandomNumber(10);
    idClient++;
    clientsInLine++;

    time_t arrivalTime = time(NULL);

    printf("O cliente %d acabou de chegar às %s.\n", idClient, getTimeStamp());
	sprintf(bufferMonitor, "ClientArrived %d %s", idClient, getTimeStamp());
	send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

	pthread_mutex_unlock(&someMutex);

    sem_wait(&semEmployee);
    pthread_mutex_lock(&someMutex);

    clientsInLine--;

    if ((time(NULL) - arrivalTime) > waitingTime) {

        thresholdToGiveUp = getRandomNumber(100);

        if (thresholdToGiveUp <= probWithdrawl) {
            
        }

    }

}

void threadsShop()
{

    pthread_t tClientManager;
    pthread_create(&tClientManager, NULL, &clientManager, NULL);

    pthread_t tEmployee;
    pthread_create(&tEmployee, NULL, employee, NULL);
}

void closeShop()
{
    printf("A loja está fechada, mas falta atender os clientes em fila.\n");

    while (clientsInLine != 0)
    {
        printf("Já não existem clientes.\n");  // not sure...
    }

    printf("Simulação term.\n");

    isItOpen = 0;
    close(simSocket);
}

void sleepingShop()
{

    while (time(NULL) < closingTime)
    {
        while (!isItOpen){
            // não faz nada pausado da simulação
        }

        pthread_create(&tClient, NULL, client, NULL);
        sleep((rand() % avgTimeArrivalClients + 1) + avgTimeArrivalClients * 0.5);
    }

    //closeShop();
}

void shopRuntime()
{

    /*     while(isItOpen) {

        openingTime = time(NULL);
        closingTime = openingTime + timeCounter;

        threadsShop();
        sleepingShop();
        closeShop();

    } */

    openingTime = time(NULL);
    closingTime = openingTime + timeCounter;

    threadsShop();
    sleepingShop();
    closeShop();
}

void simpleMessages()
{

    sprintf(messageToLog, "clientIsHere %s", getTimeStamp());
    send(simSocket, messageToLog, sizeof(messageToLog), 0);
}

//char buf[1000] = {0};

void DEBUGcreateClient(int idClient)
{

    // printf("O cliente %d acabou de chegar.\n", idClient);
    //snprintf(buf, 999, "O cliente %d acabou de chegar.\n", idClient);
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", idClient);
    printToScreen(logFile, messageToLog);
    //snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", idClient);
    // writeOutputToMonitor(messageToLog);
    // writeLogFiles(messageToLog);
}

int randomNumberLoop()
{

    while (1)
    {
        getRandomNumber(25);
    }
}

// copypasta

void *pasta()
{
    int n;
    char buffer[256];
    //char operation[64];
    //Ciclo que fica a espera das respostas do Simulador para apresentar os seus resultados
    while (1)
    {
        if ((n = recv(sockfd, operation, sizeof(operation), 0)) > 0)
        {
            buffer[n] = '\0';
            operation[n] = '\0';

            if (!strcmp(buffer, "pause\n"))
            {
                printf("\nSimulacao parada\n\n");
                //pausa = 1;
                sprintf(buffer, "pause");
                send(sockfd, buffer, sizeof(buffer), 0);
            }

            if(!strcmp(operation, "init\n")) {

                printf("Simulação a correr...\n");

                isItOpen = 1;
                if (simPause) {
                    simPause = 0;
                }
            }

            if(!strcmp(operation, "halt\n")) {

                printf("Simulação em pausa...\n");

                if (!simPause) {
                    simPause = 1;
                }
            }
        }
        else
        {
            if (n < 0)
                printf("Erro na recepção de informação.");
            else
                printf("\nServidor foi desligado.\n");
            exit(1);
        }
    }
    close(sockfd);
    return NULL;
}

void *recMSGClient(void *tid)
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

/*

Criação da ligação entre o monitor (servidor) e o simulador (cliente).

*/

int simLength;
int simSocketConnection;

int startSimulatorClientSocket()
{

    // create a socket

    if ((simSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("Não foi possível criar a socket.\n");
        return -1;
    }

    printf("Socket foi criada.\n");

    // specify an address for the socket
    //struct sockaddr_in simSocketAddress;
    bzero((char *)&simSocketAddress, sizeof(simSocketAddress));
    simSocketAddress.sun_family = AF_UNIX;
    //simSocketAddress.sun_port = htons(PORT);
    strcpy(simSocketAddress.sun_path, UNIXSTR_PATH);
    //simSocketAddress.sun_addr.s_addr = INADDR_ANY;
    simLength = strlen(simSocketAddress.sun_path) + sizeof(simSocketAddress.sun_family);

    if (connect(simSocket, (struct sockaddr *)&simSocketAddress, simLength) < 0)
    {
        printf("Conexão falhada.\n");
        return -1;
    }

    printf("Conexão feita.\n");

    return 0;
}

void socketStartPleaseClient()
{

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("Simulador: cant open socket stream\n");
    }

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, UNIXSTR_PATH);
    lengthServer = strlen(serverAddr.sun_path) + sizeof(serverAddr.sun_family);

    if (connect(sockfd, (struct sockaddr *)&serverAddr, lengthServer) < 0)
    {
        printf("connect error\n");
    }
}

void threadMessage()
{

    pthread_t tMessages;
    //pthread_create(&tMessages, NULL, &recMSG, NULL);
    pthread_create(&tMessages, NULL, &pasta, NULL);
}

void startSemaphores() {

    sem_init(&semEmployee, 0, 1);
    sem_init(&semQueueManager, 0, 0);
    sem_init(&semRestock, 0, 0);
    sem_init(&semAvailableProduct, 0, 0);
    
}

void main()
{

    initSimulation();

    //startSimulatorSocket();
    //startSimulatorServerSocket();
    socketStartPleaseClient();

    threadMessage();
    startSemaphores();

    while (!isItOpen)
    {
        sleep(1); // a espera que a simulação inicie pelo monitor
    }

    //pthread_mutex_lock(&monitorFlag);
    //pthread_mutex_unlock(&monitorFlag);


    // inicialização de variáveis devido ao começo da simulação

    openingTime = time(0);
    closingTime = openingTime + timeCounter;

    threadsShop();

    pthread_t tClient;

    while(time(0) < closingTime) {

        while(simPause) {
            //
        }

        pthread_create(&tClient, NULL, client, NULL);
        sleep((rand() % avgTimeArrivalClients + 1) + avgTimeArrivalClients * 0.5);

    }

    //closeShop();

}
