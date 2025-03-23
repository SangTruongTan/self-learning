#include <iostream>
#include <arpa/inet.h>

int main() {
    // IPv4:

    char ip4[INET_ADDRSTRLEN]; // space to hold the IPv4 string
    struct sockaddr_in sa;     // pretend this is loaded with something

    inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

    printf("The IPv4 address is: %s\n", ip4);

    // IPv6:

    char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
    struct sockaddr_in6 sa6;    // pretend this is loaded with something

    inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

    printf("The address is: %s\n", ip6);
}
