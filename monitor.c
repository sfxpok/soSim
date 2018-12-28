#include "libs.h"

/*

    function: displayHeader

    Mostra no terminal o cabeçalho do menu

*/

void displayHeader()
{
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                         Loja de café                        │\n");
    printf("│                Sistemas Operativos 2018/2019                │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

/*

    function: displayMenu

    Mostra no terminal o menu

*/

void displayMenu()
{
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                      Lista de operacoes                     │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│init - inicializa a simulacao                                │\n");
    printf("│menu - mostra o menu                                         │\n");
    printf("│halt - pausa a simulacao                                     │\n");
    printf("│stat - mostra as estatísticas da simulação                   │\n");
    printf("│quit - sai da simulacao                                      │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

/*

    function: displayStats

    Mostra no terminal as estatísticas da simulação

*/

void displayStats()
{

    if((createdClients - clientsInLine) != 0) {
        avgTimeWaitingClientsInLine = waitingTimeInLine / (createdClients - clientsInLine); // cálculo do tempo média de espera na fila
    }

    if(unitsSoldCoffeeA != 0) {
        avgTimeToServeCoffeeA = timeToServeCoffeeA / unitsSoldCoffeeA; // cálculo do tempo médio para servir o café 1
    }

    if(unitsSoldCoffeeB != 0) {
        avgTimeToServeCoffeeB = timeToServeCoffeeB / unitsSoldCoffeeB; // cálculo do tempo médio para servir o café 2
    }

    if(unitsSoldCoffeeC != 0) {
        avgTimeToServeCoffeeC = timeToServeCoffeeC / unitsSoldCoffeeC; // cálculo do tempo médio para servir o café 3
    }

    currentTime = time(NULL);

    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                         Estatisticas                        │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Geral ###                                               │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Duração da simulação: %d                                     │\n", currentTime-timeStartOfSimulation);
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
    printf("│ ### Cafés ###                                               │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Vendas do café 1: %d                                         │\n", unitsSoldCoffeeA);
    printf("│Vendas do café 2: %d                                         │\n", unitsSoldCoffeeB);
    printf("│Vendas do café 3: %d                                         │\n", unitsSoldCoffeeC);
    printf("│Tempo médio de serviço do café 1: %d                         │\n", avgTimeToServeCoffeeA);
    printf("│Tempo médio de serviço do café 2: %d                         │\n", avgTimeToServeCoffeeB);
    printf("│Tempo médio de serviço do café 3: %d                         │\n", avgTimeToServeCoffeeC);
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

/* void writeStatsToLog() {

    if((createdClients - clientsInLine) != 0) {
        avgTimeWaitingClientsInLine = waitingTimeInLine / (createdClients - clientsInLine);
    }

    if(unitsSoldCoffeeA != 0) {
        avgTimeToServeCoffeeA = timeToServeCoffeeA / unitsSoldCoffeeA;
    }

    if(unitsSoldCoffeeB != 0) {
        avgTimeToServeCoffeeB = timeToServeCoffeeB / unitsSoldCoffeeB;
    }

    if(unitsSoldCoffeeC != 0) {
        avgTimeToServeCoffeeC = timeToServeCoffeeC / unitsSoldCoffeeC;
    }

    //currentTime = time(NULL);

    //if (logFile == NULL) {
        //open(logFile, "a+");
    //}

    fprintf(logFile, "┌─────────────────────────────────────────────────────────────┐\n");
    fprintf(logFile, "│                         Estatisticas                        │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Geral ###                                               │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Duração da simulação: %d                                     │\n", currentTime-timeStartOfSimulation);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Clientes ###                                            │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Clientes criados na simulação: %d                            │\n", createdClients);
    fprintf(logFile, "│Clientes à espera na fila: %d                                │\n", clientsInLine);
    fprintf(logFile, "│Tempo médio de espera em fila: %d                            │\n", avgTimeWaitingClientsInLine);
    fprintf(logFile, "│Clientes que mudaram o seu pedido: %d                        │\n", totalChangedOrder);
    fprintf(logFile, "│Clientes que desistiram: %d                                  │\n", totalWithdrawls);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Empregados ###                                          │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Empregados ao serviço no máximo: %d                          │\n", maxEmployeesUsed);
    fprintf(logFile, "│Empregados ao serviço: %d                                    │\n", actualEmployeesUsedNow);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│ ### Cafés ###                                               │\n");
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");
    fprintf(logFile, "│Vendas do café 1: %d                                         │\n", unitsSoldCoffeeA);
    fprintf(logFile, "│Vendas do café 2: %d                                         │\n", unitsSoldCoffeeB);
    fprintf(logFile, "│Vendas do café 3: %d                                         │\n", unitsSoldCoffeeC);
    fprintf(logFile, "│Tempo médio de serviço do café 1: %d                         │\n", avgTimeToServeCoffeeA);
    fprintf(logFile, "│Tempo médio de serviço do café 2: %d                         │\n", avgTimeToServeCoffeeB);
    fprintf(logFile, "│Tempo médio de serviço do café 3: %d                         │\n", avgTimeToServeCoffeeC);
    fprintf(logFile, "├─────────────────────────────────────────────────────────────┤\n");

    fclose(logFile);

} */

/*

    function: sendMessageSocket

    Envia uma mensagem (em particular, uma operação do menu) para o simulador.

*/

int sendMessageSocket() {

    if (send(newsockfd, operation, sizeof(operation), 0) == -1)
    {

        printf("Falha de envio de mensagem no socket.\n");
        return -1;
    }

    return 0;
}

/*

    function: askForInputString

    Processa que operação é que o utilizador quer realizar no programa


*/

void askForInputString()
{
    do
    {
        printf("Escreva um comando: \n");
        fgets(operation, sizeof(operation), stdin);

        if (!strcmp(operation, "menu\n")) {
            displayMenu();
        }

        if (!strcmp(operation, "stat\n")){
            displayStats();
        }

        if (!strcmp(operation, "init\n")) {
            sendMessageSocket();
            timeStartOfSimulation = time(NULL);
        }

        if (!strcmp(operation, "halt\n")) {
            sendMessageSocket();
        }

        // printlog não funciona!

        if (!strcmp(operation, "printlog\n")) {
            if (canWriteStats) {
                writeStatsToLog();
            } else {
                printf("A simulação ainda está a decorrer.\n");
            }
        }

    } while (strcmp(operation, "quit\n"));
}

/*

    function: openServerSocket

    Cria um canal de comunicação entre o monitor (servidor) e o simulador (cliente).

*/

int openServerSocket()
{

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("Não consigo criar o socket.\n");
        return -1;
    }

    printf("Socket criado.\n");

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

/* void openForAppend() {
    logFile = fopen("log.txt", "a+");
} */

/*

    function: *getMonitorMessages

    Recebe as mensagens que vêem do simulador.

*/

void *getMonitorMessages(void *tid)
{

    int n;
    int sockfd = *((int *)tid);
    int error = 0;
    char eventMessage[20];
    char buffer[1024];
    int someIntegerA = 0;
    int someIntegerB = 0;
    int someIntegerC = 0;
    int someIntegerD = 0;
    int loop;

    //while (1)
    //{

        error = 0;

        do
        {
            if ((n = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0)
            {

                if (n < 0)
                    printf("recv error");
                //else
                    //printf("Servidor foi desligado.\n");
                //exit(1);

                error = 1;
            }
    
            sscanf(buffer, "%s %d %d %d %d", eventMessage, &someIntegerA, &someIntegerB, &someIntegerC, &someIntegerD);

            //printf("I_A: %d\n", someIntegerA);

            if (!strcmp(eventMessage, "ClientArrived")) {
                //openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - Cliente número %d chegou.\n", getTimeStamp(), someIntegerA);

                createdClients++;
                clientsInLine++;

            }

            if (!strcmp(eventMessage, "GiveUpClient")) {
                //openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - Cliente número %d desistiu.\n", getTimeStamp(), someIntegerA);

                clientsInLine--;         
                totalWithdrawls++;       

            }

            if (!strcmp(eventMessage, "ChangedOrder")) {
                //openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O cliente %d alterou o seu pedido e pediu %d unidades do café %d.\n", getTimeStamp(), someIntegerA, someIntegerB, someIntegerC);

                totalChangedOrder++;

            }

            if (!strcmp(eventMessage, "AddEmployee")) {
                //openForAppend();

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
                //openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O funcionário %d foi removido.\n", getTimeStamp(), someIntegerA);

                actualEmployeesUsedNow--;
            }

            if (!strcmp(eventMessage, "AskForCoffee")) {
                //openForAppend();

             /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O cliente %d pediu %d unidades do café %d.\n", getTimeStamp(), someIntegerA, someIntegerB, someIntegerC);

                clientsInLine--;
                waitingTimeInLine += someIntegerD; // tá a somar o tempo que o cliente esperou

            }

            if (!strcmp(eventMessage, "GiveCoffee")) {
                //openForAppend();

                /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O funcionário %d deu o café %d ao cliente %d.\n", getTimeStamp(), someIntegerA, someIntegerB, someIntegerC);

            }

            if (!strcmp(eventMessage, "ReceiveCoffee")) {
                //openForAppend();

                /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - O cliente %d recebeu o café %d de %d unidades.\n", getTimeStamp(), someIntegerA, someIntegerC, someIntegerB);

                if (someIntegerC == 1) {
                    timeToServeCoffeeA += someIntegerD; // tá a somar o tempo que levou para servir o cliente
                    unitsSoldCoffeeA += someIntegerB; // tá a somar quantas unidades do café A vendeu
                }
                else if (someIntegerC == 2) {
                    timeToServeCoffeeB += someIntegerD; // tá a somar o tempo que levou para servir o cliente
                    unitsSoldCoffeeB += someIntegerB; // tá a somar quantas unidades do café B vendeu
                }
                else {
                    timeToServeCoffeeC += someIntegerD; // tá a somar o tempo que levou para servir o cliente
                    unitsSoldCoffeeC += someIntegerB; // tá a somar quantas unidades do café C vendeu
                }

            }

            if (!strcmp(eventMessage, "RestockCoffee")) {
                //openForAppend();

                /* if (logFile != NULL) {
                    fprintf(logFile, "%s - Cliente número %d chegou.\n", getTimeStamp(), someInteger);
                } */

                printf("%s - %d unidades do café %d foram repostas.\n", getTimeStamp(), someIntegerA, someIntegerB);

            }

        } while (!error);
    //}

    close(sockfd);

}

/*

    function: startMessageThread

    Inicializa a thread que trata das mensagens que vêem do simulador.

*/

void startMessageThread()
{

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &getMonitorMessages, &newsockfd);
}

/*

    function: shutdownMonitor

    Desliga o monitor. Este desliga-se após o simulador desligar.

*/

void shutdownMonitor() {

    printf("Fim da simulação.\n");

    writeStatsToLog();
    displayStats();

    close(newsockfd);
    close(sockfd);

    exit(0);
}

/*

    function: main

    Programa principal

*/

void main()
{

    openServerSocket();
    startMessageThread();

    displayHeader();
    displayMenu();

    //askForInput();
    askForInputString();
    //pastaAskForInput();

    shutdownMonitor();
}