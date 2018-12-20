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
        maxClients = 3;
        spawnedClients = 6;
        avgTimeArrivalClients = 3;
        timeToServeCoffeeA = 2;
        timeToServeCoffeeB = 3;
        timeToServeCoffeeC = 4;
        probWithdrawl = 2;
        openingTime = 10;
        closingTime = 13;
        timeCounter = 0;
        isItOpen = 0;
        durationOpen = 0;
    }

    else
    {
        printf("A ler o ficheiro de configuração...\n");

        while (fscanf(fileConfig, "%s %d\n", param, &value) != EOF)
        {

            if (strcmp(param, "maxClients") == 0)
                maxClients = value;
            else if (strcmp(param, "spawnedClients") == 0)
                spawnedClients = value;
            else if (strcmp(param, "avgTimeArrivalClients") == 0)
                avgTimeArrivalClients = value;
            else if (strcmp(param, "timeToServeCoffeeA") == 0)
                timeToServeCoffeeA = value;
            else if (strcmp(param, "timeToServeCoffeeB") == 0)
                timeToServeCoffeeB = value;
            else if (strcmp(param, "timeToServeCoffeeC") == 0)
                timeToServeCoffeeC = value;
            else if (strcmp(param, "probWithdrawl") == 0)
                probWithdrawl = value;
            else if (strcmp(param, "openingTime") == 0)
                openingTime = value;
            else if (strcmp(param, "closingTime") == 0)
                closingTime = value;
            else if (strcmp(param, "timeCounter") == 0)
                timeCounter = value;
            else if (strcmp(param, "isItOpen") == 0)
                isItOpen = value;
            else if (strcmp(param, "durationOpen") == 0)
                durationOpen = value;
            else if (strcmp(param, "unitsCoffeeA") == 0)
                unitsCoffeeA = value;
            else if (strcmp(param, "unitsCoffeeB") == 0)
                unitsCoffeeB = value;
            else if (strcmp(param, "unitsCoffeeC") == 0)
                unitsCoffeeC = value;
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

void askForCoffee(int idClient, char charCoffee)
{

    // printf("O cliente %d pediu pela Coffee %c.\n", idClient, charCoffee);

    switch (charCoffee)
    {
    case 'A':
        // da-lhe Coffee A

        if (simulador.unitsCoffeeA < 2)
        {
            // cliente espera
        }

        snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela Coffee %c.\n", idClient, charCoffee);
        writeOutputToMonitor(messageToLog);
        writeLogFiles(messageToLog);

        break;
    case 'B':
        // da-lhe Coffee B

        if (simulador.unitsCoffeeB < 2)
        {
            // cliente espera
        }

        snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela Coffee %c.\n", idClient, charCoffee);
        writeOutputToMonitor(messageToLog);
        writeLogFiles(messageToLog);

        break;
    case 'C':
        // da-lhe Coffee C

        if (simulador.unitsCoffeeC < 2)
        {
            // cliente espera
        }

        snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu pela Coffee %c.\n", idClient, charCoffee);
        writeOutputToMonitor(messageToLog);
        writeLogFiles(messageToLog);

        break;
    }
}

void giveCoffeeToClient(int idClient, char charCoffee, int idEmployee)
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

void restockCoffee(int idEmployee, char charCoffee)
{

    switch (charCoffee)
    {
    case 'a':
        // repoe Coffee A
        printf("O empregado %d repôs a Coffee %c.\n", idEmployee, charCoffee);
        break;
    case 'b':
        // repoe Coffee B
        printf("O empregado %d repôs a Coffee %c.\n", idEmployee, charCoffee);
        break;
    case 'c':
        // repoe Coffee C
        printf("O empregado %d repôs a Coffee %c.\n", idEmployee, charCoffee);
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

void checkIfProductIsOutOfStock(char charCoffee)
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

    //sprintf(messageToLog, "%d", idEvent);

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

        printf("tou dentro do ciclo clientManager\n");

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

    while (!simPause) {

        printf("tou dentro do ciclo employee\n");

        sem_wait(&semRestock);
        pthread_mutex_lock(&someMutex);

        if (unitsCoffeeA <= 3) {

            sleep(1);

            unitsCoffeeA = unitsCoffeeA + stockWarehouse;

            printf("%d unidades do produto %c foram repostas às %s\n", stockWarehouse, 'A', getTimeStamp());
            sprintf(bufferMonitor, "RestockProduct %c %d %s", 'A', stockWarehouse, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }

        else if (unitsCoffeeB <= 3) {

            sleep(1);

            unitsCoffeeB = unitsCoffeeB + stockWarehouse;

            printf("%d unidades do produto %c foram repostas às %s\n", stockWarehouse, 'B', getTimeStamp());
            sprintf(bufferMonitor, "RestockProduct %c %d %s", 'A', stockWarehouse, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }

        else if (unitsCoffeeC <= 3) {

            sleep(1);

            unitsCoffeeC = unitsCoffeeC + stockWarehouse;

            printf("%d unidades do produto %c foram repostas às %s\n", stockWarehouse, 'C', getTimeStamp());
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
    
    printf("### Cliente foi criado. (thread) ###\n");

    char bufferMonitor[1024];
    int probabilityThreshold;
    int id;

    time_t waitingTimeInLine;

    pthread_mutex_lock(&someMutex);

    int waitingTime = getRandomNumber(10);
    id = idClient++;
    clientsInLine++;

    time_t arrivalTime = time(NULL);

    printf("O cliente %d acabou de chegar às %s.\n", id, getTimeStamp());
	sprintf(bufferMonitor, "ClientArrived %d %s", id, getTimeStamp());
	send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

	pthread_mutex_unlock(&someMutex);

    sem_wait(&semEmployee);
    pthread_mutex_lock(&someMutex);

    clientsInLine--;

    printf("antes de calcular prob de desistir\n");

    if ((time(NULL) - arrivalTime) > waitingTime) {

        probabilityThreshold = getRandomNumber(100);

        if (probabilityThreshold <= probWithdrawl) {
            
            printf("O cliente %d desistiu às %s.\n", id, getTimeStamp());
	        sprintf(bufferMonitor, "GiveUpClient %d %s", id, getTimeStamp());
	        send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

            sem_post(&semQueueManager);
			pthread_mutex_unlock(&someMutex);

            return NULL;

        }

    }

        pthread_mutex_unlock(&someMutex);
	    pthread_mutex_lock(&someMutex);

        unitsBought = getRandomNumber(3);
        coffee = getRandomNumber(3);

        waitingTimeInLine = time(NULL) - arrivalTime;

        printf("O cliente %d pediu %d unidades do café %d às %s.\n", id, unitsBought, coffee, getTimeStamp());
	    sprintf(bufferMonitor, "AskForCoffee %d %d %d %s %d", id, unitsBought, coffee, getTimeStamp(), waitingTimeInLine);
	    send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        probabilityThreshold = getRandomNumber(100);

        if (probabilityThreshold <= probChangeOrder) {
            
            int aux = coffee;

            while (aux == coffee) {
                unitsBought = getRandomNumber(2);
                coffee = getRandomNumber(3);
            }

            printf("O cliente %d alterou o seu pedido e pediu %d unidades do café %d às %s.\n", id, unitsBought, coffee, getTimeStamp());
	        sprintf(bufferMonitor, "ChangedOrder %d %d %d %s", id, unitsBought, coffee, getTimeStamp());
	        send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);
            
        }

        switch(coffee) {

            case 1:
                while (unitsCoffeeA <= 3) {
                    sem_post(&semRestock);
                    pthread_mutex_unlock(&someMutex);
                    sem_wait(&semAvailableProduct);
                    pthread_mutex_lock(&someMutex);
                }   

                pthread_mutex_unlock(&someMutex);
                sleep(getRandomNumber(timeToServeCoffeeA) + timeToServeCoffeeA * 0.2);
                pthread_mutex_lock(&someMutex);

                unitsCoffeeA = unitsCoffeeA - unitsBought;

                break;

            case 2:
                while (unitsCoffeeB <= 3) {
                    sem_post(&semRestock);
                    pthread_mutex_unlock(&someMutex);
                    sem_wait(&semAvailableProduct);
                    pthread_mutex_lock(&someMutex);
                }

                pthread_mutex_unlock(&someMutex);
                sleep(getRandomNumber(timeToServeCoffeeB) + timeToServeCoffeeB * 0.2);
                pthread_mutex_lock(&someMutex);

                unitsCoffeeB = unitsCoffeeB - unitsBought;

                break;

            case 3:
                while (unitsCoffeeC <= 3) {
                    sem_post(&semRestock);
                    pthread_mutex_unlock(&someMutex);
                    sem_wait(&semAvailableProduct);
                    pthread_mutex_lock(&someMutex);
                }

                pthread_mutex_unlock(&someMutex);
                sleep(getRandomNumber(timeToServeCoffeeC) + timeToServeCoffeeC * 0.2);
                pthread_mutex_lock(&someMutex);

                unitsCoffeeC = unitsCoffeeC - unitsBought;

                break;                

        }

    timeToServeClient = time(NULL) - waitingTimeInLine;

    printf("O cliente %d recebeu %d unidades do café %d às %s.\n", id, unitsBought, coffee, getTimeStamp());
	sprintf(bufferMonitor, "ReceiveCoffee %d %d %d %s", id, unitsBought, coffee, getTimeStamp(), timeToServeClient);
	send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);
    
    sem_post(&semQueueManager);
    pthread_mutex_unlock(&someMutex);

    return 0;

}

void threadsShop()
{

    pthread_t tClientManager;
    pthread_create(&tClientManager, NULL, &clientManager, NULL);

    pthread_t tClient;

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

//int runStore;

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
                //runStore = 1;
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

    printf("Semáforos inicializados.\n");
    
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

    timeCounter = 100;
    openingTime = time(0);
    closingTime = openingTime + timeCounter;

    threadsShop();

    while(time(0) < closingTime) {

        while(simPause) {
            sleep(1);
        }

        pthread_create(&tClient, NULL, client, NULL);
        sleep((rand() % avgTimeArrivalClients + 1) + avgTimeArrivalClients * 0.5);

    }

    closeShop();

}
