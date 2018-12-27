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

void closeServerSocket()
{
    close(newsockfd);
    close(sockfd);
}

void pastaCharAskForInput()
{

    do
    {
        printf("Escreve um comando: \n");
        //fgets(op, sizeof(op), stdin);
        scanf("\n%c", &op);

        switch (op) {

        case 'i':
            // sendMessageSocket();

            if (send(newsockfd, op, sizeof(op), 0) == -1)
            {

                printf("Falha de envio de mensagem no socket.\n");
                return -1;
            }

            isItOpen = 1;
            if (simPause)
            {
                simPause = 0;
            }
            break;

        case 'h':
            sendMessageSocket();
            if (!simPause)
            {
                simPause = 1;
            }
            break;

        case 'q':
            sendMessageSocket();
            isItOpen = 0;
            closeShop();
            break;

        case 'm':
            displayMenu();
            break;

        case 's':
            displayStats();
            break;
        }
    } while (op != 'q');
}

void closeShop()
{
    printf("O programa terminou.\n");

    displayStats();

    closeServerSocket();
}

void outputMenu()
{
    //
}

void pauseShop()
{
    //
}

void askForInput()
{

    printf("entrei no askforinput\n");

    int halt = 0;

    do
    {

        printf("Escreva um comando:\n");
        scanf("%c", &op);

        switch (op)
        {

        case 'i':
            //initThreads();
            break;

        case 'h':
            break;

        case 'q': // to be fixed
            halt = 1;
            break;

        case 'm':
            displayMenu();
            break;

        case 's':
            closeServerSocket();
            halt = 1;
            break;
        }

        // e preciso mudar a condicao do while para o op, eventualmente
        // op = getchar();

    } while (halt != 1);

    printf("sai do askforinput\n");

    //closeShop();
}

void pastaAskForInput()
{
    do
    {
        printf("Escreve um comando: \n");
        fgets(buffer, sizeof(buffer), stdin);
        if (!strcmp(buffer, "menu\n"))
            displayMenu();
        if (!strcmp(buffer, "estatistica\n"))
        {
            //mostra_estatistica();
            printf("stat\n");
        }

        if (!strcmp(buffer, "start\n"))
        {
            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {

                printf("send\n");
                exit(1);
            }
            //tempo_inicio_simulacao = time(NULL);
            printf("start?\n");

            if (simPause)
            {
                simPause = 0;
            }
        }
        if (!strcmp(buffer, "pause\n"))
        {
            printf("Introduza o comando log para ver o registo da simulacao\n");
            printf("Introduza o comando estatistica para ver as mesmas\n");

            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {
                exit(1);
            }

            simPause = 1;
        }

        if (!strcmp(buffer, "abre\n"))
        {
            printf("hey do monitor - abre\n");

            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {
                exit(1);
            }
        }

        if (!strcmp(buffer, "dummy\n"))
        {
            printf("dummy command\n");

            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {
                exit(1);
            }
        }
    } while (strcmp(buffer, "quit\n"));
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