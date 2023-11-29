#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define BUF_LEN 4096
#define HTTPS_PORT 443

int main(int argc, char **argv) {
    int sock, count;
    char *buf;
    struct hostent *host;
    struct sockaddr_in addr;
    SSL_CTX *ctx;
    SSL *ssl;

    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }

    // Extract hostname from the URL
    char *url = argv[1] + strlen("https://");
    char *slash = strchr(url, '/');
    if (slash != NULL) {
        *slash = '\0'; // Null-terminate the hostname
    }

    buf = (char *)malloc(BUF_LEN);
    if (buf == NULL) {
        fprintf(stderr, "malloc() error\n");
        return 1;
    }

    // Initialize OpenSSL
    SSL_library_init();
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) {
        fprintf(stderr, "SSL_CTX_new() error\n");
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        fprintf(stderr, "socket() error\n");
        return 1;
    }

    addr.sin_family = AF_INET;

    host = gethostbyname(url);
    if (host == NULL) {
        fprintf(stderr, "Unknown server\n");
        return 1;
    }

    memcpy(&addr.sin_addr, host->h_addr_list[0], host->h_length);
    addr.sin_port = htons(HTTPS_PORT);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "connect() error\n");
        return 1;
    }

    // Set up SSL connection
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    if (SSL_connect(ssl) == -1) {
        fprintf(stderr, "SSL_connect() error\n");
        return 1;
    }

    // Send HTTPS request
    char request[BUF_LEN];
    snprintf(request, BUF_LEN, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", url);
    SSL_write(ssl, request, strlen(request));

    // Receive and print the response
    while ((count = SSL_read(ssl, buf, BUF_LEN)) > 0) {
        write(1, buf, count);
    }

    // Clean up
    SSL_free(ssl);
    close(sock);
    free(buf);
    SSL_CTX_free(ctx);

    return 0;
}
