#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main() {
    uint16_t s;
    uint32_t l;

    printf("Enter a 16-bit number: ");
    scanf("%hu", &s);  // %hu for uint16_t

    printf("Enter a 32-bit number: ");
    scanf("%u", &l);   // %u for uint32_t

    printf("\nHost to Network (htons): %u\n", htons(s));
    printf("Network to Host (ntohs): %u\n", ntohs(htons(s)));

    printf("Host to Network (htonl): %u\n", htonl(l));
    printf("Network to Host (ntohl): %u\n", ntohl(htonl(l)));

    // Check endianness
    uint16_t x = 1;
    if (*(char*)&x) {
        printf("System is Little Endian\n");
    } else {
        printf("System is Big Endian\n");
    }

    return 0;
}
