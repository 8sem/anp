#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    int choice;
    char input[100];
    struct hostent *he;
    struct in_addr addr;

    printf("1. Hostname to IP\n2. IP to Hostname\nEnter choice: ");
    scanf("%d", &choice);
    getchar(); // Clear newline from buffer

    if (choice == 1) {
        printf("Enter hostname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        he = gethostbyname(input);
        if (he)
            printf("IP: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
        else
            printf("Hostname lookup failed.\n");

    } else if (choice == 2) {
        printf("Enter IP: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        inet_aton(input, &addr);
        he = gethostbyaddr(&addr, sizeof(addr), AF_INET);
        if (he)
            printf("Hostname: %s\n", he->h_name);
        else
            printf("IP lookup failed.\n");

    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

