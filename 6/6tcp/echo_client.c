#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) return printf("Usage: %s <server_ip> <tcp|udp>\n", argv[0]), 1;

    int is_udp = strcmp(argv[2], "udp") == 0;
    int sock = socket(AF_INET, is_udp ? SOCK_DGRAM : SOCK_STREAM, 0);
    struct sockaddr_in server = {AF_INET, htons(8080)};
    inet_pton(AF_INET, argv[1], &server.sin_addr);

    char msg[100], buf[100];
    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);

    if (is_udp) {
        sendto(sock, msg, strlen(msg), 0, (void*)&server, sizeof(server));
        socklen_t slen = sizeof(server);
        recvfrom(sock, buf, sizeof(buf), 0, (void*)&server, &slen);
    } else {
        connect(sock, (void*)&server, sizeof(server));
        send(sock, msg, strlen(msg), 0);
        recv(sock, buf, sizeof(buf), 0);
    }

    printf("Echo: %s\n", buf);
    close(sock);
}

