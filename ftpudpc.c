#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockdes, n;
    struct sockaddr_in server;
    socklen_t s = sizeof(server);
    char buffer[2000];
    FILE *file;

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    printf("Enter the file name to send: ");
    scanf("%s", buffer);

    printf("Sending file name: %s\n", buffer);
    sendto(sockdes, buffer, strlen(buffer), 0, (struct sockaddr*)&server, s);

    file = fopen(buffer, "rb");
    if (!file) {
        perror("File open failed");
        exit(1);
    }

    printf("Sending file contents...\n");
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        sendto(sockdes, buffer, n, 0, (struct sockaddr*)&server, s);
    }

    // Send termination signal
    strcpy(buffer, "__END__");
    sendto(sockdes, buffer, strlen(buffer), 0, (struct sockaddr*)&server, s);

    fclose(file);
    close(sockdes);
    printf("File sent successfully.\n");

    return 0;
}
