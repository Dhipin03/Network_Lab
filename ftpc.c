#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];
    FILE *file;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server...\n");

    // Read the file to be sent
    file = fopen("cfile.txt", "rb");
    if (file == NULL) {
        perror("File opening error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Send file data to the server
    ssize_t data_size;
    while ((data_size = fread(buffer, 1, MAX_BUFFER_SIZE, file)) > 0) {
        if (send(client_socket, buffer, data_size, 0) < 0) {
            perror("Sending failed");
            fclose(file);
            close(client_socket);
            exit(EXIT_FAILURE);
        }
    }

    printf("File sent successfully.\n");

    fclose(file);
    close(client_socket);

    return 0;
}
