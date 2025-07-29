#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY}, cli;
    socklen_t clen = sizeof(cli);
    char buf[100];

    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    printf("UDP Echo Server started on port 8080\n");

    while (1) {
        memset(buf, 0, sizeof(buf));
        recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &clen);
        sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&cli, clen);
    }

    close(sfd);
    return 0;
}

