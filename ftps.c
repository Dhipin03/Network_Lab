#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket, addr_size;
    struct sockaddr_in server_addr, client_addr;
    char buffer[MAX_BUFFER_SIZE];
    FILE *file;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 1) < 0) {
        perror("Listening failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for connections...\n");

    // Accept connection from client
    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addr_size);
    if (client_socket < 0) {
        perror("Acceptance failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Client connected...\n");

    // Receive file data from client and save it to a file
    file = fopen("sfile.txt", "wb");
    if (file == NULL) {
        perror("File opening error");
        close(client_socket);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    ssize_t data_size;
    while ((data_size = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, data_size, file);
    

    if (data_size < 0) {
        perror("Receiving failed");
    } else {
        printf("File received successfully.\n");
    }
    }

    fclose(file);
    close(client_socket);
    close(server_socket);

    return 0;
}
