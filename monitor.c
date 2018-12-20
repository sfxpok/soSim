#include "libs.h"

void displayHeader()
{
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                            Loja                             │\n");
    printf("│                Sistemas Operativos 2018/2019                │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

void displayMenu()
{
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                      Lista de operacoes                     │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│(i)nit - inicializa a simulacao                              │\n");
    printf("│(m)enu - mostra o menu                                       │\n");
    printf("│(h)alt - pausa a simulacao                                   │\n");
    printf("│(s)tat - mostra as estatísticas da simulação                 │\n");
    printf("│(q)uit - sai da simulacao                                    │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

void displayStats()
{

    // põe qualquer coisa aqui para escrever no ficheiro de log dude

    // cuidado que esta função está incompleta

    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                         Estatisticas                        │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Geral ###                                               │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Duração da simulação: %d                                     │\n", timeCounter);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Clientes ###                                            │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Clientes criados na simulação: %d                            │\n", createdClients);
    printf("│Clientes à espera na fila: %d                                │\n", clientsInLine);
    printf("│Tempo médio de espera em fila: %d                            │\n", avgTimeWaitingClientsInLine);
    printf("│Clientes que mudaram o seu pedido: %d                        │\n", totalChangedOrder);
    printf("│Clientes que desistiram: %d                                  │\n", totalWithdrawls);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Empregados ###                                          │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Empregados ao serviço no máximo: %d                          │\n", maxEmployeesUsed);
    printf("│Empregados ao serviço: %d                                    │\n", actualEmployeesUsedNow);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Produtos ###                                            │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Vendas do produto 1: %d                                      │\n", unitsSoldCoffeeA);
    printf("│Vendas do produto 2: %d                                      │\n", unitsSoldCoffeeB);
    printf("│Vendas do produto 3: %d                                      │\n", unitsSoldCoffeeC);
    printf("│Tempo médio de serviço do produto 1: %d                      │\n", avgTimeToServeCoffeeA);
    printf("│Tempo médio de serviço do produto 2: %d                      │\n", avgTimeToServeCoffeeB);
    printf("│Tempo médio de serviço do produto 3: %d                      │\n", avgTimeToServeCoffeeC);
    printf("├─────────────────────────────────────────────────────────────┤\n");
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

int sendMessageSocket() {

    if (send(newsockfd, operation, sizeof(operation), 0) == -1)
    {

        printf("Falha de envio de mensagem no socket.\n");
        return -1;
    }

    return 0;
}

void askForInputString()
{
    do
    {
        printf("Escreva um comando: \n");
        fgets(operation, sizeof(operation), stdin);

        if (!strcmp(operation, "menu\n")) {
            displayMenu();
        }

        if (!strcmp(operation, "stats\n")){
            displayStats();
        }

        if (!strcmp(operation, "init\n")) {
            sendMessageSocket();
            //tempo_inicio_simulacao = time(NULL);
        }

        if (!strcmp(operation, "halt\n")) {
            sendMessageSocket();
        }

    } while (strcmp(operation, "quit\n"));
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

int openServerSocket()
{

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("Não deu para criar o socket dude.\n");
        return -1;
    }

    printf("Socket criado dude.\n");

    bzero((char *)&serverAddr, sizeof(serverAddr));
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, UNIXSTR_PATH);
    lengthServer = strlen(serverAddr.sun_path) + sizeof(serverAddr.sun_family);

    unlink(UNIXSTR_PATH);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, lengthServer) < 0)
    {
        printf("Bind não feito.\n");
        return -1;
    }

    printf("Bind feito.\n");

    listen(sockfd, 1);
    printf("Listen feito.\n");
    printf("À espera do simulador...\n");

    int lengthClient = sizeof(clientAddr);

    if ((newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &lengthClient)) < 0)
    {
        printf("Conexão falhada.");
        return -1;
    }

    printf("Conexão feita.\n");

    return 0;
}

void openForAppend() {
    logFile = fopen("log.txt", "a+");
}

void *getMonitorMessages(void *tid)
{

    int n;
    int sockfd = *((int *)tid);
    int error = 0;
    char eventMessage[20];
    int someIntegerA = 0;
    int someIntegerB = 0;
    int someIntegerC = 0;
    int someIntegerD = 0;

    while (1)
    {

        error = 0;

        do
        {
            if ((n = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0)
            {

                if (n < 0)
                {
                    printf("recv error");
                }

                error = 1;
            }

            sscanf(buffer, "%s %s %d %d %d %d", eventMessage, getTimeStamp(), &someIntegerA, &someIntegerB, &someIntegerC, &someIntegerD);

            if (!strcmp(eventMessage, "AddClient")) {
                openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - Cliente número %d chegou.\n", getTimeStamp(), someIntegerA);

                createdClients++;
                clientsInLine++;

            }

            if (!strcmp(eventMessage, "GiveUpClient")) {
                openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - Cliente número %d desistiu.\n", getTimeStamp(), someIntegerA);

                clientsInLine--;         
                totalWithdrawls++;       

            }

            if (!strcmp(eventMessage, "ChangedOrder")) {
                openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O cliente %d alterou o seu pedido e pediu %d unidades do café %d.\n", getTimeStamp(), someIntegerA, someIntegerB, someIntegerC);

                totalChangedOrder++;

            }

            if (!strcmp(eventMessage, "AddEmployee")) {
                openForAppend();

				/* if(logFile != NULL)
				{					
					fprintf(logFile,"%s - O empregado %d foi adicionado.\n", getTimeStamp(), someIntegerA);
					fclose(logFile);
				} */
				printf("%s - O funcionário numero %d foi adicionado.\n", getTimeStamp(), someIntegerA);
				actualEmployeesUsedNow++;
				if(actualEmployeesUsedNow > maxEmployeesUsed)
				{
					maxEmployeesUsed = actualEmployeesUsedNow;
				}
            }

            if (!strcmp(eventMessage, "RemoveEmployee")) {
                openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O funcionário %d foi removido.\n", getTimeStamp(), someIntegerA);

                actualEmployeesUsedNow--;
            }

            if (!strcmp(eventMessage, "AskForCoffee")) {
                openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O cliente %d pediu pelo café.\n", getTimeStamp(), someIntegerA, someIntegerD);

                clientsInLine--;
                avgTimeWaitingClientsInLine += someIntegerD;

            }

            if (!strcmp(eventMessage, "GiveCoffee")) {
                openForAppend();

                /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O funcionário %d deu o café %d ao cliente %d.\n", getTimeStamp(), someIntegerA, someIntegerB, someIntegerC);

            }

            if (!strcmp(eventMessage, "ReceiveCoffee")) {
                openForAppend();

                /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O cliente %d recebeu o café %d de %d unidades.\n", getTimeStamp(), someIntegerA, someIntegerB, someIntegerC, someIntegerD);

                if (someIntegerC == 1) {
                    timeToServeCoffeeA += someIntegerD;
                    unitsSoldCoffeeA += someIntegerB;
                }
                else if (someIntegerC == 2) {
                    timeToServeCoffeeB += someIntegerD;
                    unitsSoldCoffeeB += someIntegerB;
                }
                else {
                    timeToServeCoffeeC += someIntegerD;
                    unitsSoldCoffeeC += someIntegerB;
                }

            }

            if (!strcmp(eventMessage, "RestockCoffee")) {
                openForAppend();

                /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O funcionário %d repôs o café %d.\n", getTimeStamp(), someIntegerA, someIntegerB);

                // tira os cafés do armazém?

            }

        } while (!error);
    }
}

void closeServerSocket()
{
    close(newsockfd);
    close(sockfd);
}

void startMessageThread()
{

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &getMonitorMessages, &newsockfd);
}

void main()
{

    openServerSocket();
    startMessageThread();

    displayHeader();
    displayMenu();

    //askForInput();
    askForInputString();
    //pastaAskForInput();

    //closeShop();
}