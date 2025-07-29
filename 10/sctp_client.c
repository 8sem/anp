#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    struct sockaddr_in servaddr = {0};
    char buffer[100];

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    send(sockfd, "Hello from client", 17, 0);
    close(sockfd);
    return 0;
}

