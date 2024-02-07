#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define RECONNECT_ATTEMPTS 3
#define TIMEOUT_SECONDS 5

int thaw_host(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    int attempt;
    int result = -1; // Default to failure

    for (attempt = 0; attempt < RECONNECT_ATTEMPTS; attempt++) {
        // Create the socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Error creating socket");
            return -1;
        }

        // Configure connection parameters
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
            perror("Invalid address / Address not supported");
            close(sockfd);
            continue;
        }

        // Set timeout for connection attempts
        struct timeval tv;
        tv.tv_sec = TIMEOUT_SECONDS;
        tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof tv);

        // Attempt to connect to the server
        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Connection Failed");
            close(sockfd);
        } else {
            result = 0; // Connection successful
            break;
        }
    }

    // If we completed a connection, close the socket
    if (result == 0) {
        close(sockfd);
    }

    return result;
}


This function attempts to connect to the specified IP and port `RECONNECT_ATTEMPTS` times with a timeout of `TIMEOUT_SECONDS` on each attempt. It uses IPv4 (AF_INET) and a TCP socket (SOCK_STREAM). If the connection is successful, it will close the socket and return 0. If all attempts fail, it will return -1.