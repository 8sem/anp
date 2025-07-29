#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("/tmp/daemon_log.txt", "r");
    if (!fp) {
        perror("Error opening log file");
        return 1;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
    return 0;
}

