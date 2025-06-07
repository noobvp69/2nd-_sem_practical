#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>


int main() {
    int sockdes = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(8888);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockdes, (struct sockaddr*)&client, sizeof(client)); // Connect to the server

    char buf[100];
    read(sockdes, buf, sizeof(buf)); // Receive time from server
    printf("Server date and time: %s\n", buf);

    close(sockdes); // Close the socket
    return 0;
}