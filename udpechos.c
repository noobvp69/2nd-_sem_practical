#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main() {
    int sockfd;
    char buffer[2000];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create UDP socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8888);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));  // Bind socket
    printf("Server is listening on port %d...\n", 8888);

    while (1) {
        int n = recvfrom(sockfd, buffer, 2000, 0, (struct sockaddr *)&client_addr, &addr_len);  // Receive message
        buffer[n] = '\0';  // Null-terminate
        printf("Received: %s\n", buffer);  // Print received message
        sendto(sockfd, buffer, 2000, 0, (struct sockaddr *)&client_addr, addr_len);  // Echo back
    }

    close(sockfd);  // Close socket
    return 0;
}