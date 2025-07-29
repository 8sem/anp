#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int main() {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};

    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sfd, 5);
    printf("TCP Concurrent Server started on port 8080\n");

    while (1) {
        int cfd = accept(sfd, NULL, NULL);
        if (fork() == 0) {
            char buf[100] = {};
            recv(cfd, buf, sizeof(buf), 0);
            send(cfd, buf, strlen(buf), 0);
            close(cfd);
            exit(0);
        } else {
            close(cfd);
            waitpid(-1, NULL, WNOHANG);  // clean up zombies
        }
    }

    close(sfd);
    return 0;
}

