// Client TCP

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5000

int main() {

    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char serverName[100];
    char risposta[50];
    char lettera;
    int num1, num2, risultato;

    // Inizializzazione di WinSock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Inserimento nome server
    printf("Inserisci nome server (es. localhost): ");
    scanf("%s", serverName);

    // Creazione socket TCP
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Risoluzione DNS
    struct hostent *he = gethostbyname(serverName);
    if (he == NULL) {
        printf("Errore: impossibile risolvere hostname\n");
        return 1;
    }

    // Impostazione parametri server (IP e porta)
    memcpy(&server.sin_addr, he->h_addr, he->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connessione al server
    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Errore nella connessione\n");
        return 1;
    }

    // Ricezione messaggio di benvenuto
    recv(sock, risposta, 50, 0);
    printf("%s\n", risposta);

    // Invio lettera
    printf("Inserisci una lettera: ");
    scanf(" %c", &lettera);
    send(sock, &lettera, 1, 0);

    // Ricezione operazione
    recv(sock, risposta, 50, 0);
    printf("%s\n", risposta);

    // Controllo se terminare
    if(strcmp(risposta, "TERMINE PROCESSO CLIENT") == 0) {
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    // Lettura due interi
    printf("Inserisci due interi: ");
    scanf("%d %d", &num1, &num2);

    // Invio interi al server
    send(sock, (char*)&num1, sizeof(int), 0);
    send(sock, (char*)&num2, sizeof(int), 0);

    // Ricezione risultato
    recv(sock, (char*)&risultato, sizeof(int), 0);

    // Stampa risultato
    printf("Risultato = %d\n", risultato);

    // Chiusura socket
    closesocket(sock);
    WSACleanup();
    return 0;
}
