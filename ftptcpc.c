#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main() {
    int sock, n;  // Declare 'n' here
    struct sockaddr_in server;
    char buffer[2000];
    FILE *file;

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Cannot create socket");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // Server port
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server.\n");

    // Get file name from user
    printf("Enter the file name to send: ");
    scanf("%s", buffer);

    // Send file name to server
   send(sock, buffer, 2000, 0) ;

    // Open file for reading
    file = fopen(buffer, "rb");

    // Send file data
    while ((n = fread(buffer, 1, 2000, file)) > 0) {
        send(sock, buffer, n, 0) ;
        }
    

    printf("File sent successfully.\n");

    // Close file and socket
    fclose(file);
    close(sock);

    return 0;
}