#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create UDP socket
    char buffer[2000];
    struct sockaddr_in server;
    socklen_t c = sizeof(server);


    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = INADDR_ANY;  // Server IP (localhost)

    printf("Enter a string: ");
    fgets(buffer,sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline

    sendto(sockfd, buffer, 2000, 0, (struct sockaddr *)&server, c);  // Send to server
    recvfrom(sockfd, buffer,2000, 0, NULL, NULL);  // Receive echoed message
    printf("From server: %s\n", buffer);  // Print echoed message

    close(sockfd);  // Close socket
    return 0;
}