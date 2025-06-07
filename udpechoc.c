#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    char buffer[2000];
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create UDP socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Server IP (localhost)

    printf("Enter a string: ");
    fgets(buffer,sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline

    sendto(sockfd, buffer, 2000, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));  // Send to server
    recvfrom(sockfd, buffer,2000, 0, NULL, NULL);  // Receive echoed message
    printf("From server: %s\n", buffer);  // Print echoed message

    close(sockfd);  // Close socket
    return 0;
}