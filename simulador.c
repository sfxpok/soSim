#include "libs.h"

/*

    function: checkBadConfigValues

    value: valor de um parâmetro de configuração

    Não permite que hajam parâmetros de configuração que causem o mau funcionamento do programa.

*/

int checkBadConfigValues(int value) {

    if (value < 0 || value > 100) {
        printf("Existem parâmetros de configuração com valores inadequados. Altere o ficheiro de configuração.\n");
        exit(1);
    } else {
        return 0;
    }

}

/*

    function: readConfig

    Lê parâmetros de configuração do ficheiro "config.conf". Caso o "config.conf" não exista, usamos
    valores pré-definidos dentro do código.

*/

void readConfig()
{

    FILE *fileConfig = fopen("config.conf", "r");

    char param[128];
    int value;

    if (fileConfig == NULL)
    {
        printf("Erro ao abrir o ficheiro. O programa irá usar valores pré-definidos.");

        // Valores pré-definidos
        //maxClients = 3;
        //spawnedClients = 6;
        //avgTimeArrivalClients = 3;
        timeToServeCoffeeA = 2;
        timeToServeCoffeeB = 3;
        timeToServeCoffeeC = 4;
        probWithdrawl = 2;
        //openingTime = 10;
        //closingTime = 13;
        //timeCounter = 0;
        isItOpen = 0;
        durationOpen = 30;
        maxClientsPerEmployee = 3;
        probChangeOrder = 10;
        stockWarehouse = 5;

    }

    else
    {
        printf("A ler o ficheiro de configuração...\n");

        while (fscanf(fileConfig, "%s %d\n", param, &value) != EOF)
        {

            checkBadConfigValues(value);

            if (strcmp(param, "stockWarehouse") == 0)
                stockWarehouse = value;
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
            else if (strcmp(param, "probChangeOrder") == 0)
                probChangeOrder = value;
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

        }

        fclose(fileConfig);
        printf("Inicialização feita.\n");
    }
}

/*

    function: initSimulation

    Apenas acede funções que lêem o ficheiro de configuração, apaga o conteúdo do ficheiro de registo
    e abre a stream para podermos escrever no ficheiro de registo.

*/

void initSimulation()
{
    readConfig();
    cleanLogFile();
    openLogFile();
}

/*

    function: *clientManager

    *tid: ID do thread que acede esta função

    Função que desempenha o papel de gestor de filas.

*/

int numberOfEmployeesToWork;

void *clientManager(void *tid)
{

    char bufferMonitor[512]; // buffer para transmitir mensagem do simulador para o monitor

    while(isItOpen) { // o gestor de filas trabalha enquanto que a loja tiver aberta

        //printf("tou dentro do ciclo clientManager\n");

        sem_wait(&semQueueManager); // vai decidir quantos funcionários vão estar no serviço
        pthread_mutex_lock(&someMutex);

        // fórmula para calcular quantos funcionários deviam tar em serviço
        numberOfEmployeesToWork = (round(clientsInLine / maxClientsPerEmployee) + 1);

        if(numberOfEmployeesToWork > actualEmployeesUsedNow) {

            actualEmployeesUsedNow = numberOfEmployeesToWork;
            //actualEmployeesUsedNow++;

            sem_post(&semEmployee);
            sem_post(&semEmployee); // como é que isto funciona? pensei que só fosse preciso assinalar uma vez...

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
            sem_post(&semEmployee); // ?
        }

        pthread_mutex_unlock(&someMutex);

    }
}

/*

    function: *employee

    *tid: ID do thread que acede esta função

    Função que desempenha o papel de funcionário.

*/

void *employee(void *tid)
{
    char bufferMonitor[512]; // buffer para transmitir mensagem do simulador para o monitor

    while (isItOpen) { // o gestor de filas trabalha enquanto que a loja tiver aberta

        //printf("tou dentro do ciclo employee\n");

        sem_wait(&semRestock); // vai fazer restock de algum café
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
        sem_post(&semAvailableProduct); // é para avisar que o funcionário pode voltar à caixa e servir o café ao cliente

    }

}

/*

    function: *client

    *tid: ID do thread que acede esta função

    Função que desempenha o papel de cliente.

*/

