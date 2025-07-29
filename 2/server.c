#include <stdio.h>
#include <stdlib.h>             // <-- add this for atoi()
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int a, char *v[]) {
    if (a != 2) return printf("Usage: %s <port>\n", v[0]), 1;

    int sfd = socket(AF_INET, SOCK_STREAM, 0), cfd;
    struct sockaddr_in addr = {AF_INET, htons(atoi(v[1])), INADDR_ANY};

    bind(sfd, (void*)&addr, sizeof(addr));
    listen(sfd, 1);
    cfd = accept(sfd, NULL, NULL);

    char buf[100] = {};
    recv(cfd, buf, sizeof(buf), 0);
    printf("Client: %s\n", buf);

    send(cfd, "Hello from server", 17, 0);
    close(cfd); close(sfd);
}

