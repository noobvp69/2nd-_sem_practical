#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create UDP socket
    char buffer[2000];
    struct sockaddr_in server, client;
    socklen_t c = sizeof(client);

   
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));  // Bind socket
    printf("Server is listening on port %d...\n", 8888);

    
        int n = recvfrom(sockfd, buffer, 2000, 0, (struct sockaddr *)&client, &c);  // Receive message
        buffer[n] = '\0';  // Null-terminate
        printf("Received: %s\n", buffer);  // Print received message
        sendto(sockfd, buffer, 2000, 0, (struct sockaddr *)&client, c);  // Echo back
    
        

    close(sockfd);  // Close socket
    return 0;
}