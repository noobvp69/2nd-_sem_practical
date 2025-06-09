#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes, newsock, n;
    struct sockaddr_in server, client;
    socklen_t c = sizeof(client);
    char buffer[2000];
    FILE *file;

    // Create TCP socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind socket
    bind(sockdes, (struct sockaddr *)&server, sizeof(server));

    // Listen for incoming connections
    listen(sockdes, 1);

    printf("Server listening on port 8888...\n");

    // Accept a client connection
    newsock = accept(sockdes, (struct sockaddr *)&client, &c);
 

    printf("Client connected.\n");

    // Receive file name from client
    n = recv(newsock, buffer,2000, 0);
   
    buffer[n] = '\0';  // Null-terminate the file name

    printf("Receiving file: %s\n", buffer);

    // Open file for writing
    file = fopen(buffer, "wb");

    // Receive file data
    while ((n = recv(newsock, buffer,2000, 0)) > 0) {
        fwrite(buffer, 1, n, file);
    }


    printf("File received successfully.\n");

    // Close file and sockets
    fclose(file);
    close(newsock);
    close(sockdes);

    return 0;
}