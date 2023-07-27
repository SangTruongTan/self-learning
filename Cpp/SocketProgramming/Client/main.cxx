#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *IP = "127.0.0.1";
    const int PORT = 8080;

    int sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        int err = errno;
        ::printf("Socket error: %s\n", ::strerror(err));
        std::exit(1);
    }
    ::printf("Socket okay\n");

    struct sockaddr_in addr;
    ::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = PORT;
    addr.sin_addr.s_addr = ::inet_addr(IP);

    if (::connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        int err = errno;
        ::printf("Connect error:%s\n", strerror(err));
        ::close(sock);
        std::exit(1);
    }
    ::printf("Connect okay\n");

    const size_t BUF_SIZE = 1024;
    char buffer[BUF_SIZE];
    ::memset(buffer, 0, sizeof(buffer));
    ::strncpy(buffer, "Hello, this is client!", sizeof(buffer) - 1);

    if(::send(sock, buffer, ::strlen(buffer), 0) < 0) {
        int err = errno;
        ::printf("Send error:%s\n", strerror(err));
        ::close(sock);
        std::exit(1);
    }
    ::printf("Send okay:%s\n", buffer);

    ::memset(buffer, 0, sizeof(buffer));

    if(::recv(sock, buffer, sizeof(buffer) - 1, 0) < 0) {
        int err = errno;
        ::printf("Received error:%s\n", strerror(err));
        ::close(sock);
        std::exit(1);
    }
    ::printf("Received okay:%s\n", buffer);

    ::close(sock);
    ::printf("Disconnected\n");

    return 0;
}
