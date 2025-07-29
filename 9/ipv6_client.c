#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int cfd = socket(AF_INET6, SOCK_STREAM, 0);
    struct sockaddr_in6 serv = {0};
    serv.sin6_family = AF_INET6;
    serv.sin6_port = htons(8080);

    // Connect to localhost IPv6 (::1)
    inet_pton(AF_INET6, "::1", &serv.sin6_addr);
    connect(cfd, (struct sockaddr*)&serv, sizeof(serv));

    char msg[100] = "Hello from IPv6 client";
    send(cfd, msg, strlen(msg), 0);

    char buf[100] = {};
    recv(cfd, buf, sizeof(buf), 0);
    printf("Server: %s\n", buf);

    close(cfd);
    return 0;
}

