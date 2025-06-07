#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockdes = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    struct sockaddr_in server; 
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockdes, (struct sockaddr*)&server, sizeof(server)); // Bind socket to port 8080
    listen(sockdes, 1); // Listen for incoming connections

    printf("Daytime server is listening on port 8888...\n" );

    while (1) {
        int newsock = accept(sockdes, NULL, NULL); // Accept a new connection
        time_t rawtime = time(NULL); // Get current time
        char buf[100];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&rawtime)); // Format time
        write(newsock, buf, sizeof(buf)); // Send time to client
        close(newsock); // Close the connection
    }
}