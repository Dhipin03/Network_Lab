j#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];
    const char *message = "Hello from the client!";
    socklen_t addr_len = sizeof(server_addr);

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Send a message to the server
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, addr_len);

    // Receive data from the server
    int recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
    buffer[recv_len] = '\0';
    printf("Received message from server: %s\n", buffer);

    close(sockfd);
    return 0;
}
