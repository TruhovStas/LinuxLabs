#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define SOCK_NAME "mysocket"

int main(int argc, char **argv) {
    int sock;
    struct sockaddr_in addr;

    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);

    if (sock == -1) {
        fprintf(stderr, "socket() error\n");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(12345);

    if (sendto(sock, argv[1], strlen(argv[1]), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "sendto() error\n");
        return 1;
    }

    close(sock);

    return 0;
}
