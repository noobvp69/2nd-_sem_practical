#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockdes, n;
    struct sockaddr_in server, client;
    socklen_t c = sizeof(client);
    char buffer[2000];
    FILE *file;

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    printf("Binding done. Waiting to receive file name...\n");

    n = recvfrom(sockdes, buffer, 2000, 0, (struct sockaddr*)&client, &c);
    if (n < 0) {
        perror("recvfrom failed");
        exit(1);
    }

    buffer[n] = '\0';
    printf("Receiving file: %s\n", buffer);

    file = fopen(buffer, "wb");
    if (!file) {
        perror("File open failed");
        exit(1);
    }

    while ((n = recvfrom(sockdes, buffer, 2000, 0, (struct sockaddr*)&client, &c)) > 0) {
        buffer[n] = '\0';
        if (strcmp(buffer, "__END__") == 0) {
            printf("End of file received.\n");
            break;
        }
        fwrite(buffer, 1, n, file);
    }

    fclose(file);
    close(sockdes);
    printf("File received and saved successfully.\n");

    return 0;
}
