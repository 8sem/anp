#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sfd = socket(AF_INET6, SOCK_STREAM, 0);
    struct sockaddr_in6 serv = {0};
    serv.sin6_family = AF_INET6;
    serv.sin6_port = htons(8080);
    serv.sin6_addr = in6addr_any;  // IPv6 equivalent of INADDR_ANY

    bind(sfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sfd, 5);

    printf("IPv6 TCP Server running on port 8080...\n");

    int cfd = accept(sfd, NULL, NULL);
    char buf[100] = {};
    recv(cfd, buf, sizeof(buf), 0);
    printf("Client: %s\n", buf);
    send(cfd, buf, strlen(buf), 0);  // echo

    close(cfd);
    close(sfd);
    return 0;
}

