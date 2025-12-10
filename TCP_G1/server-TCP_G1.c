// Server TCP

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5000   // Porta su cui il server è in ascolto

int main() {

    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    int c, recv_size;
    char lettera;
    char risposta[50];
    int num1, num2, risultato;

    // Inizializzazione di WinSock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Creazione socket TCP (IPv4, stream)
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Impostazione parametri server (IP e porta)
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Binding della socket alla porta
    bind(serverSocket, (struct sockaddr*)&server, sizeof(server));

    // Messa in ascolto (coda max 3 connessioni)
    listen(serverSocket, 3);

    printf("Server TCP avviato sulla porta %d\n", PORT);

    while(1) {

        // Attesa connessione da un client
        c = sizeof(struct sockaddr_in);
        clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c);

        // Invio messaggio di benvenuto
        send(clientSocket, "connessione avvenuta", 21, 0);

        // Ricezione lettera dal client
        recv_size = recv(clientSocket, &lettera, 1, 0);

        // Controllo della lettera e preparazione risposta
        if(lettera == 'A' || lettera == 'a') strcpy(risposta, "ADDIZIONE");
        else if(lettera == 'S' || lettera == 's') strcpy(risposta, "SOTTRAZIONE");
        else if(lettera == 'M' || lettera == 'm') strcpy(risposta, "MOLTIPLICAZIONE");
        else if(lettera == 'D' || lettera == 'd') strcpy(risposta, "DIVISIONE");
        else strcpy(risposta, "TERMINE PROCESSO CLIENT");

        // Invio operazione al client
        send(clientSocket, risposta, strlen(risposta)+1, 0);

        // Se il client non vuole terminare, riceve numeri ed esegue operazione
        if(strcmp(risposta, "TERMINE PROCESSO CLIENT") != 0) {

            // Ricezione due interi dal client
            recv(clientSocket, (char*)&num1, sizeof(int), 0);
            recv(clientSocket, (char*)&num2, sizeof(int), 0);

            // Esecuzione operazione
            switch(lettera) {
                case 'A': case 'a': risultato = num1 + num2; break;
                case 'S': case 's': risultato = num1 - num2; break;
                case 'M': case 'm': risultato = num1 * num2; break;
                case 'D': case 'd': risultato = num1 / num2; break;
            }

            // Invio risultato al client
            send(clientSocket, (char*)&risultato, sizeof(int), 0);
        }

        // Chiusura socket verso il client corrente
        closesocket(clientSocket);
    }

    // Chiusura socket server e liberazione Winsock
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