void *client(void *tid)
{
    
    //printf("### Cliente foi criado. (thread) ###\n");

    char bufferMonitor[1024]; // buffer para transmitir mensagem do simulador para o monitor
    int probabilityThreshold; // apenas serve para gerar números de 0 a 100, ver mais abaixo
    int id; // ID do cliente
    //int probWithdrawl;
    int unitsBought; // unidades a comprar
    int coffee; // qual é o café

    time_t waitingTimeInLine; // tempo de espera na fila

    pthread_mutex_lock(&someMutex);

    int waitingTime = getRandomNumber(5); // tempo de espera que é usado para decidir se vai ficar em risco de querer desistir
    id = idClient++;
    clientsInLine++;

    time_t arrivalTime = time(NULL); // tempo em que chegou à loja

    //printf("ID CLIENTE: %d\n", id);

    //printf("O cliente %d acabou de chegar às %s.\n", id, getTimeStamp());
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", id);
    //printf("### Cliente foi criado. (thread) ###\n");
    writeLogFiles(messageToLog);

    sprintf(bufferMonitor, "ClientArrived %d %s", id, getTimeStamp());
    send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

    pthread_mutex_unlock(&someMutex);

    sem_wait(&semEmployee); // há um funcionário que vai atender um cliente, logo o semáforo decrementa
    pthread_mutex_lock(&someMutex);

    clientsInLine--;

    if ((time(NULL) - arrivalTime) > waitingTime) { // o cliente esperou muito?

        probabilityThreshold = getRandomNumber(100);

        if (probabilityThreshold <= probWithdrawl) { // a probabilidade de desistir da fila é maior que o número aleatório criado?
            
            //printf("O cliente %d desistiu às %s.\n", id, getTimeStamp());
            snprintf(messageToLog, sizeof(messageToLog), "O cliente %d desistiu.\n", id);
            writeLogFiles(messageToLog);
            
            sprintf(bufferMonitor, "GiveUpClient %d %s", id, getTimeStamp());
            send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

            clientsLeftStore++;

            sem_post(&semQueueManager);
            pthread_mutex_unlock(&someMutex);

            return NULL; // cliente desistiu...

        }

    }

    pthread_mutex_unlock(&someMutex);
    pthread_mutex_lock(&someMutex);

    unitsBought = getRandomNumber(3); // quantas unidades é que o cliente vai comprar?
    coffee = getRandomNumber(3); // qual é o café que o cliente vai comprar?

    waitingTimeInLine = time(NULL) - arrivalTime;

    //printf("O cliente %d pediu %d unidades do café %d às %s.\n", id, unitsBought, coffee, getTimeStamp());
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d pediu %d unidades do café %d.\n", id, unitsBought, coffee);
    writeLogFiles(messageToLog);

    sprintf(bufferMonitor, "AskForCoffee %d %d %d %s %ld", id, unitsBought, coffee, getTimeStamp(), waitingTimeInLine);
    send(sockfd, bufferMonitor, sizeof(bufferMonitor), 0);

    probabilityThreshold = getRandomNumber(100);

    if (probabilityThreshold <= probChangeOrder) {  // a probabilidade de trocar de pedido é maior que o número aleatório criado?
        
        //printf("CHANGED ORDER.\n");

        int aux = coffee;

        while (aux == coffee) { // tenta obter um café diferente
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
                sem_post(&semRestock); // vai fazer restock do café
                pthread_mutex_unlock(&someMutex);
                sem_wait(&semAvailableProduct); // já tamos café com stock?
                pthread_mutex_lock(&someMutex);
            }
            pthread_mutex_unlock(&someMutex);
            sleep(getRandomNumber(timeToServeCoffeeA) + timeToServeCoffeeA * 0.2); // tá a servir o café...
            pthread_mutex_lock(&someMutex);

            unitsCoffeeA = unitsCoffeeA - unitsBought;

            break;
        case 2:
            while (unitsCoffeeB <= 3) {
                sem_post(&semRestock); // vai fazer restock do café
                pthread_mutex_unlock(&someMutex);
                sem_wait(&semAvailableProduct); // já tamos café com stock?
                pthread_mutex_lock(&someMutex);
            }
            pthread_mutex_unlock(&someMutex);
            sleep(getRandomNumber(timeToServeCoffeeB) + timeToServeCoffeeB * 0.2); // tá a servir o café...
            pthread_mutex_lock(&someMutex);

            unitsCoffeeB = unitsCoffeeB - unitsBought;

            break;
        case 3:
            while (unitsCoffeeC <= 3) {
                sem_post(&semRestock); // vai fazer restock do café
                pthread_mutex_unlock(&someMutex);
                sem_wait(&semAvailableProduct); // já tamos café com stock?
                pthread_mutex_lock(&someMutex);
            }
            pthread_mutex_unlock(&someMutex);
            sleep(getRandomNumber(timeToServeCoffeeC) + timeToServeCoffeeC * 0.2); // tá a servir o café...
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

    //pthread_exit(tid);
    return 0;

}

/*

    function: threadsShop

    Inicialização da thread do gestor de filas e de empregado.

*/

void threadsShop()
{

    pthread_t tClientManager;
    pthread_create(&tClientManager, NULL, &clientManager, NULL);

    //pthread_t *tClient;

    pthread_t tEmployee;
    pthread_create(&tEmployee, NULL, employee, NULL);
}

/*

    function: closeShop

    Fecha a loja e dá por concluído a simulação da mesma.

*/

int closeShop()
{
    printf("A loja está fechada, mas falta atender os clientes em fila.\n");

    //printf("Clientes em fila: %d\n", clientsInLine);
    //printf("Clientes que já sairam da loja: %d\n", clientsLeftStore);

    while ((clientsInLine - clientsLeftStore) != 0) // enquanto que ainda houver clientes para atender dentro da loja...
    {
        // espera ativa
    }

    printf("Já não existem clientes.\n");
    printf("Fim da simulação.\n");

    writeStatsToLog(); // escreve estatísticas para o ficheiro de registo

    isItOpen = 0;
    //canWriteStats = 1;
    //while(1);
    close(simSocket);

    exit(0);
}

/*

    function: *simulatorMessages

    Trata do envio das mensagens entre o simulador para o monitor.

*/

void *simulatorMessages()
{
    int n;
    char buffer[256];
    //char operation[64];
    
    while (1) // está sempre a tentar enviar qualquer coisa do simulador para o monitor
    {

        //timeCounter++;

        if ((n = recv(sockfd, operation, sizeof(operation), 0)) > 0) // tá a enviar direito?
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

    function: startSimulatorClientSocket

    Cria um canal de comunicação entre o simulador (cliente) e o monitor (servidor).

*/

void startSimulatorClientSocket()
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

/*

    function: threadMessage

    Inicialização da thread que trata das mensagens enviadas do simulador para o monitor.

*/

void threadMessage()
{

    pthread_t tMessages;
    //pthread_create(&tMessages, NULL, &recMSG, NULL);
    pthread_create(&tMessages, NULL, &simulatorMessages, NULL);
}

/*

    function: startSemaphores

    Inicialização dos semáforos.

*/

void startSemaphores() {

    sem_init(&semEmployee, 0, 1);
    sem_init(&semQueueManager, 0, 0);
    sem_init(&semRestock, 0, 0);
    sem_init(&semAvailableProduct, 0, 0);

    printf("Semáforos inicializados.\n");
    
}

/* int h = 0;
int g = 0;

void insertClientArray() {
    pthread_create(&tClient[g], NULL, client, NULL);
    g++;
} */

/*

    function: main

    Programa principal

*/

void main()
{

    initSimulation();

    startSimulatorClientSocket();

    threadMessage();
    startSemaphores();

    while (!isItOpen) // a espera que a simulação inicie para o monitor avanaçar...
    {
        // espera ativa
    }

    openingTime = time(0); // tempo de abertura da loja (NOTA: atribuições com o time() são em UNIXTIME)

    // o tempo de encerramento da loja é a soma do tempo da abertura da loja com a duração que a loja vai
    // estar aberta. O último é definido previamente no ficheiro de configuração.
    closingTime = openingTime + durationOpen; 

    threadsShop();

    while(time(0) < closingTime) { // já podemos fechar a loja?

        while(simPause) { // a simulação pode ficar em pausa
            // espera ativa
        }

        pthread_create(&tClient, NULL, client, NULL);
        //insertClientArray();

        sleep((rand() % avgTimeArrivalClients + 1) + avgTimeArrivalClients * 0.5); // método de criar clientes de vez em quando

    }

    // faz um ciclo for para fazer "join" nas threads todas. as threads ficam guardadas num array
    //pthread_join(&tClient, )

/*     for(h = 0; h < g; h++) {
        pthread_join(tClient[h], NULL);
    } */

    closeShop();

}