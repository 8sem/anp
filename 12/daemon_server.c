#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PORT 9090

void daemonize() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);   // Fork failed
    if (pid > 0) exit(EXIT_SUCCESS);   // Exit parent

    // Become session leader
    if (setsid() < 0) exit(EXIT_FAILURE);

    // Fork again to avoid terminal attachment
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    umask(0);               // Reset file mode mask
    chdir("/");             // Change working directory
    close(STDIN_FILENO);    // Close standard file descriptors
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main() {
    daemonize();

    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) exit(1);

    // Set socket option
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    int logfd = open("/tmp/daemon_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&addr, &addrlen);
        int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
        buffer[bytes] = '\0';
        dprintf(logfd, "Received: %s\n", buffer);
        close(client_fd);
    }

    close(server_fd);
    close(logfd);
    return 0;
}
//to run server do ./server &




