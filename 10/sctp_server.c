#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    struct sockaddr_in servaddr = {0}, cliaddr;
    char buffer[100];
    socklen_t len = sizeof(cliaddr);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9000);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sockfd, 1);
    int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);

    send(connfd, "Hello from server", 17, 0);
    recv(connfd, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    close(connfd);
    close(sockfd);
    return 0;
}

