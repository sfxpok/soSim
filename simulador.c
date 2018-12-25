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
            else if (strcmp(param, "maxClientsPerEmployee") == 0)
                maxClientsPerEmployee = value;
            else if (strcmp(param, "stockWarehouse") == 0)
                stockWarehouse = value;
        }

        fclose(fileConfig);
        printf("Inicialização feita.\n");
    }
}

void initSimulation()
{
    readConfig();
    cleanLogFile();
    openLogFile();
}

void closeSocket()
{
    close(simSocket);
}

/*

Funcionamento do gestor de filas de clientes

*/

int numberOfEmployeesToWork;

void *clientManager(void *tid)
{

    char bufferMonitor[512];

    while(!simPause) {

        //printf("tou dentro do ciclo clientManager\n");

        sem_wait(&semQueueManager);
        pthread_mutex_lock(&someMutex);

        numberOfEmployeesToWork = (round(clientsInLine / maxClientsPerEmployee) + 1); // floating point exception without round()

        if(numberOfEmployeesToWork > actualEmployeesUsedNow) {

            actualEmployeesUsedNow = numberOfEmployeesToWork;
            //actualEmployeesUsedNow++;

            sem_post(&semEmployee);
            sem_post(&semEmployee); // como é que isto funciona?

            //printf("O funcionário %d foi posto no serviço às %s.\n", numberOfEmployeesToWork, getTimeStamp());
            snprintf(messageToLog, sizeof(messageToLog), "O funcionário %d foi posto no serviço.\n", numberOfEmployeesToWork);
            writeLogFiles(messageToLog);

            sprintf(bufferMonitor, "AddEmployee %d %s", numberOfEmployeesToWork, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }
        else if(numberOfEmployeesToWork < actualEmployeesUsedNow) {
            
            actualEmployeesUsedNow = numberOfEmployeesToWork;
            //actualEmployeesUsedNow--;

            //printf("O funcionário %d deixou o serviço às %s.\n", numberOfEmployeesToWork, getTimeStamp());
            snprintf(messageToLog, sizeof(messageToLog), "O funcionário %d deixou o serviço.\n", numberOfEmployeesToWork+1);
            writeLogFiles(messageToLog);

            sprintf(bufferMonitor, "RemoveEmployee %d %s", (numberOfEmployeesToWork+1), getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }
        else {
            sem_post(&semEmployee);
            //printf("PASSEI POR SEMPOST DO FUNCIONARIO DE ELSE.\n");
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

        //printf("tou dentro do ciclo employee\n");

        sem_wait(&semRestock);
        pthread_mutex_lock(&someMutex);

        if (unitsCoffeeA <= 3) {

            sleep(1);

            unitsCoffeeA = unitsCoffeeA + stockWarehouse;

            //printf("%d unidades do café %d foram repostas às %s\n", stockWarehouse, 1, getTimeStamp());
            snprintf(messageToLog, sizeof(messageToLog), "%d unidades do café %d foram repostas.\n", stockWarehouse, 1);
            writeLogFiles(messageToLog);

            sprintf(bufferMonitor, "RestockCoffee %d %d %s", stockWarehouse, 1, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }

        else if (unitsCoffeeB <= 3) {

            sleep(1);

            unitsCoffeeB = unitsCoffeeB + stockWarehouse;

            //printf("%d unidades do café %d foram repostas às %s\n", stockWarehouse, 2, getTimeStamp());
            snprintf(messageToLog, sizeof(messageToLog), "%d unidades do café %d foram repostas.\n", stockWarehouse, 2);
            writeLogFiles(messageToLog);

            sprintf(bufferMonitor, "RestockCoffee %d %d %s", stockWarehouse, 2, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

        }

        else if (unitsCoffeeC <= 3) {

            sleep(1);

            unitsCoffeeC = unitsCoffeeC + stockWarehouse;

            //printf("%d unidades do café %d foram repostas às %s\n", stockWarehouse, 3, getTimeStamp());
            snprintf(messageToLog, sizeof(messageToLog), "%d unidades do café %d foram repostas.\n", stockWarehouse, 3);
            writeLogFiles(messageToLog);

            sprintf(bufferMonitor, "RestockCoffee %d %d %s", stockWarehouse, 3, getTimeStamp());
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
    
    //printf("### Cliente foi criado. (thread) ###\n");

    char bufferMonitor[1024];
    int probabilityThreshold;
    int id;

    time_t waitingTimeInLine;

    pthread_mutex_lock(&someMutex);

    int waitingTime = getRandomNumber(10);
    id = idClient++;
    clientsInLine++;

    time_t arrivalTime = time(NULL);

    //printf("ID CLIENTE: %d\n", id);

    //printf("O cliente %d acabou de chegar às %s.\n", id, getTimeStamp());
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", id);
    writeLogFiles(messageToLog);

	sprintf(bufferMonitor, "ClientArrived %d %s", id, getTimeStamp());
	send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

	pthread_mutex_unlock(&someMutex);

    sem_wait(&semEmployee);
    pthread_mutex_lock(&someMutex);

    clientsInLine--;

    //printf("antes de calcular prob de desistir\n");

    if ((time(NULL) - arrivalTime) > waitingTime) {

        probabilityThreshold = getRandomNumber(100);

        if (probabilityThreshold <= probWithdrawl) {
            
            //printf("O cliente %d desistiu às %s.\n", id, getTimeStamp());
            snprintf(messageToLog, sizeof(messageToLog), "O cliente %d desistiu.\n", id);
            writeLogFiles(messageToLog);
            
	        sprintf(bufferMonitor, "GiveUpClient %d %s", id, getTimeStamp());
	        send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

            clientsLeftStore++;

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

    //printf("O cliente %d pediu %d unidades do café %d às %s.\n", id, unitsBought, coffee, getTimeStamp());
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu %d unidades do café %d.\n", id, unitsBought, coffee);
    writeLogFiles(messageToLog);

	sprintf(bufferMonitor, "AskForCoffee %d %d %d %s %ld", id, unitsBought, coffee, getTimeStamp(), waitingTimeInLine);
	send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

    probabilityThreshold = getRandomNumber(100);

    if (probabilityThreshold <= probChangeOrder) {
        
        printf("CHANGED ORDER.\n");

        int aux = coffee;

        while (aux == coffee) {
            unitsBought = getRandomNumber(3);
            coffee = getRandomNumber(3);
        }
        //printf("O cliente %d alterou o seu pedido e pediu %d unidades do café %d às %s.\n", id, unitsBought, coffee, getTimeStamp());
        snprintf(messageToLog, sizeof(messageToLog), "O cliente %d alterou o seu pedido e pediu %d unidades do café %d.\n", id, unitsBought, coffee);
        writeLogFiles(messageToLog);
        
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

    //printf("O cliente %d recebeu %d unidades do café %d às %s.\n", id, unitsBought, coffee, getTimeStamp());
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d recebeu %d unidades do café %d.\n", id, unitsBought, coffee);
    writeLogFiles(messageToLog);
    
	sprintf(bufferMonitor, "ReceiveCoffee %d %d %d %s %d", id, unitsBought, coffee, getTimeStamp(), timeToServeClient);
	send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);
    
    clientsLeftStore++;

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

int closeShop()
{
    printf("A loja está fechada, mas falta atender os clientes em fila.\n");

    //printf("Clientes em fila: %d\n", clientsInLine);
    //printf("Clientes que já sairam da loja: %d\n", clientsLeftStore);

    while ((clientsInLine - clientsLeftStore) != 0)
    {
        // espera que os clientes todos saem da loja
    }

    printf("Já não existem clientes.\n");
    printf("Fim da simulação.\n");

    isItOpen = 0;
    //while(1);
    close(simSocket);

    return 0;
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

        //timeCounter++;

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

    openingTime = time(0);
    closingTime = openingTime + durationOpen;

    threadsShop();

    while(time(0) < closingTime) {

        while(simPause) {
            //sleep(1);
        }

        pthread_create(&tClient, NULL, client, NULL);
        sleep((rand() % avgTimeArrivalClients + 1) + avgTimeArrivalClients * 0.5);

    }

    closeShop();

}
