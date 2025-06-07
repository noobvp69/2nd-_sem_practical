#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];
    socklen_t len = sizeof(server);

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        printf("\nCannot create socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    while (1) {
        printf("\nTo server: ");
        fgets(msg,sizeof(msg),stdin);
       // msg[strcspn(msg,"\n")] = 0;// remove newline
        sendto(sockdes, msg, 2000, 0, (struct sockaddr *)&server, len);
        recvfrom(sockdes, reply, 2000, 0, (struct sockaddr *)&server, &len);
        printf("\nFrom server: %s\n", reply);
    }

    close(sockdes);
    return 0;
}
