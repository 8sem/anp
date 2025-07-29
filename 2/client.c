#include <stdio.h>
#include <stdlib.h>             // <-- add this for atoi()
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int a, char *v[]) {
    if (a != 3) return printf("Usage: %s <ip> <port>\n", v[0]), 1;

    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in srv = {AF_INET, htons(atoi(v[2]))};
    inet_pton(AF_INET, v[1], &srv.sin_addr);

    connect(cfd, (void*)&srv, sizeof(srv));
    send(cfd, "Hello from client", 17, 0);

    char buf[100] = {};
    recv(cfd, buf, sizeof(buf), 0);
    printf("Server: %s\n", buf);

    close(cfd);
}

