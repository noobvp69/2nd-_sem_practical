#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];
    socklen_t len = sizeof(client);

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        printf("Cannot create socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sockdes, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Bind failed!");
        return 1;
    }

    printf("\nUDP Server listening on port 8888...\n");

    while (1) {
        recvfrom(sockdes, reply, 2000, 0, (struct sockaddr *)&client, &len);
        printf("\nFrom client: %s\n", reply);
        printf("\nTo client: ");
                fgets(msg,sizeof(msg),stdin);
        //msg[strcspn(msg,"\n")] = 0;// remove newline

        sendto(sockdes, msg, 2000, 0, (struct sockaddr *)&client, len);
    }

    close(sockdes);
    return 0;
}
