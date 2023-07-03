#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *IP = "127.0.0.1";
    const int PORT = 8080;

    int server_sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        int err = errno;
        ::printf("Socket error:%s\n", ::strerror(err));
        std::exit(1);
    }
    ::printf("Socket okay\n");

    struct sockaddr_in server_addr;
    ::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = ::inet_addr(IP);
    if (::bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        int err = errno;
        ::printf("Bind error:%s\n", ::strerror(err));
        ::close(server_sock);
        std::exit(1);
    }
    ::printf("Bind okay\n");

    if (::listen(server_sock, 5) < 0) {
        int err = errno;
        ::printf("Listen error:%s\n", ::strerror(err));
        ::close(server_sock);
        std::exit(1);
    }
    ::printf("Listen okay\n\n");

    while(1) {
        struct sockaddr_in client_addr;
        socklen_t addr_size = sizeof(client_addr);
        int client_sock = ::accept(server_sock, (struct sockaddr *) &client_addr, &addr_size);
        if (client_sock < 0) {
            int err = errno;
            ::printf("Accept error:%s\n", ::strerror(err));
            continue;
        }
        ::printf("Accept okay\n");

        ::printf("Client connected\n");

        const size_t BUF_SIZE = 1024;
        char buffer[BUF_SIZE];

        ::memset(buffer, 0, sizeof(buffer));
        if (::recv(client_sock, buffer, sizeof(buffer) - 1, 0) < 0) {
            int err = errno;
            ::printf("Receive error:%s\n", ::strerror(err));
            ::close(client_sock);
            continue;
        }
        ::printf("Received:%s\n", buffer);

        ::memset(buffer, 0, sizeof(buffer));
        ::strncpy(buffer, "Hello, this is from Server!", sizeof(buffer) - 1);
        if (::send(client_sock, buffer, ::strlen(buffer), 0) < 0) {
            int err = errno;
            ::printf("Send error:%s\n", ::strerror(err));
            ::close(client_sock);
            continue;
        }
        ::printf("Send:%s\n", buffer);

        ::close(client_sock);
        ::printf("Client disconnected\n\n");
    }

    /* Nerver reach here. */
    ::close(server_sock);
    return 0;
}