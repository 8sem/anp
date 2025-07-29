#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 9090

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char *message = "Hello from C client!";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        exit(1);
    }

    send(sock, message, strlen(message), 0);
    printf("Message sent to daemon server.\n");

    close(sock);
    return 0;
}

