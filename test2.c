#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>


int main(){
    int sockdes = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);
    connect(sockdes,(struct sockaddr*)&server, sizeof(server));
    
    char buf[100];
    read(sockdes,buf,sizeof(buf));
    printf("Daytime Server : %s",buf);
    close(sockdes);
}