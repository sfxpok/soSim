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
